#include "aoc_timer.hpp"
#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <numeric>
#include <ranges>
#include <span>
#include <sstream>
#include <string>
#include <vector>

int solve_part_1(const std::vector<std::tuple<int, int, char, std::string>> &data) {
    auto count = data | std::views::transform([](auto &item) {
                     int         count_start = std::get<0>(item);
                     int         count_end   = std::get<1>(item);
                     char        letter      = std::get<2>(item);
                     std::string passwd      = std::get<3>(item);
                     auto        num_chars   = std::count(passwd.begin(), passwd.end(), letter);
                     return ((count_start <= num_chars) && (num_chars <= count_end)) ? 1 : 0;
                 });
    return std::reduce(count.begin(), count.end());
}

int solve_part_2(const std::vector<std::tuple<int, int, char, std::string>> &data) {
    auto count = data | std::views::transform([](auto &item) {
                     int         first_pos  = std::get<0>(item) - 1;
                     int         second_pos = std::get<1>(item) - 1;
                     char        letter     = std::get<2>(item);
                     std::string passwd     = std::get<3>(item);
                     if ((passwd[first_pos] == letter) != (passwd[second_pos] == letter)) {
                         return 1;
                     } else {
                         return 0;
                     }
                 });
    return std::reduce(count.begin(), count.end());
}

int main(int argc, char **argv) {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 2;

    auto args = std::span(argv, size_t(argc));

    std::vector<std::tuple<int, int, char, std::string>> data;

    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    filepath = filepath / std::format("{}/{:02d}", year, day) / filename;
    std::ifstream ifs(filepath);
    std::string   line;
    while (std::getline(ifs, line)) {
        std::stringstream ss{line};
        int               a = 0, b = 0;
        char              letter = 0, tmp = 0;
        std::string       passwd;
        ss >> a >> tmp >> b >> letter >> tmp >> passwd;
        data.push_back(std::tuple(a, b, letter, passwd));
    }

    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    return 0;
}
