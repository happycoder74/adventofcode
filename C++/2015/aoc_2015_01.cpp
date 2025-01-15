#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>

using Clock    = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double>;

int solve_part_1(std::string &instructions) {
    auto rng = instructions | std::views::transform([](auto &c) { return c == ')' ? -1 : 1; }) | std::views::common;
    return std::reduce(rng.begin(), rng.end());
}

int solve_part_2(std::string &instructions) {
    int level   = 0;
    int counter = 0;
    for (auto ch : instructions) {
        ch == '(' ? level++ : level--;
        counter++;
        if (level == -1) {
            return counter;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    std::int16_t  level   = 0;
    std::uint16_t counter = 0;
    std::string   filename;

    bool basement_found = false;

    const int year = 2015;
    const int day  = 1;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    std::vector<std::string> line = aoc::io::get_input_list<std::string>(filename, year, day);

    auto start_1  = Clock::now();
    auto result_1 = solve_part_1(line[0]);
    auto end_1    = Clock::now();

    auto start_2  = Clock::now();
    auto result_2 = solve_part_2(line[0]);
    auto end_2    = Clock::now();

    auto elapsed_part_1 = aoc::convert_duration(end_1 - start_1);
    auto elapsed_part_2 = aoc::convert_duration(end_2 - start_2);

    aoc::io::header(year, day);
    std::cout << "Part 1 answer: " << std::format("{:<20}", result_1) << std::format("{:>20}", elapsed_part_1) << '\n';
    std::cout << "Part 2 answer: " << std::format("{:<20}", result_2) << std::format("{:>20}", elapsed_part_2) << '\n';

    return 0;
}
