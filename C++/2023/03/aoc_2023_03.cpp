#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

class Schematic {
  private:
    std::uint32_t max_x;
    std::uint32_t max_y;
    std::uint32_t num_parts;
    std::uint32_t next_col;
    char        **grid;

  public:
    Schematic() {
        this->max_x = 0;
        this->max_y = 0;
        this->num_parts = 0;
        this->next_col = 0;
        this->grid = NULL;
    };
    explicit Schematic(std::vector<std::string>);
    ~Schematic() {
        for (std::uint32_t row = 0; row < this->max_y; row++) {
            std::free(this->grid[row]);
        }
        free(this->grid);
        this->grid = NULL;
    };
    void          neighbours(std::uint32_t y, std::uint32_t x, char *nbs, std::uint32_t *length);
    bool          near_symbol(std::uint32_t y, std::uint32_t x);
    std::uint32_t find_parts();
    std::uint32_t find_number(std::uint32_t row, std::uint32_t col);
    std::uint32_t find_gears();
};

Schematic::Schematic(std::vector<std::string> data) {
    this->max_y = data.size();
    this->grid = static_cast<char **>(calloc(this->max_y, sizeof(char *)));
    for (unsigned ind = 0; ind < this->max_y; ind++) {
        this->grid[ind] = static_cast<char *>(calloc(data.at(ind).size(), sizeof(char)));
        std::strcpy(this->grid[ind], data.at(ind).c_str());
    }
    this->max_x = strlen(this->grid[0]);
    this->next_col = UINT_MAX;
}
void Schematic::neighbours(std::uint32_t y, std::uint32_t x, char *nbs, std::uint32_t *length) {
    std::uint32_t nb_index = 0;
    for (std::int16_t j = -1; j <= 1; j++) {
        for (std::int16_t i = -1; i <= 1; i++) {
            if (((static_cast<int>(y) + j) >= 0) && ((static_cast<int>(y) + j) < static_cast<int>(this->max_y)) && (0 <= (static_cast<int>(x) + i)) &&
                ((static_cast<int>(x) + i) < static_cast<int>(this->max_x))) {
                if (!((i == 0) && (j == 0))) {
                    nbs[nb_index++] = this->grid[y + j][x + i];
                }
            }
        }
    }

    *length = nb_index;
    return;
}

bool Schematic::near_symbol(std::uint32_t y, std::uint32_t x) {
    char          nbs[9] = {0};
    std::uint32_t length;
    this->neighbours(y, x, nbs, &length);
    for (std::uint32_t index = 0; index < length; index++) {
        if (!isdigit(nbs[index]) && (nbs[index] != '.')) {
            return true;
        }
    }
    return false;
}

std::uint32_t Schematic::find_parts() {
    std::uint32_t num_parts = 0;
    for (std::uint32_t j = 0; j < this->max_y; j++) {
        int  num_start = -1;
        bool keep = false;
        for (std::uint32_t i = 0; i <= this->max_x; i++) {
            char point = this->grid[j][i];
            if (isdigit(point)) {
                if (num_start == -1) {
                    num_start = static_cast<int>(i);
                }
                if (keep || near_symbol(j, i)) {
                    keep = true;
                }
            } else {
                if ((num_start != -1) && keep) {
                    char          buf[100];
                    std::uint32_t k;
                    for (k = 0; k <= (i - num_start); k++) {
                        buf[k] = this->grid[j][k + num_start];
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

std::uint32_t Schematic::find_number(std::uint32_t row, std::uint32_t col) {
    int start = static_cast<int>(col);
    int end = static_cast<int>(col);
    if (!isdigit(this->grid[row][col])) {
        return 0;
    }
    // Look left
    while (start >= 0) {
        if (isdigit(this->grid[row][start])) {
            start--;
        } else {
            break;
        }
    }

    // Look right
    while (isdigit(this->grid[row][end])) {
        end++;
    }

    char buf[10] = {0};
    int  k;
    for (k = start + 1; k <= end - 1; k++) {
        buf[k - (start + 1)] = this->grid[row][k];
    }
    buf[k - (start + 1)] = '\0';

    this->next_col = end;
    return atoi(buf);
}

std::uint32_t Schematic::find_gears() {
    std::uint32_t                              gear_ratio = 0;
    std::vector<std::pair<uint32_t, uint32_t>> gears;

    for (std::uint32_t j = 0; j < this->max_y; j++) {
        for (std::uint32_t i = 0; i < this->max_x; i++) {
            if (this->grid[j][i] == '*') {
                gears.push_back(std::pair<uint32_t, uint32_t>(i, j));
            }
        }
    }

    for (std::uint32_t index = 0; index < gears.size(); index++) {
        std::pair<uint32_t, uint32_t> p = gears[index];
        std::uint32_t                 i = p.first;
        std::uint32_t                 j = p.second;

        std::uint32_t numbers[9] = {0};
        std::uint32_t n_numbers = 0;

        for (std::uint32_t row = j - 1; row <= j + 1; row++) {
            for (std::uint32_t col = i - 1; col <= i + 1; col++) {
                if ((0 <= static_cast<int>(row)) && (row < this->max_y) && (0 <= static_cast<int>(col)) && (col < this->max_x)) {
                    if (isdigit(this->grid[row][col])) {
                        numbers[n_numbers++] = find_number(row, col);
                        if (this->next_col != UINT_MAX) {
                            col = this->next_col;
                            this->next_col = UINT_MAX;
                        }
                    }
                }
            }
        }
        if (n_numbers > 1) {
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
