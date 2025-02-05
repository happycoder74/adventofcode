#include "aoc_timer.hpp"
#include <filesystem>
#include <format>
#include <fstream>
#include <span>
#include <string>
#include <unordered_set>
#include <vector>

struct Input {
    std::vector<int>        data;
    std::unordered_set<int> s;
};

int solve_part_1(const struct Input &data) {
    const int target_value = 2020;

    for (auto &c : data.data) {
        if (data.s.contains(target_value - c))
            return c * (target_value - c);
    }

    return 0;
}

int solve_part_2(const struct Input &data) {
    const int target_value = 2020;

    for (auto &num1 : data.data) {
        auto remaining = target_value - num1;
        for (auto &num2 : data.data) {
            if (num2 > remaining)
                continue;
            if (data.s.contains(remaining - num2))
                return num1 * num2 * (remaining - num2);
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    std::string           filename;
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));
    const int             year = 2020;
    const int             day  = 1;
    struct Input          data = {std::vector<int>(), std::unordered_set<int>()};

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

    std::ifstream ifs(filepath / std::filesystem::path(std::format("{}/{:02d}", year, day)) / std::filesystem::path(filename));
    std::string   line;
    while (std::getline(ifs, line)) {
        data.data.push_back(std::stoi(line));
        data.s.insert(stoi(line));
    }

    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    return 0;
}
