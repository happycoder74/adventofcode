#include "aoc_io.hpp"
#include <cstdint>
#include <fmt/core.h>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::int16_t  level = 0;
    std::uint16_t counter = 0;
    std::string   filename;

    bool      basement_found = false;
    const int year = 2015;
    const int day = 1;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    std::vector<std::string> line = aoc::io::get_input_list<std::string>(filename, year, day);

    for (auto ch : line[0]) {
        ch == '(' ? level++ : level--;
        if (!basement_found) {
            counter++;
            if (level == -1) {
                basement_found = true;
            }
        }
    }

    std::cout << "Solution for " << std::format("{:d}/{:02d}", year, day) << std::endl;
    std::cout << level << std::endl;
    std::cout << counter << std::endl;
    return 0;
}
