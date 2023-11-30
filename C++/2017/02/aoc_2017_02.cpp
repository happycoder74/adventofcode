#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace aoc_2017_02 {

int solve_part_1(std::vector<std::vector<int>> lines) {
    int checksum = 0;

    for (auto &line : lines) {
        checksum += (*std::max_element(line.begin(), line.end()) - *std::min_element(line.begin(), line.end()));
    }
    return checksum;
}

int solve_part_2(std::vector<std::vector<int>> lines) {
    int checksum = 0;

    for (auto &line : lines) {
        for (auto &num : line) {
            for (auto &nn : line) {
                if ((nn != num) && ((num % nn) == 0)) {
                    checksum += num / nn;
                }
            }
        }
    }
    return checksum;
}

int solve_all(std::vector<std::vector<int>> lines) {
    aoc::timer<int, std::vector<int>>(1, aoc_2017_02::solve_part_1, lines, true);
    aoc::timer<int, std::vector<int>>(2, aoc_2017_02::solve_part_2, lines, true);

    return 0;
}
} // namespace aoc_2017_02

int main(int argc, char **argv) {
    std::string filename;

    std::vector<std::string> data;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    data = aoc::io::get_input_list<std::string>(filename, 2017, 2);
    std::vector<std::vector<int>> lines;
    for (std::string &dataline : data) {
        std::vector<int> line;
        std::replace(dataline.begin(), dataline.end(), '\t', ' ');
        for (std::string &num : aoc::string::split(dataline, ' ')) {
            line.push_back(std::stoi(num));
        }
        lines.push_back(line);
    }

    std::cout << "Presenting solution:\n";
    aoc::timer<int, std::vector<int>>(0, aoc_2017_02::solve_all, lines, false);

    return 0;
}
