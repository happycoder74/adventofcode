#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <cstdint>
#include <format>
#include <string>
#include <vector>

static int find_digit(std::string string, int order) {
    if (order >= 0) { // Look from the front
        for (std::uint32_t i = 0; i < string.length(); i++) {
            if (isdigit(string[i])) {
                return string[i] - '0';
            }
        }
    } else {
        for (int32_t i = static_cast<int>(string.length()) - 1; i >= 0; i--) {
            if (isdigit(string[i])) {
                return string[i] - '0';
            }
        }
    }
    return -1;
}

std::string solve_part_1(std::vector<std::string> data) {
    uint32_t sum = 0;
    for (auto &string : data) {
        uint32_t first = find_digit(string, 1);
        uint32_t second = find_digit(string, -1);
        sum += first * 10 + second;
    }

    return std::string(std::format("{}", sum));
}

std::vector<std::string> needles = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

std::vector<std::int32_t> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};

std::string solve_part_2(std::vector<std::string> data) {
    uint32_t sum = 0;
    for (auto &string : data) {
        int32_t first_index = 100;
        int32_t second_index = -100;
        int32_t first = 0;
        int32_t second = 0;

        for (int32_t i_needle = 0; i_needle < 18; i_needle++) {
            std::string::size_type found;
            std::string            needle = needles[i_needle];

            found = string.find(needle);
            if (found != std::string::npos) {
                if (static_cast<int>(found) < first_index) {
                    first_index = static_cast<int>(found);
                    first = values[i_needle];
                }
            }
            found = string.rfind(needle);
            if (found != std::string::npos) {
                if (static_cast<int>(found) > second_index) {
                    second_index = static_cast<int>(found);
                    second = values[i_needle];
                }
            }
        }

        sum += first * 10 + second;
    }

    return std::string(std::format("{}", sum));
}

void *solve_all(std::vector<std::string> data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data, 1);
        aoc::timer(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    std::vector<std::string> data;

    char sourcefile[20];
    int  year = 2023;
    int  day = 1;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(argv[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    aoc::timer(0, solve_all, data, 0);

    return 0;
}
