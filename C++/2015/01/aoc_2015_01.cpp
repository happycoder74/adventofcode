#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

using Clock    = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double>;

int main(int argc, char **argv) {
    std::int16_t  level   = 0;
    std::uint16_t counter = 0;
    std::string   filename;

    bool basement_found = false;

    const int year = 2015;
    const int day  = 1;

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

    auto t1 = Clock::now();

    std::chrono::time_point<Clock> t2;

    for (auto ch : line[0]) {
        ch == '(' ? level++ : level--;
        if (!basement_found) {
            counter++;
            if (level == -1) {
                t2             = Clock::now();
                basement_found = true;
            }
        }
    }
    auto t3 = Clock::now();

    auto elapsed_part_1 = aoc::convert_duration(t3 - t1);
    auto elapsed_part_2 = aoc::convert_duration(t2 - t1);

    aoc::io::header(year, day);
    std::cout << "Part 1 answer: " << std::format("{:<20}", level) << std::format("{:>20}", elapsed_part_1) << '\n';
    std::cout << "Part 2 answer: " << std::format("{:<20}", counter) << std::format("{:>20}", elapsed_part_2) << '\n';

    return 0;
}
