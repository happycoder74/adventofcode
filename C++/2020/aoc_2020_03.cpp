#include "aoc_timer.hpp"
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <ranges>
#include <span>
#include <string>
#include <vector>

auto solve_part_1(const std::pair<std::vector<std::string>, std::vector<std::pair<int, int>>> &data) -> int {
    auto result   = 0;
    auto [dx, dy] = data.second[0];
    auto trees    = data.first;
    int  x        = 0;
    for (std::size_t y = 0; y < trees.size(); y += dy) {
        if (trees[y][x] == '#') {
            result += 1;
        }
        x = (x + dx) % (int)trees[0].size();
    }
    return result;
}

auto solve_part_2(const std::pair<std::vector<std::string>, std::vector<std::pair<int, int>>> &data) -> std::uint64_t {
    std::uint64_t result = 1;
    auto          trees  = data.first;
    for (auto [dx, dy] : data.second) {
        auto part_result = 0;
        int  x           = 0;
        for (size_t y = 0; y < trees.size(); y += dy) {
            if (trees[y][x] == '#') {
                part_result += 1;
            }
            x = (x + dx) % (int)trees[0].size();
        }
        result *= part_result;
    }
    return result;
}

auto main(int argc, char **argv) -> int {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 3;

    auto args = std::span(argv, size_t(argc));

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

    auto first  = std::views::istream<std::string>(ifs) | std::ranges::to<std::vector>();
    auto second = std::vector<std::pair<int, int>>{
        {3, 1},
        {1, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    };
    auto data = std::make_pair(first, second);

    std::cout << std::format("{:=<55}\n", "");
    std::cout << std::format("Solution for {:d}, day {:02d}\n", year, day);
    std::cout << std::format("{:-<55}\n", "");
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    std::cout << std::format("{:-<55}\n", "");

    return 0;
}
