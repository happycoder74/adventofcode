#include "aoc_timer.hpp"
#include <format>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <unordered_map>
#include <vector>

constexpr int ncycles = 6;
constexpr int mask    = 0xFF;

constexpr unsigned int get_key(auto x, auto y, auto z, auto w) {
    return (x + ncycles + 1) << 24 | (y + ncycles + 1) << 16 | (z + ncycles + 1) << 8 | (w + ncycles + 1);
};

auto count_neighbours(auto x, auto y, auto z, auto w, std::unordered_map<unsigned int, int> &map, bool part_2 = false) {
    auto             count     = 0;
    int              dw_start  = 0;
    int              dw_end    = 0;
    std::vector<int> dw_deltas = {0};

    auto deltas = {-1, 0, 1};
    if (part_2) {
        dw_deltas.insert(dw_deltas.begin() + 1, -1);
        dw_deltas.push_back(1);
    }

    for (auto &dw : dw_deltas) {
        for (auto &dz : deltas) {
            for (auto &dy : deltas) {
                for (auto &dx : deltas) {
                    if ((dx == 0) && (dy == 0) && (dz == 0) && (dw == 0)) {
                        continue;
                    }
                    unsigned int key = get_key(x + dx, y + dy, z + dz, w + dw);
                    if (map[key]) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int solve_part_1(std::unordered_map<unsigned int, int> &map, int coord_max) {
    std::vector<unsigned int> activate{};
    std::vector<unsigned int> deactivate{};

    for (int i = 1; i <= ncycles; i++) {
        for (int z = -i; z <= i; z++) {
            for (int y = -i; y <= (int)coord_max + i; y++) {
                for (int x = -i; x <= (int)coord_max + i; x++) {
                    auto active_neighbours = count_neighbours(x, y, z, 0, map);
                    auto key               = get_key(x, y, z, 0);
                    auto is_active         = map[key];
                    if (is_active && (active_neighbours < 2 || active_neighbours > 3)) {
                        deactivate.push_back(key);
                    } else if (active_neighbours == 3) {
                        activate.push_back(key);
                    }
                }
            }
        }

        for (auto &key : activate) {
            map[key] = true;
        }
        for (auto &key : deactivate) {
            map[key] = false;
        }

        activate.clear();
        deactivate.clear();
    }
    auto result = 0;
    for (auto &k : map) {
        result += k.second;
    }
    return result;
}

int solve_part_2(std::unordered_map<unsigned int, int> &map, int coord_max) {
    std::vector<unsigned int> activate{};
    std::vector<unsigned int> deactivate{};

    for (int i = 1; i <= ncycles; i++) {
        for (int w = -i; w <= i; w++) {
            for (int z = -i; z <= i; z++) {
                for (int y = -i; y <= (int)coord_max + i; y++) {
                    for (int x = -i; x <= (int)coord_max + i; x++) {
                        auto active_neighbours = count_neighbours(x, y, z, w, map, true);
                        auto key               = get_key(x, y, z, w);
                        auto is_active         = map[key];
                        if (is_active && (active_neighbours < 2 || active_neighbours > 3)) {
                            deactivate.push_back(key);
                        } else if (active_neighbours == 3) {
                            activate.push_back(key);
                        }
                    }
                }
            }
        }

        for (auto &key : activate) {
            map[key] = true;
        }
        for (auto &key : deactivate) {
            map[key] = false;
        }

        activate.clear();
        deactivate.clear();
    }
    auto result = 0;
    for (auto &k : map) {
        result += k.second;
    }
    return result;
}

int main(void) {
    std::unordered_map<unsigned int, int> map = {};

    std::ifstream ifs("/home/christian/projects/adventofcode/data/2020/17/input.txt");
    std::string   line;
    int           coord_max = 0;

    int row = 0;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        char              c   = 0;
        int               col = 0;
        while (ss >> c) {
            if (c == '#') {
                map[get_key(col, row, 0, 0)] = true;
            }
            col++;
        }
        if (row == 0)
            coord_max = col - 1;
        row++;
    }

    std::unordered_map<unsigned int, int> map_clone = map;

    aoc::timer(1, solve_part_1, map, coord_max);
    aoc::timer(2, solve_part_2, map_clone, coord_max);
    // std::cout << std::format("Part 1: {}", solve_part_1(map)) << "\n";
    // std::cout << std::format("Part 2: {}", solve_part_2(map_clone)) << "\n";
    return 0;
}
