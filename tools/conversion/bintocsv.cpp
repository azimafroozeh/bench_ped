// Standard libs
#include <filesystem>
#include <fstream>

// External libs
#include "gflags/gflags.h"
#include "yaml-cpp/yaml.h"
#include "spdlog/spdlog.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"

// Btr internal includes
#include "storage/Relation.hpp"
#include "datablock/schemes/CSchemePool.hpp"
#include "datablock/Datablock.hpp"
#include "datablock/cache/ThreadCache.hpp"
#include "parser/Parser.hpp"
#include "analysis/Analysis.hpp"
#include "datablock/BtrReader.hpp"
#include "storage/StringPointerArrayViewer.hpp"
#include "utils/Utils.hpp"
#include "Units.hpp"


DEFINE_string(input_file, "data.bin", "Data file");
DEFINE_string(type, "integer", "Data type");
DEFINE_string(delimiter, ",", "CSV Delimiter");
DEFINE_string(output_file, "/tmp/data.csv", "File for CSV output");
DEFINE_string(fsst_stats, "", ""); // For the linker

template<typename T, typename F>
void outputColumn(const std::string& input_file, const std::string& output_file, F fn = [](std::ostream& s) { return s; }) {
    auto output = ofstream(output_file);
    Vector<T> input(input_file.c_str());

    for (auto i = 0ul; i != input.size(); ++i) {
       fn(output) << FLAGS_delimiter << input[i] << std::endl;
    }
}


int main(int argc, char **argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    auto fn = [](std::ostream& s) -> std::ostream& {
        return s << "a,b";
    };

    if (FLAGS_type == "integer") {
        outputColumn<INTEGER>(FLAGS_input_file, FLAGS_output_file, fn);
    } else if (FLAGS_type == "double") {
        outputColumn<DOUBLE>(FLAGS_input_file, FLAGS_output_file, fn);
    } else if (FLAGS_type == "string") {
        outputColumn<std::string_view>(FLAGS_input_file, FLAGS_output_file, fn);
    }

    return 0;
}
