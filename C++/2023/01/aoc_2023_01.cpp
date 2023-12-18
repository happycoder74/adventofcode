#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <format>
#include <ranges>
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

        auto first = needles | std::ranges::views::transform([&string](const auto &needle) -> std::pair<std::string::size_type, std::int32_t> {
                         auto found = string.find(needle);
                         if (found != std::string::npos) {
                             for (std::vector<std::string>::iterator it = needles.begin(); it < needles.end(); it++) {
                                 if (*it == needle) {
                                     return std::make_pair(found, values[static_cast<int>(it - needles.begin())]);
                                 }
                             }
                         }
                         return std::make_pair(1000, 0);
                     });

        auto second = needles | std::ranges::views::transform([&string](const auto &needle) -> std::pair<std::string::size_type, std::int32_t> {
                          auto found = string.rfind(needle);
                          if (found != std::string::npos) {
                              for (std::vector<std::string>::iterator it = needles.begin(); it < needles.end(); it++) {
                                  if (*it == needle) {
                                      return std::make_pair(found, values[static_cast<int>(it - needles.begin())]);
                                  }
                              }
                          }
                          return std::make_pair(0, 0);
                      });

        auto f_it = std::ranges::min_element(first);
        auto s_it = std::ranges::max_element(second);
        sum += (*f_it).second * 10 + (*s_it).second;
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
