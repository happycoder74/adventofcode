#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <array>
#include <ranges>
#include <string>
#include <vector>

auto solve_part_1(const std::vector<std::string> &instructions) -> int {
    int result = 0;

    for (auto [row_index, row] : std::views::zip(std::views::iota(0), instructions)) {
        for (auto [col_index, col] : std::views::zip(std::views::iota(0), row)) {
            if (col != 'X')
                continue;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if ((dr == 0) && (dc == 0))
                        continue;
                    if (((row_index + 3 * dr) < 0) || (int(instructions.size()) <= (row_index + 3 * dr)))
                        continue;
                    if (((col_index + 3 * dc) < 0) || (int(row.size()) <= (col_index + 3 * dc)))
                        continue;
                    if ((instructions[row_index + dr][col_index + dc] == 'M') && (instructions[row_index + 2 * dr][col_index + 2 * dc] == 'A') &&
                        (instructions[row_index + 3 * dr][col_index + 3 * dc] == 'S')) {
                        result++;
                    }
                }
            }
        }
    }
    return result;
}

auto solve_part_2(const std::vector<std::string> &instructions) -> int {
    int                              result = 0;
    const std::array<std::string, 4> pattern{"MMSS", "SMSM", "SSMM", "MSMS"};

    for (auto [row_index, row] : std::views::zip(std::views::iota(1), std::ranges::subrange(instructions.begin() + 1, instructions.end() - 1))) {
        for (auto [col_index, col] : std::views::zip(std::views::iota(1), std::ranges::subrange(row.begin() + 1, row.end() - 1))) {
            if (col != 'A')
                continue;
            auto i = row_index;
            auto j = col_index;

            for (const auto &p : pattern) {
                bool match = (instructions[i - 1][j - 1] == p[0]);
                match      = match && (instructions[i - 1][j + 1] == p[1]);
                match      = match && (instructions[i + 1][j - 1] == p[2]);
                match      = match && (instructions[i + 1][j + 1] == p[3]);
                if (match) {
                    result++;
                    break;
                }
            }
        }
    }
    return result;
}

void solve_all(const std::vector<std::string> &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 4;

    auto args = std::span(argv, argc);
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
