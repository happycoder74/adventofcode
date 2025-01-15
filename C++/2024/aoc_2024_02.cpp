#include <chrono>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

auto solve_part_1(auto instructions) {
    auto result = 0;
    return result;
}

auto solve_part_2(auto instructions) {
    auto result = 0;
    return result;
}

auto solve_all(auto instructions) {
    auto start_1  = Clock::now();
    auto result_1 = solve_part_1(instructions);
    auto stop_1   = Clock::now();
    std::println("Part 1: {:10d} {:10.3f} ms ({})", result_1, std::chrono::round<std::chrono::microseconds>(stop_1 - start_1).count() / 1000., stop_1 - start_1);
    auto start_2  = Clock::now();
    auto result_2 = solve_part_2(instructions);
    auto stop_2   = Clock::now();
    std::println("Part 2: {:10d} {:10.3f} ms ({})", result_2, std::chrono::round<std::chrono::microseconds>(stop_2 - start_2).count() / 1000., stop_2 - start_2);
}

int main(int argc, char **argv) {
    std::vector<std::vector<int>> instructions;
    std::string                   line;

    auto          filename = argc > 1 ? argv[1] : "/home/christian/projects/adventofcode/data/2024/02/input.txt";
    std::ifstream ifs{filename = filename};

    while (std::getline(ifs, line)) {
        auto vec = line | std::views::split(' ') | std::views::transform([](auto &&c) { return std::stoi(std::string(c.begin(), c.end())); }) | std::ranges::to<std::vector<int>>();
        instructions.push_back(vec);
    }

    auto start_1 = Clock::now();
    solve_all(instructions);
    auto stop_1 = Clock::now();
    std::println("Total: {:22.3f} ms ({})", std::chrono::round<std::chrono::microseconds>(stop_1 - start_1).count() / 1000., stop_1 - start_1);

    return 0;
}
