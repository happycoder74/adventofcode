#ifndef __AOC_IO_HPP__
#define __AOC_IO_HPP__

#include <fstream>
#include <string>
#include <vector>

namespace aoc {
    std::string get_input_bare(std::string fn, int year, int day);

    template <typename T>
    std::vector<T> get_input_list(std::string fn, int year, int day) {
        std::ifstream ifs(fn);
        std::vector<T> return_data;
        std::string line;

        while(std::getline(ifs, line)) {
            return_data.push_back(line);
        }

        return return_data;
    }
    template<>
        inline std::vector<int> get_input_list(std::string fn, int year, int day) {
        std::ifstream ifs(fn);
        std::string line;
        std::vector<int> result;

        while(std::getline(ifs, line)) {
           result.push_back(std::stoi(line));
        }

        return result;
    }
}

#endif
