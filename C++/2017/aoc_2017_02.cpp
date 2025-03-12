#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

namespace aoc_2017_02 {

auto transform_input(const std::vector<std::string> &data) {

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

auto solve_part_1(const std::vector<std::vector<int>> &lines) -> int {

    auto rng = lines //
               | std::views::transform([](const auto &line) {
                     auto [min, max] = std::ranges::minmax_element(line);
                     return *max - *min;
                 });
    auto checksum = std::reduce(rng.begin(), rng.end());
    return checksum;
}

auto solve_part_2(const std::vector<std::vector<int>> &lines) -> int {

    auto rng = lines //
               | std::views::transform([](const auto &line) {
                     int checksum = 0;
                     for (auto &num : line) {
                         for (auto &nn : line) {
                             if ((nn != num) && ((num % nn) == 0)) {
                                 checksum += num / nn;
                             }
                         }
                     }
                     return checksum;
                 });
    auto result = std::reduce(rng.begin(), rng.end());
    return result;
}

void solve_all(const std::vector<std::string> &data) {
    auto lines = aoc::timer(aoc_2017_02::transform_input, data, "Preparation time:");

    aoc::timer(1, aoc_2017_02::solve_part_1, lines);
    aoc::timer(2, aoc_2017_02::solve_part_2, lines);
}
} // namespace aoc_2017_02

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2017;
    const int   day  = 2;

    std::vector<std::string> data;

    auto args = std::span(argv, argc);
    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(args[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    aoc::io::header(year, day);
    aoc::timer(aoc_2017_02::solve_all, data);

    return 0;
}
