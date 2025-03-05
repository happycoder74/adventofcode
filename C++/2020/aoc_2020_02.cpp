#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <span>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

auto parse_data(const std::vector<std::string> &data) -> std::vector<std::tuple<int, int, char, std::string>> {
    auto rng = data //
               | std::views::transform([](const auto &line) {
                     std::stringstream ss{line};
                     int               a = 0, b = 0;
                     char              letter = 0, tmp = 0;
                     std::string       passwd;
                     ss >> a >> tmp >> b >> letter >> tmp >> passwd;
                     return std::make_tuple(a, b, letter, passwd);
                 }) //
               | std::ranges::to<std::vector>();
    return rng;
}
auto solve_part_1(const std::vector<std::tuple<int, int, char, std::string>> &data) -> int {
    auto count = data //
                 | std::views::transform([](auto &item) {
                       auto [count_start, count_end, letter, passwd] = item;

                       auto num_chars = std::count(passwd.begin(), passwd.end(), letter);
                       return ((count_start <= num_chars) && (num_chars <= count_end)) ? 1 : 0;
                   });
    return std::reduce(count.begin(), count.end());
}

auto solve_part_2(const std::vector<std::tuple<int, int, char, std::string>> &data) -> int {
    auto count = data //
                 | std::views::transform([](auto &item) {
                       auto [first_pos, second_pos, letter, passwd] = item;
                       return ((passwd[first_pos - 1] == letter) != (passwd[second_pos - 1] == letter)) ? 1 : 0;
                   });
    return std::reduce(count.begin(), count.end());
}

void solve_all(const std::vector<std::string> &data) {
    auto parsed_data = aoc::timer(parse_data, data, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_data);
    aoc::timer(2, solve_part_2, parsed_data);
}

auto main(int argc, char **argv) -> int {
    std::string filename;
    const int   year = 2020;
    const int   day  = 2;

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

    auto data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);
    return 0;
}
