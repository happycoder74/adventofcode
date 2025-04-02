#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <unordered_set>
#include <vector>

using Point = std::pair<int, int>;
using Robot = std::pair<Point, Point>;

template <>
struct std::hash<std::pair<int, int>> {
    auto operator()(const pair<int, int> &v) const -> size_t {
        return std::hash<int>()(v.first) ^ std::hash<int>()(v.second);
    }
};

[[nodiscard]] auto parse_instructions(const std::vector<std::string> &instructions) -> std::vector<Robot> {
    auto robots = std::vector<Robot>{};
    std::ranges::transform(instructions, std::back_inserter(robots), [](const auto &s) -> Robot {
        const auto s1 = s.substr(s.find('=') + 1, s.find(' '));
        const auto s2 = s.substr(s.find('v') + 2, s.npos);
        const auto p1 = std::stoi(s1);
        const auto p2 = std::stoi(s1.substr(s1.find(',') + 1, s1.npos));
        const auto p3 = std::stoi(s2);
        const auto p4 = std::stoi(s2.substr(s2.find(',') + 1, s2.npos));

        return {
            std::pair{p1, p2},
            std::pair{p3, p4}
        };
    });
    return robots;
}

void move_robot(Robot &r, const auto steps, const auto &limits) {
    auto &[position, velocity] = r;
    auto &[x, y]               = position;
    auto &[vx, vy]             = velocity;

    auto &[max_x, max_y] = limits;

    x = (max_x + (x + steps * vx) % max_x) % max_x;
    y = (max_y + (y + steps * vy) % max_y) % max_y;
}

auto get_limits(const std::vector<Robot> &robots) {
    auto max_x_pair = std::ranges::max(robots, {}, [](const auto &v) {
        return v.first.first;
    });
    auto max_y_pair = std::ranges::max(robots, {}, [](const auto &v) {
        return v.first.second;
    });
    return std::pair{max_x_pair.first.first + 1, max_y_pair.first.second + 1};
}

[[nodiscard]] auto solve_part_1(const std::vector<Robot> &instructions) -> uint32_t {
    const auto         iterations = 100;
    std::vector<Robot> robots     = instructions;

    const auto limits         = get_limits(instructions);
    const auto [max_x, max_y] = limits;
    std::ranges::for_each(robots, [&](auto &robot) {
        move_robot(robot, iterations, limits);
    });

    const auto quadrants = std::array<std::pair<Point, Point>, 4>{
        {{{0, 0}, {max_x / 2, max_y / 2}}, {{max_x / 2 + 1, 0}, {max_x, max_y / 2}}, {{0, max_y / 2 + 1}, {max_x / 2, max_y}}, {{max_x / 2 + 1, max_y / 2 + 1}, {max_x, max_y}}}
    };

    auto result = uint32_t{1};
    for (auto &quadrant : quadrants) {
        result *= std::ranges::count_if(robots, [&quadrant](const auto &r) {
            auto [position, velocity] = r;
            auto [l1, l2]             = quadrant;
            if (!((l1.first <= position.first) && (position.first < l2.first) && (l1.second <= position.second) && (position.second < l2.second)))
                return false;
            return true;
        });
    }
    return result;
}

auto all_unique_positions(const std::vector<Robot> &robots) -> bool {
    auto field = std::unordered_set<Point>{};
    for (auto &robot : robots) {
        auto [it, success] = field.insert(robot.first);
        if (!success)
            return false;
    }
    return true;
}

[[nodiscard]] auto solve_part_2(const std::vector<Robot> &instructions) -> int {

    std::vector<Robot> robots = instructions;
    const auto         limits = get_limits(instructions);
    auto               result = int{};
    for (; !all_unique_positions(robots); ++result) {
        std::ranges::for_each(robots, [&](auto &robot) {
            move_robot(robot, 1, limits);
        });
    }
    return result;
}

void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 14;

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
