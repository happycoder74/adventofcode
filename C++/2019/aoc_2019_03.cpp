#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <climits>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>

using Point = std::pair<int, int>;

using Container = std::pair<std::vector<std::pair<Point, Point>>, std::vector<std::map<Point, int>>>;

auto find_intersections(const std::map<Point, Point> &m1, const std::map<Point, Point> &m2) {
    std::vector<Point> return_vector;

    auto values = m1 //
                  | std::views::filter([&m2](const std::pair<Point, Point> &p) {
                        return m2.contains(p.first);
                    });
    return std::vector<std::pair<Point, Point>>(values.begin(), values.end());
}

static auto manhattan_distance(const Point &p0, const Point &p1) {
    return std::abs((p0.first - p1.first)) + abs((p0.second - p1.second));
}

static auto transform_input(const std::vector<std::string> &instructions) {
    std::vector<std::map<Point, int>>   wire_stepmap;
    std::vector<std::map<Point, Point>> wire_coords;
    for (const std::string &l : instructions) {
        int steps = 0;

        std::pair<int, int>      position = {0, 0};
        std::pair<int, int>      move;
        std::vector<std::string> tokens = aoc::string::split(l, ',');
        std::map<Point, Point>   wc_map;
        std::map<Point, int>     ws_map;

        for (const auto &ch : tokens) {
            char direction = ch[0];
            int  magnitude = std::stoi(ch.substr(1));
            switch (direction) {
                case 'U':
                    move = {0, 1};
                    break;
                case 'D':
                    move = {0, -1};
                    break;
                case 'L':
                    move = {-1, 0};
                    break;
                case 'R':
                    move = {1, 0};
                    break;
                default:
                    std::cerr << "Error in direction input" << '\n';
                    exit(EXIT_FAILURE);
                    break;
            }
            for (int i = 0; i < magnitude; i++) {
                position.first += move.first;
                position.second += move.second;
                wc_map[position] = position;
                steps++;
                ws_map.try_emplace(position, steps);
            }
        }
        wire_coords.push_back(wc_map);
        wire_stepmap.push_back(ws_map);
    }

    std::pair<std::vector<std::pair<Point, Point>>, std::vector<std::map<Point, int>>> data{find_intersections(wire_coords.front(), wire_coords.back()), wire_stepmap};

    return data;
}

auto solve_part_1(const Container &data) {
    int dist = std::ranges::min(data.first | std::views::transform([](const auto &p) -> int {
                                    return manhattan_distance(p.first, {0, 0});
                                }));

    return dist;
}

auto solve_part_2(const Container &data) {
    int signal = INT_MAX;
    for (const auto &p : data.first) {
        const auto &second = data.second;
        signal             = std::min(signal, second.front().at(p.first) + second.back().at(p.first));
    }

    return signal;
}

auto solve_all(const std::vector<std::string> &instructions) {
    Container data = transform_input(instructions);

    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);

    return 0;
}

int main(int argc, char **argv) {
    std::string filename;
    std::string line;
    const int   year = 2019;
    const int   day  = 3;

    std::vector<std::string> data;

    auto args = std::span(argv, argc);
    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(args[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);

    return 0;
}
