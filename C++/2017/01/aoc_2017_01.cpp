#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <iostream>
#include <string>

namespace aoc_2017_01 {

int solution(std::string line, int step) {
    int sum = 0;

    std::string line2 = line;
    std::rotate(line2.begin(), line2.begin() + step, line2.end());
    for (std::string::iterator it1 = line.begin(), it2 = line2.begin(); it1 != line.end(); it1++, it2++) {
        if (*it1 == *it2) {
            sum += *it1 - '0';
        }
    }

    return sum;
}

int solve_part_1(std::string line) {
    return solution(line, 1);
}

int solve_part_2(std::string line) {
    return solution(line, static_cast<int>(line.length()) / 2);
}

int solve_all(std::string line) {
    aoc::timer(1, aoc_2017_01::solve_part_1, line, true);
    aoc::timer(2, aoc_2017_01::solve_part_2, line, true);

    return 0;
}
} // namespace aoc_2017_01

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2017;
    const int   day = 1;

    std::vector<std::string> data;

    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "input.txt";
    }

    data = aoc::io::get_input_list<std::string>(filename, year, day);

    std::cout << "Solution for " << std::format("{:d}/{:02d}", year, day) << std::endl;
    aoc::timer(0, aoc_2017_01::solve_all, data[0], false);

    return 0;
}
