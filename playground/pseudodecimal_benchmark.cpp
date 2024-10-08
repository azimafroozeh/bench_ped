#include "datablock/schemes/CSchemePicker.hpp"
#include "datablock/schemes/v2/double/DynamicDictionary.hpp"
#include "datablock/schemes/v2/double/Frequency.hpp"
#include "datablock/schemes/v2/double/RLE.hpp"
#include "datablock/schemes/v2/double/DoubleBP.hpp"

#include "datablock/schemes/v2/integer/PBP.hpp"
#include "gflags/gflags.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/ranges.h"

#include "Units.hpp"
#include "PerfEvent.hpp"
#include "datablock/schemes/v2/double/Decimal.hpp"
#include "datablock/schemes/CScheme.hpp"
#include "datablock/schemes/CSchemePool.hpp"

#include <string>
#include <fstream>
#include <sstream>


// for some reason, this is only DECLARED in DynamicDictionary but not defined (breaks linking)
// and then DEFINED in every cpp file that uses it
DEFINE_string(fsst_stats, "", "");
DEFINE_string(input_file, "pbi-double-columns.txt", "file-list");
DEFINE_int32(cascade_depth, 1, "cascade");

// example2.double: s3://public-bi-benchmark/binary/Telco/1/Telco_1/106_RECHRG_INC_MIN_USED_P1.double
// example2.bitmap: s3://public-bi-benchmark/binary/Telco/1/Telco_1/106_RECHRG_INC_MIN_USED_P1.bitmap

struct InputFiles {
    std::ifstream list;
    InputFiles(const std::string& filename) : list(filename) {
        std::cout << "file " << filename << std::endl;
    }

    bool next(std::string& output) {
        return !(std::getline(list, output).fail());
    }
};

using T = double;
bool test_compression(cengine::db::DoubleScheme &scheme, cengine::db::DoubleStats& stats, T* src, size_t size, PerfEvent& e, u8 cascade) {
    std::vector<u8> compressed(size * sizeof(T) * 2);
    std::vector<T> dst(size * 2, 0);

    auto src_ptr = src;
    auto compressed_ptr = reinterpret_cast<u8 *>(compressed.data());
    auto dst_ptr = dst.data();

    size_t output_bytes{-1ul};
    e.setParam("cascade", cascade);
    e.setParam("phase", "compression");
    {
      PerfEventBlock blk(e, size);
      try {
        output_bytes = scheme.compress(src_ptr, nullptr, compressed_ptr, stats, cascade);
      } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
      }
      //std::cout << "cf: " << 1.0 * size * sizeof(T) / output_bytes << std::endl;
      e.setParam("compr", (1.0 * size * sizeof(T)) / output_bytes);
    }

    e.setParam("phase", "decompression");
    {
      PerfEventBlock blk(e, size);
      try {
        scheme.decompress(dst_ptr, nullptr, compressed_ptr, stats.tuple_count, cascade);
      } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
      }
    }
    //std::cerr << "Decompression done." << std::endl;
    for (auto i = 0ul; i != size; ++i) {
        die_if(src[i] == dst[i]);
    }

    return 0;
}

void setupSchemePool()
{
  using namespace cengine::db;
  cengine::db::CSchemePool::refresh();
  auto& schemes = *cengine::db::CSchemePool::available_schemes;
  return;
  // double: DOUBLE_BP, UNCOMPRESSED,
  for (auto it = schemes.double_schemes.begin();
       it != schemes.double_schemes.end();) {
    if (it->first != DoubleSchemeType::DOUBLE_BP &&
        it->first != DoubleSchemeType::UNCOMPRESSED) {
      it = schemes.double_schemes.erase(it);
    } else {
      ++it;
    }
  }
  // int: X_FBP, UNCOMPRESSED,
  for (auto it = schemes.integer_schemes.begin(); it != schemes.integer_schemes.end();) {
    if (it->first != IntegerSchemeType::X_FBP &&
        it->first != IntegerSchemeType::UNCOMPRESSED) {
      it = schemes.integer_schemes.erase(it);
    } else {
      ++it;
    }
  }
}

/**
 * interesting columns:
 * - columns/CommonGovernment/1/CommonGovernment_1/31_gsaotherdollar.double
 *   + bitpack: 12.2, decimal2: 23.5, rle2: 8.5
 * - columns/CommonGovernment/1/CommonGovernment_1/30_gsadollar.double
 *   + bitpack: 4.6, decimal2: 7.8, rle2: 3.9
 * - columns/Arade/1/Arade_1/9_F9.double
 *   + bitpack: 0.99, decimal2: 2.01, rle2: 1.36
 * */
int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    setupSchemePool();
#ifdef NDEBUG
    // spdlog::set_level(spdlog::level::debug);
    spdlog::set_level(spdlog::level::warn);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    PerfEvent perf;
    std::cerr << "using cascade depth " << FLAGS_cascade_depth << " and input file " << FLAGS_input_file << std::endl;

    InputFiles file_list(FLAGS_input_file);

    std::string bucket = "s3://public-bi-benchmark-us-east-2/binary/";
    std::string nextfile;
    int i = 0;
    while (file_list.next(nextfile)) {
      std::string outfile = "columns/" + nextfile;
      if (nextfile[0] == '#') { continue; }
      if (i++ > 20) { break; }
      std::stringstream _cmd;
      _cmd << "bash -c '(mkdir -p columns; test -f \"" << outfile << "\" && echo \"file exists, skipping download\" || (echo \"downloading file\"; aws s3 cp \"" << bucket << nextfile << "\" \"" << outfile << "\")) 1>&2'";
      std::string  cmd(_cmd.str());
      spdlog::info("running {}", cmd);
      system(cmd.c_str());

      Vector<T> doubles(outfile.c_str());

      {
        std::vector<T> head(doubles.data, doubles.data + std::min(10ul, doubles.size()));
        spdlog::info("size: {:03.2f} MiB, head: {}", (sizeof(T) * doubles.size()) * 1.0 / 1024 / 1024, head);
      }

      perf.setParam("column", nextfile);
      perf.setParam("scheme", "none");
      perf.setParam("compr", 1);
      perf.setParam("cascade", 0);

      cengine::db::DoubleStats stats(doubles.data, nullptr, doubles.size());
      perf.setParam("phase", "stats");
      {
        PerfEventBlock blk(perf, doubles.size());
        stats = cengine::db::DoubleStats::generateStats(doubles.data, nullptr, doubles.size());
      }

      perf.setParam("scheme", "bitpack");
      cengine::db::v2::d::DoubleBP bp;
      test_compression(bp, stats, doubles.data, doubles.count, perf, 0);

      perf.setParam("scheme", "decimal");
      cengine::db::v2::d::Decimal pd;
      test_compression(pd, stats, doubles.data, doubles.count, perf, 1);
      test_compression(pd, stats, doubles.data, doubles.count, perf, 2);

      perf.setParam("scheme", "dict");
      cengine::db::v2::d::DynamicDictionary dict;
      test_compression(dict, stats, doubles.data, doubles.count, perf, 1);
      test_compression(dict, stats, doubles.data, doubles.count, perf, 2);

      perf.setParam("scheme", "rle");
      cengine::db::v2::d::RLE rle;
      test_compression(rle, stats, doubles.data, doubles.count, perf, 1);
      test_compression(rle, stats, doubles.data, doubles.count, perf, 2);

      //perf.setParam("scheme", "freq");
      //cengine::db::v2::d::Frequency freq;
      //test_compression(freq, stats, doubles.data, doubles.count, perf, 1);
      //test_compression(freq, stats, doubles.data, doubles.count, perf, 2);
    }
}
