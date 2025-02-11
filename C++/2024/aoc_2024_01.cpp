#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

auto solve_part_1(const std::pair<std::vector<int>, std::vector<int>> &instructions) -> int {
    auto [left, right] = instructions;

    std::ranges::sort(left);
    std::ranges::sort(right);

    auto rng    = std::views::zip(left, right) | std::views::common;
    auto result = rng //
                  | std::views::transform([](const auto &p) {
                        auto [first, second] = p;
                        return std::abs(first - second);
                    }) //
                  | std::views::common;
    return std::reduce(result.begin(), result.end());
}

auto solve_part_2(const std::pair<std::vector<int>, std::vector<int>> &instructions) -> int {
    std::map<int, int> left, right;
    for (auto p : std::views::zip(std::get<0>(instructions), std::get<1>(instructions))) {
        left[std::get<0>(p)] += 1;
        right[std::get<1>(p)] += 1;
    }

    auto rng = left | std::views::transform([&right](auto c) { return c.first * c.second * right[c.first]; });

    return std::reduce(rng.begin(), rng.end());
}

auto solve_all(const std::pair<std::vector<int>, std::vector<int>> &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}

auto parse_data(const std::vector<std::string> &instructions) {
    std::vector<int> left, right;

    for (auto &line : instructions) {
        std::stringstream ss{line};
        int               l = 0, r = 0;
        ss >> l >> r;
        left.push_back(l);
        right.push_back(r);
    }
    return std::pair{left, right};
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 1;

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

    std::filesystem::path filepath{std::getenv("AOC_DATA_LOCATION")};
    filepath = filepath / std::format("{}", year) / std::format("{:02d}", day) / filename;
    std::ifstream ifs{filepath};

    std::vector<std::string> instructions;
    for (std::string line; std::getline(ifs, line);) {
        instructions.push_back(line);
    }
    auto parsed = parse_data(instructions);

    aoc::io::header(year, day);
    aoc::timer(solve_all, parsed);

    return 0;
}
