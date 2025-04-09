#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>

namespace aoc_2017_01 {

auto parse_instructions(const std::string &line) {
    auto vec = line //
               | std::views::transform([](const auto &a) {
                     return a - '0';
                 }) //
               | std::ranges::to<std::vector>();
    return vec;
}

auto solution(const std::vector<int> &line, int step) -> int {
    std::vector<int> line2 = line;
    std::ranges::rotate(line2, line2.begin() + step);

    // clang-format off
    auto result = std::views::zip(line, line2)
       | std::views::transform([](const auto a) -> int {
                      auto [v1, v2] = a;
                      if (v1 == v2) {
                          return v1;
                      }
                      return 0;
                  })
       | std::views::common;
    // clang-format on

    return std::reduce(result.begin(), result.end());
}

auto solve_part_1(const std::vector<int> &line) -> int {
    return solution(line, 1);
}

auto solve_part_2(const std::vector<int> &line) -> int {
    return solution(line, static_cast<int>(line.size()) / 2);
}

auto solve_all(const std::string &line) {
    auto parsed_instructions = parse_instructions(line);
    aoc::timer(1, aoc_2017_01::solve_part_1, parsed_instructions);
    aoc::timer(2, aoc_2017_01::solve_part_2, parsed_instructions);
}
} // namespace aoc_2017_01

int main(int argc, char **argv) {
    std::string filename;

    constexpr int year = 2017;
    constexpr int day  = 1;

    std::vector<std::string> data;

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

    data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(aoc_2017_01::solve_all, data[0]);

    return 0;
}
