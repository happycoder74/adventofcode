// #include "aoc_hashmap.hpp"
#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &key) const {
        std::size_t hash1 = std::hash<T1>{}(key.first);
        std::size_t hash2 = std::hash<T2>{}(key.second);

        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash2 >> 2));
    }
};

class Schematic {
  public:
    std::pair<int, int>                                      limits;
    int                                                      next_col{};
    std::unordered_map<std::pair<int, int>, char, pair_hash> grid_map;

    explicit Schematic(std::vector<std::string>);
    auto neighbours(int y, int x) -> std::vector<char>;
    auto near_symbol(int y, int x) -> bool;
    auto find_parts() -> int;
    auto find_number(int row, int col) -> int;
    auto find_gears() -> int;
};

Schematic::Schematic(std::vector<std::string> data) {
    limits.second = int(data.size());
    limits.first  = int(data[0].size());

#ifdef __cpp_lib_ranges_enumerate
    auto rng = data | std::views::enumerate;

    std::ranges::for_each(rng, [&](const auto &enum_row) {
        auto &[j, row] = enum_row;
        std::ranges::for_each(row | std::views::enumerate, [&](const auto &enum_col) {
            auto &[i, col]   = enum_col;
            grid_map[{j, i}] = col;
        });
    });
#else
    auto rng = std::views::zip(std::views::iota(0), data);
    std::ranges::for_each(rng, [&](const auto &enum_row) {
        auto &[j, row] = enum_row;
        std::ranges::for_each(std::views::zip(std::views::iota(0), row), [&](const auto &enum_col) {
            auto &[i, col]   = enum_col;
            grid_map[{j, i}] = col;
        });
    });
#endif

    // int j = 0;
    // for (auto &row : data) {
    //     int i = 0;
    //     for (auto &col : row) {
    //         grid_map[{j, i++}] = col;
    //     }
    //     j++;
    // }
}
auto Schematic::neighbours(int y, int x) -> std::vector<char> {
    std::vector<char>  nbs;
    std::array<int, 3> delta = {-1, 0, 1};
    for (auto &j : delta) {
        for (auto &i : delta) {
            if ((0 <= (y + j)) && ((y + j) < limits.second) && (0 <= (x + i)) && ((x + i) < limits.first)) {
                if (!((i == 0) && (j == 0))) {
                    nbs.emplace_back(grid_map[{y + j, x + i}]);
                }
            }
        }
    }

    return nbs;
}

auto Schematic::near_symbol(int y, int x) -> bool {
    std::vector<char> nbs  = neighbours(y, x);
    auto              item = nbs | std::views::filter([](const auto &nb) {
                    return ((!isdigit(nb)) && (nb != '.'));
                });
    return (!item.empty());
}

auto Schematic::find_parts() -> int {
    int num_parts = 0;
    for (int j = 0; j < this->limits.second; j++) {
        int  num_start = -1;
        bool keep      = false;
        for (int i = 0; i <= this->limits.first; i++) {
            char point = this->grid_map[{j, i}];
            if (isdigit(point)) {
                if (num_start == -1) {
                    num_start = i;
                }
                if (keep || near_symbol(j, i)) {
                    keep = true;
                }
            } else {
                if ((num_start != -1) && keep) {
                    std::string buf{};
                    for (int k = 0; k <= (i - num_start); k++) {
                        buf.push_back(this->grid_map[{j, k + num_start}]);
                    }
                    num_parts += std::stoi(buf);
                }
                num_start = -1;
                keep      = false;
            }
        }
    }
    return num_parts;
}

auto Schematic::find_number(int row, int col) -> int {
    int start = col;
    int end   = col;
    if (!isdigit(this->grid_map[{row, col}])) {
        return 0;
    }
    // Look left
    while (start >= 0) {
        if (isdigit(this->grid_map[{row, start}])) {
            start--;
        } else {
            break;
        }
    }

    // Look right
    while (isdigit(this->grid_map[{row, end}])) {
        end++;
    }

    std::string buf;
    for (int k = start + 1; k <= end - 1; k++) {
        buf.push_back(this->grid_map[{row, k}]);
    }
    this->next_col = end;
    return std::stoi(buf);
}

auto Schematic::find_gears() -> int {
    int                              gear_ratio = 0;
    std::vector<std::pair<int, int>> gears;

    for (int j = 0; j < this->limits.second; j++) {
        for (int i = 0; i < this->limits.first; i++) {
            if (this->grid_map[{j, i}] == '*') {
                gears.emplace_back(i, j);
            }
        }
    }

    for (auto &p : gears) {

        int i = p.first;
        int j = p.second;

        std::vector<int> numbers;

        for (int row = j - 1; row <= j + 1; row++) {
            for (int col = i - 1; col <= i + 1; col++) {
                if ((grid_map.contains({row, col})) && (isdigit(this->grid_map[{row, col}]))) {
                    numbers.push_back(find_number(row, col));
                    if (this->next_col != INT_MAX) {
                        col            = this->next_col;
                        this->next_col = INT_MAX;
                    }
                }
            }
        }
        if (numbers.size() > 1) {
            gear_ratio += numbers[0] * numbers[1];
        }
    }

    return gear_ratio;
}

auto solve_part_1(const std::vector<std::string> &data) -> std::string {
    Schematic schema(data);
    return std::format("{}", schema.find_parts());
}

auto solve_part_2(const std::vector<std::string> &data) -> std::string {
    Schematic schema(data);
    return std::format("{}", schema.find_gears());
}

void solve_all(const std::vector<std::string> &data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data);
        aoc::timer(2, solve_part_2, data);
    }
}

auto main(int argc, char **argv) -> int {
    std::vector<std::string> data;

    constexpr int year = 2023;
    constexpr int day  = 3;

    auto args = std::span(argv, std::size_t(argc));
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
