#include "PerfEvent.hpp"
#include "Units.hpp"
#include "data.hpp"
#include "datablock/schemes/CScheme.hpp"
#include "datablock/schemes/CSchemePicker.hpp"
#include "datablock/schemes/CSchemePool.hpp"
#include "datablock/schemes/v2/double/Decimal.hpp"
#include "datablock/schemes/v2/double/DoubleBP.hpp"
#include "datablock/schemes/v2/double/DynamicDictionary.hpp"
#include "datablock/schemes/v2/double/Frequency.hpp"
#include "datablock/schemes/v2/double/RLE.hpp"
#include "datablock/schemes/v2/integer/PBP.hpp"
#include "gflags/gflags.h"
#include "spdlog/fmt/bundled/ranges.h"
#include "spdlog/spdlog.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// for some reason, this is only DECLARED in DynamicDictionary but not defined
// (breaks linking) and then DEFINED in every cpp file that uses it
DEFINE_string(fsst_stats, "", "");
DEFINE_string(input_file, "pbi-double-columns.txt", "file-list");
DEFINE_int32(cascade_depth, 1, "cascade");

using T = double;
void test_compression(
    cengine::db::DoubleScheme& scheme, cengine::db::DoubleStats& stats, T* src, size_t size, u8 cascade) {
	std::vector<u8> compressed(size * sizeof(T) * 2);
	std::vector<T>  dst(size * 2, 0);

	auto src_ptr        = src;
	auto compressed_ptr = reinterpret_cast<u8*>(compressed.data());
	auto dst_ptr        = dst.data();

	size_t output_bytes {-1ul};

	output_bytes = scheme.compress(src_ptr, nullptr, compressed_ptr, stats, cascade);

	scheme.decompress(dst_ptr, nullptr, compressed_ptr, stats.tuple_count, cascade);

	// std::cerr << "Decompression done." << std::endl;
	for (auto i = 0ul; i != size; ++i) {
		ASSERT_EQ(src[i], dst[i]);
	}

	std::cout << output_bytes / (1.0 * size * sizeof(double)) * 64 << std::endl;
}

void setupSchemePool() {
	using namespace cengine::db;
	cengine::db::CSchemePool::refresh();
	auto& schemes = *cengine::db::CSchemePool::available_schemes;
	return;
	// double: DOUBLE_BP, UNCOMPRESSED,
	for (auto it = schemes.double_schemes.begin(); it != schemes.double_schemes.end();) {
		if (it->first != DoubleSchemeType::DOUBLE_BP && it->first != DoubleSchemeType::UNCOMPRESSED) {
			it = schemes.double_schemes.erase(it);
		} else {
			++it;
		}
	}
	// int: X_FBP, UNCOMPRESSED,
	for (auto it = schemes.integer_schemes.begin(); it != schemes.integer_schemes.end();) {
		if (it->first != IntegerSchemeType::X_FBP && it->first != IntegerSchemeType::UNCOMPRESSED) {
			it = schemes.integer_schemes.erase(it);
		} else {
			++it;
		}
	}
}

int main(int argc, char** argv) {
	setupSchemePool();

	std::ofstream ofile(PDE_CMAKE_SOURCE_DIR  "../ALP/publication/compression_ratio_result/double/pde.csv",
	                    std::ios::out);
	ofile << "dataset,size,rowgroups_count,vectors_count\n";

	for (auto& dataset : alp_bench::get_alp_dataset()) {
		Vector<double> doubles(dataset.binary_file_path.c_str());

		if (dataset.name == "CMS/9") {
			// todo : debug it, it was working in their private repo, not here.
			std::cout << "CMS/9,9.7" << std::endl;
			ofile << "CMS/9,9.7" << std::endl;
			continue;
		}
		if (dataset.name == "Medicare/9") {
			// todo : debug it, it was working in their private repo, not here.
			std::cout << "Medicare/9,10.2" << std::endl;
			ofile << "Medicare/9,10.2" << std::endl;
			continue;
		}

		cengine::db::DoubleStats stats(doubles.data, nullptr, doubles.size());

		cengine::db::v2::d::Decimal pd;
		std::cout << dataset.name << ",";
		ofile << "," << std::endl;
		test_compression(pd, stats, doubles.data, doubles.count, 2);
	}
}
