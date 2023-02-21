#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "aoc_io.hpp"
#include "aoc_timer.hpp"

namespace aoc_2017_01 {

    int solution(std::string line, int step) {
        int sum = 0;

        std::string line2 = line;
        std::rotate(line2.begin(), line2.begin() + step, line2.end());
        for(std::string::iterator it1 = line.begin(), it2 = line2.begin(); it1 != line.end(); it1++, it2++) {
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
        return solution(line, line.length() / 2);
    }

    int solve_all(std::string line) {
        aoc::timer(1, aoc_2017_01::solve_part_1, line, true);
        aoc::timer(2, aoc_2017_01::solve_part_2, line, true);

        return 0;
    }
}

int main(int argc, char **argv) {
    std::string filename;
    std::string data;

    if (argc > 1)
        filename = argv[1];
    else
        filename = "../../../data/2017/01/input.txt";

    data = aoc::get_input_bare(filename, 2017, 1);

    std::cout << "Presenting solution:\n";
    aoc::timer(0, aoc_2017_01::solve_all, data, false);

    return 0;
}

