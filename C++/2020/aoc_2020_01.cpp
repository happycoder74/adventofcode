#include "aoc_timer.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <ranges>
#include <span>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

auto solve_part_1(const std::pair<std::vector<int>, std::unordered_set<int>> &data) -> int {
    constexpr int target_value = 2020;

    for (auto &c : data.first) {
        if (data.second.contains(target_value - c))
            return c * (target_value - c);
    }

    return 0;
}

auto solve_part_2(const std::pair<std::vector<int>, std::unordered_set<int>> &data) -> int {
    constexpr int target_value = 2020;

    for (auto &num1 : data.first) {
        auto remaining = target_value - num1;
        for (auto &num2 : data.first) {
            if (num2 > remaining)
                continue;
            if (data.second.contains(remaining - num2))
                return num1 * num2 * (remaining - num2);
        }
    }

    return 0;
}

auto main(int argc, char **argv) -> int {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 1;

    std::string filename;
    const int   year = 2020;
    const int   day  = 1;

    auto                                                 args = std::span(argv, size_t(argc));
    std::pair<std::vector<int>, std::unordered_set<int>> data;

    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    filepath /= filepath / std::format("{}", year) / std::format("{:02d}", day) / filename;

    std::ifstream ifs(filepath);

    auto input{std::views::istream<int>(ifs) | std::ranges::to<std::vector>()};
    auto set{std::unordered_set<int>(input.begin(), input.end())};

    auto data = std::make_pair(input, set);

    std::cout << std::format("{:=<55}\n", "");
    std::cout << std::format("Solution for {:d}, day {:02d}\n", year, day);
    std::cout << std::format("{:-<55}\n", "");
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    std::cout << std::format("{:-<55}\n", "");
    return 0;
}
