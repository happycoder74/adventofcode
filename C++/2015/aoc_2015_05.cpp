#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <ranges>
#include <regex>
#include <string>
#include <vector>

auto solve_part_1(const std::vector<std::string> &data) -> int {
    std::regex regex_wovel("[aeiou].*[aeiou].*[aeiou]");
    std::regex regex_double_letter("(.)\\1");
    std::regex regex_invalid("(ab|cd|pq|xy)");

    auto rng = data //
               | std::views::filter([&](const auto &line) {
                     return (                                            //
                         std::regex_search(line, regex_wovel) &&         //
                         std::regex_search(line, regex_double_letter) && //
                         !std::regex_search(line, regex_invalid)         //
                     );
                 });
    return int(std::distance(rng.begin(), rng.end()));
}

auto solve_part_2(const std::vector<std::string> &data) -> int {
    std::regex regex_pairs("(..).*\\1");
    std::regex regex_repeat("(.).\\1");
    auto       rng = data //
               | std::views::filter([&](const auto &line) {
                     return (                                    //
                         std::regex_search(line, regex_pairs) && //
                         std::regex_search(line, regex_repeat));
                 });
    return int(std::distance(rng.begin(), rng.end()));
}

void solve_all(const std::vector<std::string> &data) {
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
}

auto main(int argc, char **argv) -> int {
    std::string filename;

    constexpr int year = 2015;
    constexpr int day  = 5;

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

    std::vector<std::string> data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);

    return 0;
}
