#ifndef __AOC_IO_HPP__
#define __AOC_IO_HPP__

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {

std::string get_input_bare(std::string fn);

template <typename T> std::vector<T> get_input_list(std::string fn, int year, int day) {
    std::ifstream         ifs;
    std::vector<T>        return_data;
    std::string           line;
    std::filesystem::path path(std::filesystem::current_path());
    std::filesystem::path datapath;

    if (fn == "input.txt") {
        for (auto dir = path.begin(); *dir != "C++" && dir != path.end(); dir++) {
            datapath /= *dir;
        }
        datapath = datapath / "data" / std::format("{:4d}", year) / std::format("{:02d}", day) / fn;
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
    std::filesystem::path datapath;

    if (fn == "input.txt") {
        for (auto dir = path.begin(); *dir != "C++" && dir != path.end(); dir++) {
            datapath /= *dir;
        }
        datapath = datapath / "data" / std::to_string(year) / std::format("{:02d}", day) / fn;
        ifs.open(datapath);
        std::cout << datapath << std::endl;
    } else {
        ifs.open(fn);
    }

    while (std::getline(ifs, line)) {
        result.push_back(std::stoi(line));
    }

    return result;
}

namespace string {

std::vector<std::string> split(const std::string &, char);

} // namespace string

} // namespace aoc

#endif
