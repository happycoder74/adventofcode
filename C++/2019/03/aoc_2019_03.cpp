#include "aoc_io.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>

typedef std::pair<int, int> Point;

typedef std::chrono::high_resolution_clock Clock;

static std::vector<std::pair<Point, Point>> find_intersections(std::map<Point, Point> m1, std::map<Point, Point> m2) {
    std::vector<Point> return_vector;

    auto values = m1 | std::views::filter([=](std::pair<Point, Point> p) { return m2.contains(p.first); });
    return std::vector<std::pair<Point, Point>>(values.begin(), values.end());
}

static int manhattan_distance(const Point p0, const Point p1) {
    return std::abs((p0.first - p1.first)) + abs((p0.second - p1.second));
}

int main(int argc, char **argv) {
    std::string                         filename;
    std::vector<std::string>            instructions;
    std::string                         line;
    std::vector<std::map<Point, int>>   wire_stepmap;
    std::vector<std::map<Point, Point>> wire_coords;

    auto t1 = Clock::now();

    filename = argc > 1 ? argv[1] : "input.txt";

    instructions = aoc::get_input_list<std::string>(filename, 2019, 3);

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

    std::vector<std::pair<Point, Point>> intersection_points;

    intersection_points = find_intersections(wire_coords.front(), wire_coords.back());

    int signal = INT_MAX;

    auto dist = std::ranges::min(intersection_points | std::views::transform([](const auto &p) -> int { return manhattan_distance(p.first, {0, 0}); }));

    for (auto p : intersection_points) {
        signal = std::min(signal, wire_stepmap.front()[p.first] + wire_stepmap.back()[p.first]);
    }

    auto t2 = Clock::now();

    std::chrono::duration<double> diff = t2 - t1;
    std::cout << "Part 1: " << std::setw(15) << dist << std::endl;
    std::cout << "Part 2: " << std::setw(15) << signal << std::endl;
    std::cout << "Total time:" << std::setw(12) << std::setprecision(4) << diff.count() << " s" << std::endl;
    return 0;
}
