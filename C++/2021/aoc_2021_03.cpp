#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

auto solve_part_1(const std::vector<std::string> &input) -> int {
    unsigned width = input[0].length();
    unsigned count = input.size();

    std::vector<unsigned int> counter(width, 0);

    // clang-format off
#ifdef __cpp_lib_ranges_enumerate
    auto var = std::ranges::fold_left(
            input,
            counter,
            [](auto vec, auto string) {
                auto count_vec = string | std::views::transform([](auto &c) { return c == '1'; });
                std::ranges::transform(vec, count_vec, vec.begin(), [](const auto &v1, const auto &v2) {
                        return v1 + v2;
                        });
                return vec;
            })
        | std::views::reverse
        | std::views::enumerate
        | std::views::transform([&count](auto val) {
            auto &[i, bit] =  val;
            return (bit >= count / 2) << i;
        })
        | std::views::common;
#else
    auto rng = std::ranges::fold_left(
            input,
            counter,
            [](auto vec, auto string) {
                auto count_vec = string | std::views::transform([](auto &c) { return c == '1'; });
                for (std::size_t i = 0; i < vec.size(); i++) {
                    vec[i] += count_vec[i];
                }
                return vec;
            })
        | std::views::reverse | std::ranges::to<std::vector>();
    auto var = std::views::zip(std::views::iota(0), rng)
        | std::views::transform([&count](auto val) {
            auto &[i, bit] =  val;
            return (bit >= count / 2) << i;
        })
        | std::views::common;
#endif
    // clang-format on

    auto gamma   = std::reduce(var.begin(), var.end());
    auto epsilon = ((1 << width) - 1) ^ gamma;

    return gamma * epsilon;
}

void solve_all(const std::vector<std::string> &data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data);
    }
}

auto main(int argc, char *argv[]) -> int {
    std::vector<std::string> data;

    constexpr int year = 2021;
    constexpr int day  = 3;

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
