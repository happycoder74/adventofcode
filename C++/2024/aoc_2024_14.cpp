#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <set>
#include <vector>

using Robot = std::pair<std::pair<int, int>, std::pair<int, int>>;

[[nodiscard]] auto parse_instructions(const std::vector<std::string> &instructions) -> std::vector<Robot> {
    auto robots = std::vector<Robot>{};
    std::ranges::transform(instructions, std::back_inserter(robots), [](const auto &s) -> Robot {
        auto s1 = s.substr(s.find('=') + 1, s.find(' '));
        auto s2 = s.substr(s.find('v') + 2, s.npos);
        auto p1 = std::stoi(s1);
        auto p2 = std::stoi(s1.substr(s1.find(',') + 1, s1.npos));
        auto p3 = std::stoi(s2);
        auto p4 = std::stoi(s2.substr(s2.find(',') + 1, s2.npos));

        auto pp1 = std::pair{p1, p2};
        auto pp2 = std::pair{p3, p4};
        return {pp1, pp2};
    });
    return robots;
}

void move_robot(Robot &r, const auto &steps) {
    auto &[position, velocity] = r;
    auto &[x, y]               = position;
    auto &[vx, vy]             = velocity;

    x += steps * vx;
    y += steps * vy;
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

    const auto [max_x, max_y] = get_limits(instructions);
    for (auto &robot : robots) {
        move_robot(robot, iterations);
        auto &[position, velocity] = robot;
        position.first             = position.first % max_x;
        position.second            = position.second % max_y;
        if (position.first < 0)
            position.first += max_x;
        if (position.second < 0)
            position.second += max_y;
    }

    const auto quadrants = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>{
        {{0, 0},                         {max_x / 2, max_y / 2}},
        {{max_x / 2 + 1, 0},             {max_x, max_y / 2}    },
        {{0, max_y / 2 + 1},             {max_x / 2, max_y}    },
        {{max_x / 2 + 1, max_y / 2 + 1}, {max_x, max_y}        }
    };

    auto result = uint32_t{1};
    for (auto &quadrant : quadrants) {
        result *= std::ranges::count_if(robots, [&quadrant](const auto &r) {
            auto [position, velocity] = r;
            auto [l1, l2]             = quadrant;
            if (!((l1.first <= position.first) && (position.first < l2.first)))
                return false;
            if (!((l1.second <= position.second) && (position.second < l2.second)))
                return false;
            return true;
        });
    }
    return result;
}

auto all_unique_positions(const std::vector<Robot> &robots) -> bool {
    auto field = std::set<std::pair<int, int>>{};
    std::ranges::for_each(robots, [&field](const auto &r) {
        field.insert({r.first.first, r.first.second});
    });
    return (robots.size() == field.size());
}

[[nodiscard]] auto solve_part_2(const std::vector<Robot> &instructions) -> int {

    std::vector<Robot> robots = instructions;
    auto [max_x, max_y]       = get_limits(instructions);
    auto result               = int{};
    while (!all_unique_positions(robots)) {
        for (auto &robot : robots) {
            move_robot(robot, 1);
            auto &[position, velocity] = robot;
            position.first             = position.first % max_x;
            position.second            = position.second % max_y;
            if (position.first < 0)
                position.first += max_x;
            if (position.second < 0)
                position.second += max_y;
        }
        ++result;
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
