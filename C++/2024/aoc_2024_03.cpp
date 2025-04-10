#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <span>
#include <string>
#include <vector>

auto solve_part_1(const std::vector<std::string> &instructions) {
    auto result = 0;
    return result;
}

auto solve_part_2(const std::vector<std::string> &instructions) {
    auto result = 0;
    return result;
}

auto solve_all(const std::vector<std::string> &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}

int main(int argc, char **argv) {
    std::string filename;

    constexpr int year = 2024;
    constexpr int day  = 3;

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

    auto instructions = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
