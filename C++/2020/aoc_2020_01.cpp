#include "aoc_timer.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <span>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

int solve_part_1(const std::pair<std::vector<int>, std::unordered_set<int>> &data) {
    constexpr int target_value = 2020;

    for (auto &c : data.first) {
        if (data.second.contains(target_value - c))
            return c * (target_value - c);
    }

    return 0;
}

int solve_part_2(const std::pair<std::vector<int>, std::unordered_set<int>> &data) {
    constexpr int target_value = 2020;

    for (auto &num1 : data.first) {
        auto remaining = target_value - num1;
        for (auto &num2 : data.first) {
            if (num2 > remaining)
                continue;
            if (data.second.contains(remaining - num2))
                return num1 * num2 * (remaining - num2);
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 1;

    auto                                                 args = std::span(argv, size_t(argc));
    std::pair<std::vector<int>, std::unordered_set<int>> data;

    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    filepath = filepath / std::format("{}/{:02d}", year, day) / filename;
    std::ifstream ifs(filepath);
    std::string   line;
    while (std::getline(ifs, line)) {
        data.first.push_back(std::stoi(line));
        data.second.insert(stoi(line));
    }

    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    return 0;
}
