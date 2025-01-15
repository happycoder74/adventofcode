#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

int solve_part_1(const std::vector<std::string> &input) {
    unsigned width = input[0].length();
    unsigned count = input.size();

    std::vector<std::int32_t> counter(width, 0);

    // clang-format off
    auto var = std::ranges::fold_left(
        input.begin(),
        input.end(),
        counter,
        [](auto vec, auto string) {
            auto count_vec = string | std::views::transform([](auto &c) { return c == '1'; });
            for (std::size_t i = 0; i < vec.size(); i++) {
                vec[i] += count_vec[i];
            }
            return vec;
        })
        | std::views::reverse
        | std::views::enumerate
        | std::views::transform([&count](auto val) {
            unsigned int i, bit;
            std::tie(i, bit) = val;
            return (bit >= count / 2) << i;
        })
        | std::views::common;
    // clang-format on

    auto gamma   = std::reduce(var.begin(), var.end());
    auto epsilon = ((1 << width) - 1) ^ gamma;

    return gamma * epsilon;
}

void *solve_all(const std::vector<std::string> &data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data, 1);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> data;

    int year = 2021;
    int day  = 3;

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
    aoc::timer(0, solve_all, data, 0);

    return 0;
}
