#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

using Position  = std::pair<int, int>;
using Direction = std::pair<int, int>;

template <>
struct std::hash<Position> {
    auto operator()(const Position &v) const -> size_t {
        return size_t(v.first) << 32 | v.second;
    }
};

template <>
struct std::hash<std::pair<Position, Direction>> {
    auto operator()(const std::pair<Position, Direction> &v) const -> size_t {
        return std::hash<Position>()(v.first) ^ std::hash<Direction>()(v.second);
    }
};

struct Map {
    Map() = delete;

    Map(const std::vector<std::string> &instructions) : contents(instructions) {
        find_guard();
        visited.insert(guard_position);
    }

    [[nodiscard]] Position guard() const {
        return guard_position;
    }

    [[nodiscard]] auto &get_visited() {
        return visited;
    }

    int get_visited_size() const {
        return int(visited.size());
    }

    char get_location(const Position &position) const {
        const auto &[col, row] = position;
        if (is_inside(position))
            return contents[row][col];
        else
            return '\0';
    }

    bool is_inside(const Position &position) const {
        return ((position.first >= 0) && (position.first < int(contents.front().size()))) && ((position.second >= 0) && (position.second < int(contents.size())));
    }

  private:
    std::vector<std::string>     contents;
    Position                     guard_position;
    std::unordered_set<Position> visited;

    void find_guard() {
        int x{}, y{};
        for (const auto &[ri, row] : std::views::zip(std::views::iota(0), contents)) {
            auto res = row.find('^');
            if (res != row.npos) {
                y = ri;
                x = int(res);
            }
        }
        guard_position = {x, y};
    }
};

Position operator+(const Position &p1, const Direction &p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

void turn(std::array<std::pair<int, int>, 4> &directions) {
    std::ranges::rotate(directions, directions.end() - 1);
}

void print_position(const Position &p) {
    std::cout << "[" << p.first << ", " << p.second << "]\n";
}

std::array<Direction, 4> init_directions() {
    std::array<Direction, 4> directions{
        {{0, -1}, {-1, 0}, {0, 1}, {1, 0}}
    };
    return directions;
}

auto parse_instructions(const std::vector<std::string> &instructions) -> Map {
    auto map = Map{instructions};
    return map;
}

auto solve_part_1(Map &map) -> int {
    auto  directions     = init_directions();
    auto  guard_position = map.guard();
    auto &visited        = map.get_visited();

    while (true) {
        auto next_position = guard_position + directions.front();
        if (!map.is_inside(next_position)) {
            return map.get_visited_size();
        } else if (map.get_location(next_position) == '#') {
            turn(directions);
        } else {
            guard_position = next_position;
            visited.insert(guard_position);
        }
    }
    return map.get_visited_size();
}

auto solve_part_2(Map &map) -> int {
    auto  guard_position = map.guard();
    auto &visited        = map.get_visited();

    auto count = 0;

    for (const auto &obstacle : visited) {
        auto directions = init_directions();
        guard_position  = map.guard();
        std::unordered_set<std::pair<Position, Direction>> tracemap{
            {guard_position, directions.front()}
        };

        if (obstacle == guard_position)
            continue;

        tracemap.insert({guard_position, directions.front()});
        while (true) {
            Position next_position = guard_position + directions.front();
            auto     c             = map.get_location(next_position);
            if (c == '\0') {
                break;
            } else if ((c == '#') || (next_position == obstacle)) {
                turn(directions);
            } else if (tracemap.contains({next_position, directions.front()})) {
                count += 1;
                break;
            } else {
                guard_position = next_position;
                tracemap.insert({guard_position, directions.front()});
            }
        }
    }

    return count;
}

void solve_all(const std::vector<std::string> &instructions) {
    auto map = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, map);
    aoc::timer(2, solve_part_2, map);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 6;

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
