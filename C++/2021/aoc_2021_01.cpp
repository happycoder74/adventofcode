#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <string>
#include <vector>

namespace aoc_2021_01 {

int solve_part_1(const std::vector<int> &data) {
    int sum = 0;
    for (std::vector<int>::const_iterator it1 = data.begin(), it2 = it1 + 1; it2 != data.end(); it1++, it2++) {
        if (*it1 < *it2) {
            sum++;
        }
    }

    return sum;
}

int solve_part_2(const std::vector<int> &data) {
    int sum = 0;
    for (std::vector<int>::const_iterator it1 = data.begin(), it2 = it1 + 3; it2 != data.end(); it1++, it2++) {
        if (*it1 < *it2) {
            sum++;
        }
    }

    return sum;
}

int solve_all(const std::vector<int> &data) {
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);

    return 0;
}
} // namespace aoc_2021_01

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2021;
    const int   day  = 1;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    std::vector<int> data;
    data = aoc::io::get_input_list<int>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(aoc_2021_01::solve_all, data);

    return 0;
}
