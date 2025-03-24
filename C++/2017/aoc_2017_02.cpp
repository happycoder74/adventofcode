#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

namespace aoc_2017_02 {

auto transform_input(const auto &data) {

    auto lines = data //
                 | std::views::transform([](const auto &dataline) {
                       auto line = aoc::string::split(dataline, '\t') //
                                   | std::views::transform([](const auto &num) {
                                         return std::stoi(num);
                                     }) //
                                   | std::ranges::to<std::vector>();
                       return line;
                   }) //
                 | std::ranges::to<std::vector>();

    return lines;
}

auto solve_part_1(const auto &lines) -> int {

    auto rng = lines //
               | std::views::transform([](const auto &line) {
                     auto [min, max] = std::ranges::minmax_element(line);
                     return *max - *min;
                 });

    auto checksum = std::reduce(rng.begin(), rng.end());
    return checksum;
}

auto solve_part_2(const auto &lines) -> int {

    auto rng = lines //
               | std::views::transform([](const auto &line) {
                     auto rng2 = std::views::cartesian_product(line, line) //
                                 | std::views::filter([](const auto &v) {
                                       auto &[num1, num2] = v;
                                       return ((num2 != num1) && ((num1 % num2) == 0));
                                   }) //
                                 | std::views::transform([](const auto &v) {
                                       auto &[num1, num2] = v;
                                       return num1 / num2;
                                   });
                     return std::reduce(rng2.begin(), rng2.end());
                 });
    auto result = std::reduce(rng.begin(), rng.end());
    return result;
}

void solve_all(const auto &data) {
    auto lines = aoc::timer(aoc_2017_02::transform_input<decltype(data)>, data, "Preparation time:");

    aoc::timer(1, aoc_2017_02::solve_part_1<decltype(lines)>, lines);
    aoc::timer(2, aoc_2017_02::solve_part_2<decltype(lines)>, lines);
}
} // namespace aoc_2017_02

int main(int argc, char **argv) {
    std::string   filename;
    constexpr int year = 2017;
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

    auto data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(aoc_2017_02::solve_all<decltype(data)>, data);

    return 0;
}
