#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

auto solve_part_1(const std::vector<std::vector<int>> &instructions) {
    auto result = 0;
    return result;
}

auto solve_part_2(const std::vector<std::vector<int>> &instructions) {
    auto result = 0;
    return result;
}

auto solve_all(const std::vector<std::vector<int>> &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}

int main(int argc, char **argv) {
    std::string filename;

    constexpr int year = 2024;
    constexpr int day  = 2;

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
    std::ifstream ifs{filename};
    std::string   line{};

    std::vector<std::vector<int>> instructions;
    while (std::getline(ifs, line)) {
        auto vec = line | std::views::split(' ') | std::views::transform([](auto &&c) {
                       return std::stoi(std::string(c.begin(), c.end()));
                   }) |
                   std::ranges::to<std::vector<int>>();
        instructions.push_back(vec);
    }

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
