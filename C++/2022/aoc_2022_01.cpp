#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

namespace day01::calories {
auto max_calories(const std::vector<std::string> &data) -> uint64_t {
    auto by_elf = data | std::views::lazy_split(std::string{}) | std::views::transform([](const auto &elf) -> uint64_t {
                      auto to_unsigned = [](const auto &in) { return std::stoull(in); };

                      auto rng = elf | std::views::transform(to_unsigned) | std::views::common; // std::reduce requires a common range
                      return std::reduce(rng.begin(), rng.end());
                  });
    auto it     = std::ranges::max_element(by_elf);
    return *it; // and return
}
auto top_three(const std::vector<std::string> &data) -> uint64_t {
    auto by_elf = data | std::views::lazy_split(std::string{}) |          // group by elf: range{range{string}}
                  std::views::transform([](const auto &elf) -> uint64_t { // sum up the calories for each elf: range{uint64_t}
                      auto to_unsigned = [](const auto &in) { return std::stoull(in); };
                      auto rng         = elf | std::views::transform(to_unsigned) | std::views::common; // range{string} -> range{uint64_t}
                      return std::reduce(rng.begin(), rng.end());                                       // range{uint64_t} -> uint64_t
                  });
    std::vector<uint64_t> top(3);
    std::ranges::partial_sort_copy(by_elf, top, std::greater<>{});
    return std::reduce(top.begin(), top.end());
}
} // namespace day01::calories

void solve_all(const std::vector<std::string> &data) {
    aoc::timer(1, day01::calories::max_calories, data);
    aoc::timer(2, day01::calories::top_three, data);
}

auto main(int argc, char **argv) -> int {
    std::vector<std::string> data;

    constexpr int year = 2022;
    constexpr int day  = 1;

    auto args = std::span(argv, size_t(argc));
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
    aoc::timer(solve_all, data);

    return 0;
}
