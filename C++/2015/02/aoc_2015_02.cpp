#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <vector>

namespace aoc_2015_02 {

std::vector<std::vector<int>> parse_data(const std::vector<std::string> &data) {
    auto rng = data | std::views::transform([](const auto &row) -> std::vector<int> {
                   auto to_int = [](const auto &in) { return std::stoi(std::string(in.begin(), in.end())); };
                   auto parts = row | std::views::split(std::string{'x'}) | std::views::transform(to_int);

                   auto wlh = std::vector(parts.begin(), parts.end());
                   return wlh;
               });
    return std::vector(rng.begin(), rng.end());
}

int solve_part_1(const std::vector<std::vector<int>> &data) {
    auto rng = data | std::views::transform([](const auto &row) -> int {
                   std::vector<int> area(2);
                   std::ranges::partial_sort_copy(row, area, std::less<>{});
                   auto wlh = std::vector(row.begin(), row.end());
                   return 2 * wlh[0] * wlh[1] + 2 * wlh[1] * wlh[2] + 2 * wlh[2] * wlh[0] + area[0] * area[1];
               }) |
               std::views::common;

    return std::reduce(rng.begin(), rng.end());
}

int solve_part_2(const std::vector<std::vector<int>> &data) {
    auto rng = data | std::views::transform([](const auto &row) -> int {
                   std::vector<int> area(2);
                   std::ranges::partial_sort_copy(row, area, std::less<>{});
                   return 2 * area[0] + 2 * area[1] + std::reduce(row.begin(), row.end(), 1, std::multiplies<int>());
               }) |
               std::views::common;

    return std::reduce(rng.begin(), rng.end());
}

int solve_all(const std::vector<std::string> &data) {
    auto parsed_data = parse_data(data);
    aoc::timer(1, aoc_2015_02::solve_part_1, parsed_data);
    aoc::timer(2, aoc_2015_02::solve_part_2, parsed_data);

    return 0;
}
} // namespace aoc_2015_02

int main(int argc, char **argv) {
    std::vector<std::string> data;

    char sourcefile[20];
    int  year = 2015;
    int  day = 2;

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
    aoc::timer(0, aoc_2015_02::solve_all, data, 0);

    return 0;
}
