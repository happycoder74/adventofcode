#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace aoc_2017_02 {

std::vector<std::vector<int>> transform_input(const std::vector<std::string> &data) {

    std::vector<std::vector<int>> lines;
    for (std::string dataline : data) {
        std::vector<int> line;
        std::replace(dataline.begin(), dataline.end(), '\t', ' ');
        for (std::string &num : aoc::string::split(dataline, ' ')) {
            line.push_back(std::stoi(num));
        }
        lines.push_back(line);
    }

    return lines;
}

int solve_part_1(const std::vector<std::vector<int>> &lines) {
    int checksum = 0;

    for (auto &line : lines) {
        checksum += (*std::max_element(line.begin(), line.end()) - *std::min_element(line.begin(), line.end()));
    }
    return checksum;
}

int solve_part_2(const std::vector<std::vector<int>> &lines) {
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

int solve_all(const std::vector<std::vector<int>> &lines) {
    aoc::timer(1, aoc_2017_02::solve_part_1, lines, true);
    aoc::timer(2, aoc_2017_02::solve_part_2, lines, true);

    return 0;
}
} // namespace aoc_2017_02

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2017;
    const int   day = 2;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    std::vector<std::vector<int>> lines;
    std::vector<std::string>      data;
    data = aoc::io::get_input_list<std::string>(filename, year, day);
    lines = aoc_2017_02::transform_input(data);

    std::cout << "Solution for " << std::format("{:d}/{:02d}", year, day) << std::endl;
    aoc::timer(0, aoc_2017_02::solve_all, lines, false);

    return 0;
}
