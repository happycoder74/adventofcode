#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <array>
#include <exception>
#include <iostream>
#include <ranges>
#include <unordered_set>

enum class Part {
    ONE,
    TWO
};

enum class Turn {
    UNDEFINED,
    LEFT,
    RIGHT
};

using Point = std::pair<int, int>;
using Step  = std::pair<Turn, int>;

template <>
struct std::hash<std::pair<int, int>> {
    inline auto operator()(const pair<int, int> &v) const -> size_t {
        return std::size_t(v.first) << 32 | v.second;
    }
};

Point operator+(const Point &l, const Point &r) {
    return {l.first + r.first, l.second + r.second};
}

Point operator*(const Point &l, const int r) {
    return {l.first * r, l.second * r};
}

inline auto manhattan_distance(const Point &p) -> int {
    return std::abs(p.first) + std::abs(p.second);
}

auto parse_instructions(const std::string &instructions) {
    std::vector<Step> parsed{};
    std::stringstream ss{instructions};

    char turn_char = '\0';
    int  steps     = 0;
    Turn turn      = Turn::UNDEFINED;

    while (!ss.fail()) {
        ss >> turn_char >> steps;
        switch (turn_char) {
            case 'L':
                turn = Turn::LEFT;
                break;
            case 'R':
                turn = Turn::RIGHT;
                break;
        }
        parsed.emplace_back(turn, steps);
        ss.seekg(ss.tellg() + static_cast<std::stringstream::pos_type>(1));
    }
    return parsed;
}

auto solution(const std::vector<Step> &instructions, Part part) -> int {
    Point                     pos = {0, 0};
    std::unordered_set<Point> locations{pos};

    std::array<Point, 4> directions{
        {{0, 1}, {-1, 0}, {0, -1}, {1, 0}}
    };

    for (const auto &step : instructions) {
        switch (step.first) {
            case Turn::LEFT:
                std::rotate(directions.begin(), directions.begin() + 1, directions.end());
                break;
            case Turn::RIGHT:
                std::rotate(directions.rbegin(), directions.rbegin() + 1, directions.rend());
                break;
            default:
                std::cerr << "This should not happen (Undefined direction)" << '\n';
                std::terminate();
        }

        auto current_direction = directions.front();

        if (part == Part::ONE) {
            pos = pos + current_direction * step.second;
        } else {
            for ([[maybe_unused]] auto s : std::views::iota(0) | std::views::take(step.second)) {
                pos = pos + current_direction;
                if (locations.contains(pos)) {
                    return manhattan_distance(pos);
                } else {
                    locations.insert(pos);
                }
            }
        }
    }
    return manhattan_distance(pos);
}

auto solve_part_1(const std::vector<Step> &instructions) -> int {
    return solution(instructions, Part::ONE);
}

auto solve_part_2(const std::vector<Step> &instructions) -> int {
    return solution(instructions, Part::TWO);
}

void solve_all(const std::string &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string filename;

    constexpr int year = 2016;
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

    auto line = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, line.front());

    return 0;
}
