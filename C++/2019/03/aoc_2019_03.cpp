#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>

typedef std::pair<int, int> Point;

typedef std::pair<std::vector<std::pair<Point, Point>>, std::vector<std::map<Point, int>>> Container;

static std::vector<std::pair<Point, Point>> find_intersections(std::map<Point, Point> m1, std::map<Point, Point> m2) {
    std::vector<Point> return_vector;

    auto values = m1 | std::views::filter([=](std::pair<Point, Point> p) { return m2.contains(p.first); });
    return std::vector<std::pair<Point, Point>>(values.begin(), values.end());
}

static int manhattan_distance(const Point p0, const Point p1) {
    return std::abs((p0.first - p1.first)) + abs((p0.second - p1.second));
}

static Container transform_input(std::vector<std::string> instructions) {
    std::vector<std::map<Point, int>>   wire_stepmap;
    std::vector<std::map<Point, Point>> wire_coords;
    for (std::string &l : instructions) {
        int                      steps = 0;
        std::pair<int, int>      position = {0, 0};
        std::pair<int, int>      move;
        std::vector<std::string> tokens = aoc::string::split(l, ',');
        std::map<Point, Point>   wc_map;
        std::map<Point, int>     ws_map;
        for (auto ch : tokens) {
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
                    std::cerr << "Error in direction input" << std::endl;
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

    std::pair<std::vector<std::pair<Point, Point>>, std::vector<std::map<Point, int>>> data;
    data.first = find_intersections(wire_coords.front(), wire_coords.back());
    data.second = wire_stepmap;

    return data;
}

int solve_part_1(Container data) {
    int dist = std::ranges::min(data.first | std::views::transform([](const auto &p) -> int { return manhattan_distance(p.first, {0, 0}); }));

    return dist;
}

int solve_part_2(Container data) {
    int signal = INT_MAX;
    for (auto p : data.first) {
        signal = std::min(signal, data.second.front()[p.first] + data.second.back()[p.first]);
    }

    return signal;
}

int solve_all(Container data) {
    aoc::timer<int, Container>(1, solve_part_1, data, true);
    aoc::timer<int, Container>(2, solve_part_2, data, true);

    return 0;
}

int main(int argc, char **argv) {
    std::string filename;
    std::string line;
    const int   year = 2019;
    const int   day = 3;

    std::vector<std::string> instructions;

    auto t1 = Clock::now();

    filename = argc > 1 ? argv[1] : "input.txt";

    instructions = aoc::io::get_input_list<std::string>(filename, 2019, 3);

    Container data = transform_input(instructions);

    std::cout << "Solution for " << std::format("{:d}/{:02d}", year, day) << std::endl;
    aoc::timer<int, Container>(0, solve_all, data, false);

    return 0;
}
