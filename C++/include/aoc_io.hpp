#ifndef __AOC_IO_HPP__
#define __AOC_IO_HPP__

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc::io {

inline void header(const int year, const int day) {
    std::cout << std::format("{:=<55}", "") << '\n';
    std::cout << std::format("Solution for {:d}, day {:02d}", year, day) << '\n';
    std::cout << std::format("{:-<55}", "") << '\n';
}

auto get_input_bare(const std::string &fn) -> std::string;

template <typename T>
[[nodiscard]] auto get_input_groups(const std::string &fn, int year, int day) -> std::vector<std::vector<T>> {
    std::ifstream               ifs;
    std::vector<std::vector<T>> return_data;
    std::string                 line;
    std::string                 datapath_str;

    std::filesystem::path datapath;
    std::filesystem::path path(std::filesystem::current_path());

    char *env    = std::getenv("AOC_DATA_LOCATION");
    datapath_str = std::string(env ? env : "");
    if (datapath_str.length()) {
        datapath = std::filesystem::path(datapath_str) / std::format("{:4d}", year) / std::format("{:02d}", day) / fn;
        ifs.open(datapath);
    } else {
        ifs.open(fn);
    }
    if (ifs.fail()) {
        std::cerr << "Something went wrong" << '\n';
        std::cerr << "Can not open '" << datapath << "'\n";
        return return_data;
    }
    std::vector<T> vec{};
    while (std::getline(ifs, line)) {
        if (line.length() == 0) {
            return_data.push_back(vec);
            vec.clear();
            continue;
        }
        vec.push_back(line);
    }
    return_data.push_back(vec);
    return return_data;
}

template <typename T>
[[nodiscard]] auto get_input_list(const std::string &fn, int year, int day) -> std::vector<T> {
    std::ifstream  ifs;
    std::vector<T> return_data;
    std::string    line;
    std::string    datapath_str;

    std::filesystem::path datapath;
    std::filesystem::path path(std::filesystem::current_path());

    char *env    = std::getenv("AOC_DATA_LOCATION");
    datapath_str = std::string(env ? env : "");
    if (datapath_str.length()) {
        datapath = std::filesystem::path(datapath_str) / std::format("{:4d}", year) / std::format("{:02d}", day) / fn;
        ifs.open(datapath);
    } else {
        ifs.open(fn);
    }
    if (ifs.fail()) {
        std::cerr << "Something went wrong" << '\n';
        std::cerr << "Can not open '" << datapath << "'\n";
        return return_data;
    }
    while (std::getline(ifs, line)) {
        return_data.push_back(line);
    }

    return return_data;
}

template <>
[[nodiscard]] inline auto get_input_list(const std::string &fn, int year, int day) -> std::vector<int> {
    std::ifstream    ifs;
    std::string      line;
    std::vector<int> result;
    std::string      datapath_str;

    std::filesystem::path datapath;
    std::filesystem::path path(std::filesystem::current_path());

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
