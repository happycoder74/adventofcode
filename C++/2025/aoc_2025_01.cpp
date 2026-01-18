#include "aoc_io.hpp"
#include "aoc_timer.hpp"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

auto parse_data(const std::vector<std::string> &instructions) {
    std::vector<std::pair<char, int>> return_vector{};
    for (const auto &instruction : instructions) {
        auto direction    = instruction[0];
        auto rotation_str = std::string(begin(instruction) + 1, end(instruction));
        auto rotation     = std::stoi(rotation_str);

        return_vector.emplace_back(direction, rotation);
    }

    return return_vector;
}

auto solve_part_1(const std::vector<std::string> &instructions) -> size_t {
    auto       commands       = parse_data(instructions);
    const auto positions      = 100;
    const auto start_position = 50;

    auto dial_op = [&](const auto &acc, const auto &command) -> std::pair<int, int> {
        auto position = acc.second;
        if (command.first == 'L') {
            position -= command.second;
        } else if (command.first == 'R') {
            position += command.second;
        }
        auto compare_position = ((position % positions) + positions) % positions;
        if (compare_position == 0) {
            return {acc.first + 1, position};
        }
        return {acc.first, position};
    };
    auto result = std::ranges::fold_left(commands, std::pair{0, start_position}, dial_op);

    return result.first;
}

auto solve_part_2(const std::vector<std::string> &instructions) -> int {
    auto       commands       = parse_data(instructions);
    const auto positions      = 100;
    const auto start_position = 50;

    auto lambda = [&](const auto &acc, const auto &command) -> auto {
        auto num_zeros = int{};

        auto const direction = command.first;
        auto const rotation  = command.second;
        auto       position  = acc.second;

        auto old_position = position;

        if (direction == 'L') {
            position -= rotation;
            num_zeros += rotation / positions;
            position = ((position % positions) + positions) % positions;
            if ((position >= old_position) && (old_position != 0)) {
                num_zeros += 1;
            }
        } else if (direction == 'R') {
            position += rotation;
            num_zeros += rotation / positions;
            position = ((position % positions) + positions) % positions;
            if ((position <= old_position) && (position != 0)) {
                num_zeros += 1;
            }
        }
        if ((position % positions) == 0) {
            num_zeros += 1;
        }
        return std::pair{num_zeros + acc.first, position};
    };

    auto result = std::accumulate(commands.begin(), commands.end(), std::pair{0, start_position}, lambda);
    return result.first;
}

auto solve_all(const std::vector<std::string> &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2025;
    constexpr int day  = 1;

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

    auto instructions = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
