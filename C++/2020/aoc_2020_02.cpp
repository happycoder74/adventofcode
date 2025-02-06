#include "aoc_timer.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <numeric>
#include <span>
#include <sstream>
#include <string>
#include <vector>

int solve_part_1(const std::vector<std::tuple<int, int, char, std::string>> &data) {
    int count = 0;
    for (auto &item : data) {
        int         count_start = std::get<0>(item);
        int         count_end   = std::get<1>(item);
        char        letter      = std::get<2>(item);
        std::string passwd      = std::get<3>(item);

        auto num_chars = std::transform_reduce(passwd.begin(), passwd.end(), 0, std::plus{}, [&](auto c) { return c == letter ? 1 : 0; });
        if ((count_start <= num_chars) && (num_chars <= count_end))
            count++;
    }
    return count;
}

int solve_part_2(const std::vector<std::tuple<int, int, char, std::string>> &data) {
    int count = 0;
    for (auto &item : data) {
        int         first_pos  = std::get<0>(item) - 1;
        int         second_pos = std::get<1>(item) - 1;
        char        letter     = std::get<2>(item);
        std::string passwd     = std::get<3>(item);
        if ((passwd[first_pos] == letter) != (passwd[second_pos] == letter))
            count++;
    }
    return count;
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
