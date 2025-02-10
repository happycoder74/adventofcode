#include "aoc_timer.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

enum {
    ROUNDS_PART_1 = 2020,
    ROUNDS_PART_2 = 30000000
};

int solver(const std::vector<int> &instructions, const int rounds) {
    std::vector<int> numbers(rounds, -1);
    int              turn      = 1;
    int              last_turn = 0;

    for (auto &v : instructions) {
        numbers[v] = turn++;
    }
    int next_number = instructions.back();
    for (turn = turn - 1; turn < rounds; turn++) {
        last_turn            = numbers[next_number];
        numbers[next_number] = turn;
        if (last_turn != -1)
            next_number = turn - last_turn;
        else
            next_number = 0;
    }
    std::cout << std::count(numbers.begin(), numbers.end(), -1) << " slots unallocated" << '\n';
    std::cout << "Max element is " << *std::max_element(numbers.begin(), numbers.end()) << '\n';
    return next_number;
}

int solve_part_1(const std::vector<int> &instructions) {
    return solver(instructions, ROUNDS_PART_1);
}

int solve_part_2(const std::vector<int> &instructions) {
    return solver(instructions, ROUNDS_PART_2);
}

int main(void) {
    std::string      test_input = "0,3,6";
    std::string      input      = "9,12,1,4,17,0,18";
    std::vector<int> numbers;

    for (auto &c : input) {
        if (c == ',')
            c = ' ';
    }

    std::stringstream ss{input};
    int               number = 0;
    while (ss >> number) {
        numbers.push_back(number);
    }

    aoc::timer(1, solve_part_1, numbers);
    aoc::timer(2, solve_part_2, numbers);

    return 0;
}
