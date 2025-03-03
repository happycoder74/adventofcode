#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

const int multiplier = 10;

const std::array<std::pair<int, std::string>, 18> needles{
    {{1, "one"},
     {2, "two"},
     {3, "three"},
     {4, "four"},
     {5, "five"},
     {6, "six"},
     {7, "seven"},
     {8, "eight"},
     {9, "nine"},
     {1, "1"},
     {2, "2"},
     {3, "3"},
     {4, "4"},
     {5, "5"},
     {6, "6"},
     {7, "7"},
     {8, "8"},
     {9, "9"}}
};

uint32_t solve_part_1(const std::vector<std::string> &data) {
    uint32_t sum = std::accumulate(data.begin(), data.end(), 0, [](int a, const auto &string) {
        uint32_t first  = *std::ranges::find_if(string, [](auto c) { return isdigit(c); }) - '0';
        uint32_t second = *std::ranges::find_if(string | std::views::reverse, [](auto c) { return isdigit(c); }) - '0';
        return a + first * multiplier + second;
    });

    return sum;
}

uint32_t solve_part_2(const std::vector<std::string> &data) {
    // clang-format off
    auto rng = data
            | std::views::transform([](const auto &string) -> int {
                auto first_matches = needles
                        | std::views::filter([&string](const auto &needle) -> bool {
                                return string.find(needle.second) != std::string::npos;
                                })
                        | std::views::transform([&string](const auto &needle) -> std::pair<std::string::size_type, int> {
                                return std::make_pair(string.find(needle.second), needle.first);
                                });
                auto last_matches = needles
                        | std::views::filter([&string](const auto &needle) -> bool {
                                return string.rfind(needle.second) != std::string::npos;
                                })
                        | std::views::transform([&string](const auto &needle) -> std::pair<std::string::size_type, int> {
                                return std::make_pair(string.rfind(needle.second), needle.first);
                                });
        auto first = std::ranges::min_element(first_matches);
        auto last = std::ranges::max_element(last_matches);
        return (*first).second * multiplier + (*last).second;
    });
    //  clang-format on
    auto sum = std::reduce(rng.begin(), rng.end());
    return sum;
}


void solve_all(const std::vector<std::string> &data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data);
        aoc::timer(2, solve_part_2, data);
    }
}

int main(int argc, char **argv) {
    std::vector<std::string> data;

    constexpr int year = 2023;
    constexpr int day  = 1;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(argv[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);

    return 0;
}
