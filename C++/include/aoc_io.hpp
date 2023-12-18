#ifndef __AOC_IO_HPP__
#define __AOC_IO_HPP__

#include <filesystem>
#include <format>
#include <fstream>
#include <string>
#include <vector>

namespace aoc::io {

std::string get_input_bare(std::string fn);

template <typename T> std::vector<T> get_input_list(std::string fn, int year, int day) {
    std::ifstream         ifs;
    std::vector<T>        return_data;
    std::string           line;
    std::filesystem::path path(std::filesystem::current_path());
    std::string           datapath_str;
    std::filesystem::path datapath;

    datapath_str = std::string(std::getenv("AOC_DATA_LOCATION"));
    if (datapath_str.length()) {
        datapath = datapath_str;
        datapath = datapath / std::format("{:4d}", year) / std::format("{:02d}", day) / fn;
        ifs.open(datapath);
    } else {
        ifs.open(fn);
    }
    while (std::getline(ifs, line)) {
        return_data.push_back(line);
    }

    return return_data;
}
template <> inline std::vector<int> get_input_list(std::string fn, int year, int day) {
    std::ifstream         ifs;
    std::string           line;
    std::vector<int>      result;
    std::filesystem::path path(std::filesystem::current_path());
    std::string           datapath_str;
    std::filesystem::path datapath;

    datapath_str = std::string(std::getenv("AOC_DATA_LOCATION"));
    if (datapath_str.length()) {
        datapath = datapath_str;
        datapath = datapath / std::format("{:4d}", year) / std::format("{:02d}", day) / fn;
        ifs.open(datapath);
    } else {
        ifs.open(fn);
    }

    while (std::getline(ifs, line)) {
        result.push_back(std::stoi(line));
    }

    return result;
}
} // namespace aoc::io

#endif
