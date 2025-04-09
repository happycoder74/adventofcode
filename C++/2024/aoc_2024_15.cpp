#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <exception>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <vector>

using Map   = std::vector<std::string>;
using Moves = std::string;

[[nodiscard]] static auto parse_instructions(const std::vector<std::vector<std::string>> &instructions) -> std::pair<Map, Moves> {
    auto map   = instructions[0];
    auto lines = instructions[1];
    auto moves = std::ranges::fold_left(lines, std::string{}, [](const auto &a, const auto &b) {
        return std::move(a) + b;
    });
    return {map, moves};
}

[[nodiscard]] static auto get_move(const auto &move) {
    switch (move) {
        case '^':
            return std::pair{-1, 0};
            break;
        case 'v':
            return std::pair{1, 0};
            break;
        case '<':
            return std::pair{0, -1};
            break;
        case '>':
            return std::pair{0, 1};
            break;
        default:
            std::cerr << "Should not end up here!" << '\n';
            std::terminate();
    }
}

[[nodiscard]] static auto modify_map(const Map &m) {
    Map new_map{};
    for (const auto &row : m) {
        auto new_row = std::string{};
        for (const auto c : row) {
            if (c == '#') {
                new_row += "##";
            } else if (c == '.') {
                new_row += "..";
            } else if (c == 'O') {
                new_row += "[]";
            } else if (c == '@') {
                new_row += "@.";
            }
        }
        new_map.push_back(std::move(new_row));
    }
    return new_map;
}

[[nodiscard]] static auto locate_robot(const auto &map) -> std::pair<int, int> {
    for (auto row = map.begin(); row != map.end(); ++row) {
        auto col = std::ranges::find(*row, '@');
        if (col != row->end())
            return {static_cast<int>(row - map.begin()), static_cast<int>(col - row->begin())};
    }
    return {-1, -1};
}

[[nodiscard]] auto solve_part_1(const std::pair<Map, Moves> &instructions) -> uint32_t {
    auto map        = instructions.first;
    auto moves      = instructions.second;
    auto [row, col] = locate_robot(map);

    for (const auto move : moves) {
        auto [dy, dx]           = get_move(move);
        auto [new_row, new_col] = std::pair{row + dy, col + dx};
        if (map[new_row][new_col] == '#') {
            continue;
        }
        if (map[new_row][new_col] == 'O') {
            // find if there is a gap to push to
            auto [gap_row, gap_col] = std::pair{new_row + dy, new_col + dx};
            auto check_gap          = [&map](const auto gap_row, const auto gap_col) {
                return (map[gap_row][gap_col] != '#') && (map[gap_row][gap_col] != '.');
            };
            while (check_gap(gap_row, gap_col)) {
                gap_row += dy;
                gap_col += dx;
            }
            if (map[gap_row][gap_col] == '#') {
                continue;
            } else {
                // Shift all towards gap:
                while (!((gap_row == row) && (gap_col == col))) {
                    std::swap(map[gap_row][gap_col], map[gap_row - dy][gap_col - dx]);
                    gap_row -= dy;
                    gap_col -= dx;
                }
            }
        } else {
            std::swap(map[row][col], map[new_row][new_col]);
        }
        row = new_row;
        col = new_col;
    }
#ifndef NDEBUG
    std::ranges::for_each(map, [](const auto &row) {
        std::println("{}", row);
    });
#endif

#ifndef __cpp_lib_ranges_enumerate
    std::println("Using ranged for loop version");
    auto result    = int{};
    auto row_index = size_t{};
    for (const auto &row : map) {
        auto col_index = size_t{};
        for (const auto col : row) {
            if (col == 'O') {
                result += 100 * row_index + col_index;
            }
            ++col_index;
        }
        ++row_index;
    }
#else
    std::println("Using enumerate view version");
    auto row_result = map                     //
                      | std::views::enumerate //
                      | std::views::transform([](const auto &r) {
                            auto [row_index, row] = r;
                            auto by_row           = row           //
                                          | std::views::enumerate //
                                          | std::views::transform([&row_index](const auto c) -> uint64_t {
                                                auto [col_index, col] = c;
                                                if (col == 'O')
                                                    return 100 * row_index + col_index;
                                                return 0;
                                            });
                            return std::reduce(by_row.begin(), by_row.end());
                        });
    auto result = std::reduce(row_result.begin(), row_result.end());
#endif
    return result;
}

[[nodiscard]] auto solve_part_2(const std::pair<Map, Moves> &instructions) -> uint32_t {
    auto map        = modify_map(instructions.first);
    auto moves      = instructions.second;
    auto [row, col] = locate_robot(map);

    for (const auto move : moves) {
        auto [dy, dx]           = get_move(move);
        auto [new_row, new_col] = std::pair{row + dy, col + dx};
        if (map[new_row][new_col] == '#') {
            continue;
        }
        if ((map[new_row][new_col] == '[') || (map[new_row][new_col] == ']')) {
            // find if there is a gap to push to
            auto [gap_row, gap_col] = std::pair{new_row + dy, new_col + dx};
            auto check_gap          = [&map](const auto row, const auto col, const auto dy, const auto dx) {

            };
            while ((map[gap_row][gap_col] != '#') && (map[gap_row][gap_col] != '.')) {
                gap_row += dy;
                gap_col += dx;
            }
            if (map[gap_row][gap_col] == '#') {
                continue;
            } else {
                // Shift all towards gap:
                while (!((gap_row == row) && (gap_col == col))) {
                    std::swap(map[gap_row][gap_col], map[gap_row - dy][gap_col - dx]);
                    gap_row -= dy;
                    gap_col -= dx;
                }
            }
        } else {
            std::swap(map[row][col], map[new_row][new_col]);
        }
        row = new_row;
        col = new_col;
    }
    auto result = uint32_t{};
    return result;
}

void solve_all(const std::vector<std::vector<std::string>> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 15;

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

    auto instructions = aoc::io::get_input_groups<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
