#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

std::string solve_part_1(std::vector<std::string> instructions) {
    std::string return_string;
    return return_string;
}

std::string solve_part_2(std::vector<std::string> instructions) {
    std::string return_string;
    return return_string;
}

std::string solve_all(std::vector<std::string> instructions) {
    aoc::timer<std::string>(1, solve_part_1, instructions, true);
    aoc::timer<std::string>(2, solve_part_2, instructions, true);

    return std::string("");
}

int main(int argc, char **argv) {
    std::string              filename;
    std::vector<std::string> instructions;

    filename = argc > 1 ? argv[1] : "input.txt";

    instructions = aoc::get_input_list<std::string>(filename, 2024, 3);

    aoc::timer<std::string>(0, solve_all, instructions, false);

    return 0;
}
