#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <chrono>
#include <cstring>
#include <map>
#include <ranges>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

int solve_part_1(const std::tuple<std::vector<int>, std::vector<int>> &instructions) {
    auto [left, right] = instructions;
    auto sum           = 0;

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (std::pair<int &, int &> pair : std::views::zip(left, right)) {
        sum += std::abs(pair.first - pair.second);
    }
    return sum;
}

int solve_part_2(const std::tuple<std::vector<int>, std::vector<int>> &instructions) {
    int                result = 0;
    std::map<int, int> left, right;
    for (auto p : std::views::zip(std::get<0>(instructions), std::get<1>(instructions))) {
        left[std::get<0>(p)] += 1;
        right[std::get<1>(p)] += 1;
    }

    for (auto it = left.begin(); it != left.end(); it++) {
        result += it->first * it->second * right[it->first];
    }

    return result;
}

auto solve_all(const std::tuple<std::vector<int>, std::vector<int>> &instructions) {
    aoc::timer(1, solve_part_1, instructions, true);
    aoc::timer(2, solve_part_2, instructions, true);

    return 0;
}

auto parse_data(const std::vector<std::string> &instructions) {
    std::vector<int> left, right;

    for (auto &line : instructions) {
        std::string l(line.begin(), line.begin() + line.find_first_of(' '));
        std::string r(line.begin() + line.find_last_of(' ') + 1, line.end());
        left.push_back(std::stoi(l));
        right.push_back(std::stoi(r));
    }
    return std::tuple{left, right};
}

int main(int argc, char **argv) {
    std::string              filename;
    std::vector<std::string> instructions;
    constexpr int            year = 2024;
    constexpr int            day  = 1;

    if (argc > 1) {
        if (!std::strcmp(argv[1], "--test")) {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = argc > 1 ? argv[1] : "input.txt";
    }

    instructions = aoc::io::get_input_list<std::string>(filename, year, day);

    auto parsed = parse_data(instructions);

    aoc::timer(0, solve_all, parsed, false);

    return 0;
}
