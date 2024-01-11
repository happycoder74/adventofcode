#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class Schematic {
  private:
    std::pair<std::int32_t, std::int32_t>        limits;
    std::int32_t                                 next_col;
    std::map<std::tuple<int32_t, int32_t>, char> grid_map;

  public:
    explicit Schematic(std::vector<std::string>);
    std::vector<char> neighbours(std::int32_t y, std::int32_t x);
    bool              near_symbol(std::int32_t y, std::int32_t x);
    std::int32_t      find_parts();
    std::int32_t      find_number(std::int32_t row, std::int32_t col);
    std::int32_t      find_gears();
};

Schematic::Schematic(std::vector<std::string> data) {
    this->limits.second = static_cast<int32_t>(data.size());
    this->limits.first = static_cast<int32_t>(data[0].size());
    this->next_col = INT_MAX;

    int32_t j = 0;
    for (auto &row : data) {
        int32_t i = 0;
        for (auto &col : row) {
            grid_map[{j, i++}] = col;
        }
        j++;
    }
}
std::vector<char> Schematic::neighbours(std::int32_t y, std::int32_t x) {
    std::vector<char>  nbs;
    std::array<int, 3> delta = {-1, 0, 1};
    for (auto &j : delta) {
        for (auto &i : delta) {
            /* For some reason grid_map.contains gives wrong final answer
             * if (grid_map.contains({y + j, x + i}))
             * should really be the same thing... */
            if ((0 <= (y + j)) && ((y + j) < this->limits.second) && (0 <= (x + i)) && ((x + i) < this->limits.first)) {
                if (!((i == 0) && (j == 0))) {
                    nbs.push_back(this->grid_map[{y + j, x + i}]);
                }
            }
        }
    }

    return nbs;
}

bool Schematic::near_symbol(std::int32_t y, std::int32_t x) {
    std::vector<char> nbs = this->neighbours(y, x);
    for (auto &nb : nbs) {
        if (!isdigit(nb) && (nb != '.')) {
            return true;
        }
    }
    return false;
}

std::int32_t Schematic::find_parts() {
    std::int32_t num_parts = 0;
    for (std::int32_t j = 0; j < this->limits.second; j++) {
        int  num_start = -1;
        bool keep = false;
        for (std::int32_t i = 0; i <= this->limits.first; i++) {
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
                    char         buf[100];
                    std::int32_t k;
                    for (k = 0; k <= (i - num_start); k++) {
                        buf[k] = this->grid_map[{j, k + num_start}];
                    }
                    buf[k] = '\0';
                    num_parts += std::atoi(buf);
                }
                num_start = -1;
                keep = false;
            }
        }
    }
    return num_parts;
}

std::int32_t Schematic::find_number(std::int32_t row, std::int32_t col) {
    int start = col;
    int end = col;
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

    char buf[10] = {0};
    int  k;
    for (k = start + 1; k <= end - 1; k++) {
        buf[k - (start + 1)] = this->grid_map[{row, k}];
    }
    buf[k - (start + 1)] = '\0';

    this->next_col = end;
    return atoi(buf);
}

std::int32_t Schematic::find_gears() {
    std::int32_t gear_ratio = 0;

    std::vector<std::pair<int32_t, int32_t>> gears;

    std::array<int, 3> delta = {-1, 0, 1};

    for (std::int32_t j = 0; j < this->limits.second; j++) {
        for (std::int32_t i = 0; i < this->limits.first; i++) {
            if (this->grid_map[{j, i}] == '*') {
                gears.push_back(std::pair<int32_t, int32_t>(i, j));
            }
        }
    }

    for (auto &p : gears) {

        std::int32_t i = p.first;
        std::int32_t j = p.second;

        std::vector<int32_t> numbers;

        for (std::int32_t row = j - 1; row <= j + 1; row++) {
            for (std::int32_t col = i - 1; col <= i + 1; col++) {
                if ((grid_map.contains({row, col})) && (isdigit(this->grid_map[{row, col}]))) {
                    numbers.push_back(find_number(row, col));
                    if (this->next_col != INT_MAX) {
                        col = this->next_col;
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

std::string solve_part_1(std::vector<std::string> data) {
    Schematic schema(data);

    return std::format("{}", schema.find_parts());
}

std::string solve_part_2(std::vector<std::string> data) {
    Schematic schema(data);
    return std::format("{}", schema.find_gears());
}

void *solve_all(std::vector<std::string> data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data, 1);
        aoc::timer(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    std::vector<std::string> data;

    char sourcefile[20];
    int  year = 2023;
    int  day = 3;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(argv[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    aoc::timer(0, solve_all, data, 0);

    return 0;
}
