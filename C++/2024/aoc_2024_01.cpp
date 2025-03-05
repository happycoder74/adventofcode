#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

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
    std::unordered_map<int, int> left, right;
    auto &[li, ri] = instructions;
    for (auto [p1, p2] : std::views::zip(li, ri)) {
        left[p1] += 1;
        right[p2] += 1;
    }

    auto rng = left | std::views::transform([&right](auto c) { return c.first * c.second * right[c.first]; });

    return std::reduce(rng.begin(), rng.end());
}

auto solve_all(const std::vector<std::string> &instructions) {
    auto parsed = parse_data(instructions);
    aoc::timer(1, solve_part_1, parsed);
    aoc::timer(2, solve_part_2, parsed);
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

    auto instructions = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
