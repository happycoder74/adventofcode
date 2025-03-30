#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

using Equation = std::pair<size_t, std::vector<size_t>>;
auto parse_instructions(const std::vector<std::string> &instructions) -> std::vector<Equation> {
    std::vector<Equation> vec{};
    vec.reserve(instructions.size());
    std::ranges::transform(instructions, std::back_inserter(vec), [](const auto &arg) -> Equation {
        auto                n            = std::stoull(arg);
        auto                start        = std::find(arg.begin(), arg.end(), ':');
        auto                s            = std::string(start + 1, arg.end());
        auto                split_string = aoc::string::split(s, ' ');
        std::vector<size_t> op_vec{};
        std::ranges::for_each(split_string, [&op_vec](const auto &s) {
            op_vec.emplace_back(std::stoull(s));
        });

        return Equation{n, std::move(op_vec)};
    });

    return vec;
}

auto solver(const std::vector<Equation> &instructions, auto &operators) {
    size_t result = 0;
    for (auto &eq : instructions) {
        auto [expected_result, operands] = eq;
        const auto op_variations         = static_cast<size_t>(std::pow(operators.size(), operands.size() - 1));
        for (auto index : std::ranges::iota_view(0, int(op_variations))) {
            auto       i                 = index;
            const auto calculated_result = std::ranges::fold_left(operands.begin() + 1, operands.end(), operands.front(), [&](const auto &a, const auto &b) -> size_t {
                auto v = (std::exchange(i, i / operators.size()) % operators.size());
                return operators[v](a, b);
            });
            if (expected_result == calculated_result) {
                result += expected_result;
                break;
            }
        }
    }
    return result;
}

auto solve_part_1(const std::vector<Equation> &instructions) -> size_t {
    using Op       = std::function<size_t(const size_t, const size_t)>;
    auto operators = std::array{Op{[](const size_t a, const size_t b) {
                                    return a + b;
                                }},
                                Op{[](const size_t &a, const size_t &b) {
                                    return a * b;
                                }}};

    return solver(instructions, operators);
}

auto solve_part_2(const std::vector<Equation> &instructions) -> size_t {
    using Op       = std::function<size_t(const size_t, const size_t)>;
    auto operators = std::array{Op{[](const size_t a, const size_t b) {
                                    return a + b;
                                }},
                                Op{[](const size_t &a, const size_t &b) {
                                    return a * b;
                                }},
                                Op{[](const size_t &a, const size_t &b) -> size_t {
                                    // return std::size_t{10} * a * static_cast<std::size_t>(pow(10, floor(log10(std::max(b, std::size_t{1}))))) + b;
                                    return a * size_t(pow(10, floor(log10(b)) + 1)) + b;
                                }}};

    return solver(instructions, operators);
}

void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 7;

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
