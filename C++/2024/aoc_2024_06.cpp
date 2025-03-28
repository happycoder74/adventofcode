#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

// using Position  = std::pair<int, int>;
// using Direction = std::pair<int, int>;

template <class T>
struct Position : std::pair<T, T> {
    Position() {
        this->first  = 0;
        this->second = 0;
    }
    Position(T x, T y) {
        this->first  = x;
        this->second = y;
    }
    Position operator+(const Position &p2) {
        return {this->first + p2.first, this->second + p2.second};
    }
    Position &operator+=(const Position &rhs) {
        this->first += rhs.first;
        this->second += rhs.second;
        return *this;
    }
};

template <class T>
using Direction = Position<T>;

template <class T>
struct std::hash<Position<T>> {
    auto operator()(const Position<T> &v) const -> size_t {
        return size_t(v.first) << 32 | v.second;
    }
};

template <class T>
struct std::hash<std::pair<Position<T>, Position<T>>> {
    auto operator()(const std::pair<Position<T>, Direction<T>> &v) const -> size_t {
        return std::hash<Position<T>>()(v.first) ^ std::hash<Direction<T>>()(v.second);
    }
};

template <class T>
struct Map {
    Map() = delete;

    Map(const std::vector<std::string> &instructions) : contents(instructions) {
        find_guard();
        visited.insert(guard_position);
    }

    [[nodiscard]] auto guard() const -> Position<T> {
        return guard_position;
    }

    [[nodiscard]] auto get_visited() -> auto & {
        return visited;
    }

    [[nodiscard]] auto get_visited_size() const -> int {
        return int(visited.size());
    }

    [[nodiscard]] auto get_location(const Position<T> &position) const -> char {
        const auto &[col, row] = position;
        if (is_inside(position))
            return contents[row][col];
        else
            return '\0';
    }

    [[nodiscard]] auto is_inside(const Position<T> &position) const -> bool {
        return ((position.first >= 0) && (position.first < int(contents.front().size()))) && ((position.second >= 0) && (position.second < int(contents.size())));
    }

  private:
    std::vector<std::string>        contents;
    Position<T>                     guard_position;
    std::unordered_set<Position<T>> visited;

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

template <class T>
void turn(std::array<Direction<T>, 4> &directions) {
    std::ranges::rotate(directions, directions.end() - 1);
}

void print_position(const auto &p) {
    std::cout << "[" << p.first << ", " << p.second << "]\n";
}

template <class T>
auto init_directions() -> std::array<Direction<T>, 4> {
    std::array<Direction<T>, 4> directions{
        {{0, -1}, {-1, 0}, {0, 1}, {1, 0}}
    };
    return directions;
}

auto parse_instructions(const std::vector<std::string> &instructions) -> Map<int> {
    auto map = Map<int>{instructions};
    return map;
}

auto solve_part_1(Map<int> &map) -> int {
    auto  directions     = init_directions<int>();
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

auto solve_part_2(Map<int> &map) -> int {
    auto  guard_position = map.guard();
    auto &visited        = map.get_visited();

    auto count = 0;

    visited.erase(guard_position);

    for (const auto &obstacle : visited) {
        auto directions = init_directions<int>();
        guard_position  = map.guard();
        std::unordered_set<std::pair<Position<int>, Direction<int>>> tracemap{
            {guard_position, directions.front()}
        };

        // if (obstacle == guard_position)
        //     continue;

        Position<int> next_position{};
        tracemap.insert({guard_position, directions.front()});
        while (true) {
            next_position = guard_position + directions.front();
            auto c        = map.get_location(next_position);
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
