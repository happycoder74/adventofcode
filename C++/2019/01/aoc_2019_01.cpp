#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

static int fuel_cost(int fuel) {
    fuel = (fuel / 3) - 2;
    if (fuel < 0) {
        return 0;
    }
    return fuel + fuel_cost(fuel);
}

std::vector<int> clean_input(std::vector<std::string> instructions) {
    std::vector<int> return_instructions;
    for (auto &row : instructions) {
        return_instructions.push_back(std::stoi(row));
    }

    return return_instructions;
}

int solve_part_1(std::vector<int> instructions) {

    auto fuel = instructions | std::views::transform([](const int &mass) -> int { return mass / 3 - 2; });

    auto result = std::reduce(fuel.begin(), fuel.end());
    return result;
}

int solve_part_2(std::vector<int> instructions) {

    auto fuel = instructions | std::views::transform([](const int &mass) -> int { return fuel_cost(mass); });

    auto result = std::reduce(fuel.begin(), fuel.end());
    return result;
}

std::string solve_all(std::vector<std::string> instructions) {
    std::vector<int> parsed = clean_input(instructions);
    aoc::timer<int>(1, solve_part_1, parsed, true);
    aoc::timer<int>(2, solve_part_2, parsed, true);

    return std::string("");
}

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2019;
    const int   day = 1;

    std::vector<std::string> instructions;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    instructions = aoc::io::get_input_list<std::string>(filename, year, day);

    std::cout << "Solution for " << std::format("{:d}/{:02d}", year, day) << std::endl;
    aoc::timer<std::string>(0, solve_all, instructions, false);

    return 0;
}
