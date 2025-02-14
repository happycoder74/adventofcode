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

std::vector<int> clean_input(const std::vector<std::string> &instructions) {
    std::vector<int> return_instructions;

    return_instructions.reserve(instructions.size());

    for (auto &row : instructions) {
        return_instructions.push_back(std::stoi(row));
    }

    return return_instructions;
}

int solve_part_1(const std::vector<int> &instructions) {

    auto fuel = instructions | std::views::transform([](const int &mass) -> int { return mass / 3 - 2; });

    auto result = std::reduce(fuel.begin(), fuel.end());
    return result;
}

int solve_part_2(const std::vector<int> &instructions) {

    auto fuel = instructions | std::views::transform([](const int &mass) -> int { return fuel_cost(mass); });

    auto result = std::reduce(fuel.begin(), fuel.end());
    return result;
}

void solve_all(const std::vector<std::string> &instructions) {
    std::vector<int> parsed = clean_input(instructions);
    aoc::timer(1, solve_part_1, parsed);
    aoc::timer(2, solve_part_2, parsed);
}

int main(int argc, char **argv) {
    std::string   filename;
    constexpr int year = 2019;
    constexpr int day  = 1;

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

    aoc::io::header(year, day);
    aoc::timer(0, solve_all, instructions, false);

    return 0;
}
