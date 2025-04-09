#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

constexpr auto check_wovel = [](const auto &line) -> bool {
    auto wovels = std::string{"aeiou"};
    auto result = std::accumulate(wovels.begin(), wovels.end(), 0, [&line](const auto a, const auto c) -> int {
        return a + std::count(line.begin(), line.end(), c);
    });
    return result >= 3;
};

constexpr auto check_double_letter = [](const auto &line) -> bool {
    auto zipped = std::views::zip(line, line | std::views::drop(1));
    return std::any_of(zipped.begin(), zipped.end(), [](const auto &p) {
        auto [a, b] = p;
        return a == b;
    });
};

constexpr auto check_no_invalid = [](const auto &line) -> bool {
    auto invalid = std::array<std::string, 4>{"ab", "cd", "pq", "xy"};
    return std::none_of(invalid.begin(), invalid.end(), [&line](const auto &s) {
        return line.find(s) != line.npos;
    });
};

constexpr auto check_pairs = [](const auto &line) -> bool {
    auto zipped     = std::views::zip(line, line | std::views::drop(1));
    auto loop_range = zipped | std::views::reverse | std::views::drop(2) | std::views::reverse | std::views::enumerate;
    auto rev_zipped = zipped | std::views::enumerate | std::views::reverse;

    for (auto p : loop_range) {
        auto [i, pair] = p;
        auto it        = std::find_if(rev_zipped.begin(), rev_zipped.end(), [&pair](const auto &item) {
            auto [index, content] = item;
            return pair == content;
        });
        if (it != rev_zipped.end()) {
            auto [index, content] = *it;
            if (index > i + 1) {
                return true;
            }
        }
    }
    return false;
};

constexpr auto check_repeat = [](const auto &line) -> bool {
    auto zipped = std::views::zip(line, line | std::views::drop(2));
    for (auto [a, b] : zipped) {
        if (a == b) {
            return true;
        }
    }
    return false;
};

auto solve_part_1(const std::vector<std::string> &data) -> int {
    auto rng = data //
               | std::views::filter([&](const auto &line) {
                     return (                         //
                         check_wovel(line) &&         //
                         check_double_letter(line) && //
                         check_no_invalid(line)       //
                     );
                 });
    return int(std::distance(rng.begin(), rng.end()));
}

auto solve_part_2(const std::vector<std::string> &data) -> int {
    auto rng = data //
               | std::views::filter([&](const auto &line) {
                     return (                 //
                         check_pairs(line) && //
                         check_repeat(line));
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
