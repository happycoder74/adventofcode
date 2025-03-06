#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
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

int solve_all(const std::vector<std::string> &data) {
    auto lines = aoc_2017_02::transform_input(data);

    aoc::timer(1, aoc_2017_02::solve_part_1, lines);
    aoc::timer(2, aoc_2017_02::solve_part_2, lines);

    return 0;
}
} // namespace aoc_2017_02

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2017;
    const int   day  = 2;

    std::vector<std::string> data;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(argv[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    aoc::io::header(year, day);
    aoc::timer(aoc_2017_02::solve_all, data);

    return 0;
}
