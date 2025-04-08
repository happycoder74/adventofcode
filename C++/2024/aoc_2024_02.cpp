#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

auto parse_instructions(const std::vector<std::string> &instructions) {
    auto return_vector = instructions //
                         | std::views::transform([](const auto &line) -> std::vector<int> {
                               std::vector<int>  vec{};
                               std::stringstream ss{line};
                               std::string       str{};
                               while (std::getline(ss, str, ' ')) {
                                   vec.push_back(std::stoi(str));
                               }
                               return vec;
                           }) //
                         | std::ranges::to<std::vector>();
    return return_vector;
}

auto validate(const std::vector<int> &vec) -> bool {

    auto diffs = [](const auto &p) -> int {
        auto &[a, b] = p;
        return (b - a);
    };
    auto v2 = std::views::zip(vec, vec | std::views::drop(1)) | std::views::transform(diffs);

    auto is_ok = std::ranges::all_of(v2, [](const int a) -> bool {
        auto c = std::abs(a);
        return ((1 <= c) && (c <= 3));
    });

    auto is_increasing = std::ranges::is_sorted(vec);
    auto is_decreasing = std::ranges::is_sorted(vec | std::views::reverse);

    return (is_ok && (is_increasing || is_decreasing));
}

auto solve_part_1(const std::vector<std::vector<int>> &instructions) -> int {
    auto result = static_cast<int>(std::ranges::count_if(instructions, validate));
    return result;
}

auto solve_part_2(const std::vector<std::vector<int>> &instructions) -> int {
    auto result = std::ranges::count_if(instructions, [](const std::vector<int> &vec) -> int {
        return (validate(vec) || std::ranges::any_of(std::views::iota(0, static_cast<int>(vec.size())), [&vec](const auto i) {
                    std::vector tmp_vec{vec};
                    tmp_vec.erase(tmp_vec.begin() + i);
                    return validate(tmp_vec);
                }));
    });
    return static_cast<int>(result);
}

void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 2;

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
