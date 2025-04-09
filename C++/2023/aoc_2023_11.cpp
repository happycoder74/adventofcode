#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace aoc::aoc_2023_11 {

auto distance(const std::pair<int, int> &g1, const std::pair<int, int> &g2) {
    return std::abs(g2.first - g1.first) + std::abs(g2.second - g1.second);
}

auto solver(const std::vector<std::string> &data, int multiplier = 2) {
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
        for (const auto &row : data) {
            if (row[col] == '#') {
                blank_col = false;
            }
        }
        if (blank_col) {
            col_inserts.push_back(static_cast<int>(col));
        }
    }

    // Find blank rows
    for (auto it = data.begin(); it != data.end(); it++) {
        std::string::size_type pos = 0;

        pos = (*it).find("#");
        if (pos == std::string::npos) {
            row_inserts.push_back((it - data.begin()));
        }
    }

    // Identify galaxies (simple looping)
    for (unsigned row = 0; row < data.size(); row++) {
        for (unsigned col = 0; col < data[0].size(); col++) {
            if (data[row][col] == '#') {
                galaxies.emplace_back(row, col);
            }
        }
    }

    for (auto it1 = galaxies.begin(); it1 != galaxies.end(); it1++) {
        for (auto it2 = it1 + 1; it2 != galaxies.end(); it2++) {
            std::pair<int, int> g1 = *it1, g2 = *it2;

            uint64_t                      d      = distance(g1, g2);
            uint64_t                      extras = 0;
            std::pair<uint64_t, uint64_t> minmax_r, minmax_c;

            minmax_r = std::minmax(g1.first, g2.first);
            minmax_c = std::minmax(g1.second, g2.second);
            for (unsigned long &row_insert : row_inserts) {
                if ((minmax_r.first <= row_insert) && (row_insert <= minmax_r.second)) {
                    extras += 1;
                }
            }
            for (unsigned long &col_insert : col_inserts) {
                if ((minmax_c.first <= col_insert) && (col_insert <= minmax_c.second)) {
                    extras += 1;
                }
            }
            distances += d + extras * (multiplier - 1);
        }
    }
    return distances;
}

auto solve_part_1(const std::vector<std::string> &data) {
    return aoc::aoc_2023_11::solver(data);
}

auto solve_part_2(const std::vector<std::string> &data) {
    return aoc::aoc_2023_11::solver(data, 1000000);
}

void solve_all(const std::vector<std::string> &data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data);
        aoc::timer(2, solve_part_2, data);
    }
}

} // namespace aoc::aoc_2023_11

int main(int argc, char **argv) {
    std::string filename{};

    constexpr int year = 2023;
    constexpr int day  = 11;

    auto args = std::span(argv, size_t(argc));
    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    auto data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(aoc::aoc_2023_11::solve_all, data);

    return 0;
}
