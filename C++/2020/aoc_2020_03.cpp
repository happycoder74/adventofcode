#include "aoc_timer.hpp"
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <span>
#include <string>
#include <vector>

int solve_part_1(const std::pair<std::vector<std::string>, std::vector<std::pair<int, int>>> &data) {
    auto result   = 0;
    auto [dx, dy] = data.second[0];
    auto trees    = data.first;
    int  x        = 0;
    for (int y = 0; y < trees.size(); y += dy) {
        if (trees[y][x] == '#') {
            result += 1;
        }
        x = (x + dx) % (int)trees[0].size();
    }
    return result;
}

std::uint64_t solve_part_2(const std::pair<std::vector<std::string>, std::vector<std::pair<int, int>>> &data) {
    std::uint64_t result = 1;
    auto          trees  = data.first;
    for (int slope = 0; slope < data.second.size(); slope++) {
        auto part_result = 0;
        auto [dx, dy]    = data.second[slope];
        int x            = 0;
        for (int y = 0; y < trees.size(); y += dy) {
            if (trees[y][x] == '#') {
                part_result += 1;
            }
            x = (x + dx) % (int)trees[0].size();
        }
        result *= part_result;
    }
    return result;
}

int main(int argc, char **argv) {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 3;

    auto args = std::span(argv, size_t(argc));

    std::pair<std::vector<std::string>, std::vector<std::pair<int, int>>> data;

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
        data.first.push_back(line);
    }

    data.second.push_back({3, 1});
    data.second.push_back({1, 1});
    data.second.push_back({5, 1});
    data.second.push_back({7, 1});
    data.second.push_back({1, 2});
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    return 0;
}
