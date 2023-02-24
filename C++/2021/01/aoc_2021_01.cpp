#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "aoc_io.hpp"
#include "aoc_timer.hpp"

namespace aoc_2021_01 {

    int solve_part_1(std::vector<int> data) {
        int sum = 0;
        for(std::vector<int>::iterator it1 = data.begin(), it2 = it1 + 1; it2 != data.end(); it1++, it2++) {
            if (*it1 < *it2) {
                sum++;
            }
        }

        return sum;
    }

    int solve_part_2(std::vector<int> data) {
        int sum = 0;
        for(std::vector<int>::iterator it1 = data.begin(), it2 = it1 + 3; it2 != data.end(); it1++, it2++) {
            if (*it1 < *it2) {
                sum++;
            }
        }

        return sum;
    }

    int solve_all(std::vector<int> data) {
        aoc::timer(1, aoc_2021_01::solve_part_1, data, true);
        aoc::timer(2, aoc_2021_01::solve_part_2, data, true);

        return 0;
    }
}

int main(int argc, char **argv) {
    std::string filename;
    std::vector<int> data;
    const int year = 2021;
    const int day = 1;

    if (argc > 1)
        filename = argv[1];
    else
        filename = "../../../../data/2021/01/input.txt";

    data = aoc::get_input_list<int>(filename, year, day);

    std::cout << "Presenting solution:\n";
    aoc::timer(0, aoc_2021_01::solve_all, data, false);

    return 0;
}


