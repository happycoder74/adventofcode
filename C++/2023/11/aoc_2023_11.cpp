#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace aoc {
namespace aoc_2023_11 {

static unsigned distance(std::pair<int, int> g1, std::pair<int, int> g2) {
    return std::abs(g2.first - g1.first) + std::abs(g2.second - g1.second);
}

uint64_t solver(std::vector<std::string> data, int multiplier = 2) {
    /* Solution concept
     *
     * - Find the initial positions of the galaxies.
     * - Identify the blank rows and columns.
     * - Find how many blank rows and columns there is between each pair,
     *   or rather, the row and column indices of these rows and columns.
     * - Calculate distance and add 1.000.000 for each blank row and column between the pairs.
     * - Sum up the distances.
     *
     * - Apply the same logic for both part 1 and part 2
     */

    std::vector<std::pair<int, int>> galaxies;

    std::vector<uint64_t> row_inserts;
    std::vector<uint64_t> col_inserts;

    uint64_t distances = 0;

    // Find blank columns
    for (unsigned col = 0; col < data[0].size(); col++) {
        bool blank_col = true;
        for (unsigned row = 0; row < data.size(); row++) {
            if (data[row][col] == '#') {
                blank_col = false;
            }
        }
        if (blank_col) {
            col_inserts.push_back(static_cast<int>(col));
        }
    }

    // Find blank rows
    for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++) {
        std::string::size_type pos;

        pos = (*it).find("#");
        if (pos == std::string::npos) {
            row_inserts.push_back((it - data.begin()));
        }
    }

    // Identify galaxies (simple looping)
    for (unsigned row = 0; row < data.size(); row++) {
        for (unsigned col = 0; col < data[0].size(); col++) {
            if (data[row][col] == '#') {
                galaxies.push_back(std::make_pair(row, col));
            }
        }
    }

    for (std::vector<std::pair<int, int>>::iterator it1 = galaxies.begin(); it1 != galaxies.end(); it1++) {
        for (std::vector<std::pair<int, int>>::iterator it2 = it1 + 1; it2 != galaxies.end(); it2++) {
            std::pair<int, int> g1 = *it1, g2 = *it2;

            uint64_t                      d = distance(g1, g2);
            uint64_t                      extras = 0;
            std::pair<uint64_t, uint64_t> minmax_r, minmax_c;

            minmax_r = std::minmax(g1.first, g2.first);
            minmax_c = std::minmax(g1.second, g2.second);
            for (std::vector<uint64_t>::iterator it = row_inserts.begin(); it != row_inserts.end(); it++) {
                if ((minmax_r.first <= *it) && (*it <= minmax_r.second)) {
                    extras += 1;
                }
            }
            for (std::vector<uint64_t>::iterator it = col_inserts.begin(); it != col_inserts.end(); it++) {
                if ((minmax_c.first <= *it) && (*it <= minmax_c.second)) {
                    extras += 1;
                }
            }
            distances += d + extras * (multiplier - 1);
        }
    }
    return distances;
}

std::string solve_part_1(std::vector<std::string> data) {
    return std::format("{}", aoc::aoc_2023_11::solver(data));
}

std::string solve_part_2(std::vector<std::string> data) {
    return std::format("{}", aoc::aoc_2023_11::solver(data, 1000000));
}

void *solve_all(std::vector<std::string> data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data, 1);
        aoc::timer(2, solve_part_2, data, 1);
    }

    return NULL;
}

} // namespace aoc_2023_11
} // namespace aoc

int main(int argc, char **argv) {
    std::vector<std::string> data;

    char sourcefile[20];
    int  year = 2023;

    int day = 11;

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
    aoc::timer(0, aoc::aoc_2023_11::solve_all, data, 0);

    return 0;
}
