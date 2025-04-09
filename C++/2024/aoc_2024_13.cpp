#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

template <class T>
auto divmod(T &&a, T &&b) -> std::pair<T, T> {
    return {a / b, a % b};
}

using Equation = std::vector<int>;
[[nodiscard]] auto parse_instructions(const std::vector<std::string> &instructions) -> std::vector<Equation> {
    auto rng = instructions                       //
               | std::views::split(std::string{}) //  -> vec<vec<string>>
               | std::views::transform([](const auto &group) {
                     auto rng = group //
                                | std::views::transform([](const auto &substring) {
                                      auto numbers = substring //
                                                     | std::views::filter([](const auto &c) {
                                                           return std::isdigit(c) || (c == ',');
                                                       }) //
                                                     | std::ranges::to<std::string>();
                                      return numbers;
                                  });
                     return rng;
                 }) //
               | std::views::transform([](const auto group) {
                     auto int_range = group // group = vec<std::string>
                                      | std::views::transform([](const auto &substring) {
                                            auto nn = substring                //
                                                      | std::views::split(',') //
                                                      | std::views::transform([i = 0](const auto &s) mutable {
                                                            auto str           = std::string(s.begin(), s.end());
                                                            auto return_string = std::format("'{}' {} [{}]", str, std::stoi(str), i++);
                                                            return std::stoi(str);
                                                        }); //
                                            return nn | std::ranges::to<std::vector>();
                                        });
                     return int_range;
                 }) //
               | std::views::transform([](const auto &subrange) {
                     auto joined_range = subrange           //
                                         | std::views::join //
                                         | std::ranges::to<std::vector>();
                     return joined_range;
                 });
    auto vec = std::vector<Equation>{};
    std::ranges::transform(rng, std::back_inserter(vec), [](const auto &r) {
        auto v = std::vector<int>(r.begin(), r.end());
        return v;
    });
    return vec;
}

[[nodiscard]] auto solver(const std::vector<Equation> &instructions, uint64_t delta) -> uint64_t {
    auto result = uint64_t{};
    for (auto &equation : instructions) {
        int64_t x0 = equation[0];
        int64_t y0 = equation[1];
        int64_t x1 = equation[2];
        int64_t y1 = equation[3];
        int64_t cx = equation[4] + delta;
        int64_t cy = equation[5] + delta;

        auto [a_presses, a_remainder] = divmod(cx * y1 - cy * x1, y1 * x0 - x1 * y0);
        if (a_remainder != 0)
            continue;
        auto [b_presses, b_remainder] = divmod(-cx * y0 + cy * x0, y1 * x0 - x1 * y0);
        if (b_remainder != 0)
            continue;

        result += 3 * a_presses + b_presses;
    }
    return result;
}

[[nodiscard]] auto solve_part_1(const std::vector<Equation> &instructions) -> uint32_t {
    return solver(instructions, 0);
}

[[nodiscard]] auto solve_part_2(const std::vector<Equation> &instructions) -> uint64_t {
    constexpr uint64_t delta = 10000000000000;
    return solver(instructions, delta);
}
void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 13;

    auto args = std::span(argv, argc);
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
