#include "aoc_timer.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

auto solve_part_1(std::vector<std::uint16_t> &data) -> int {
    std::sort(data.begin(), data.end());
    return data.back();
}

auto solve_part_2(std::vector<std::uint16_t> &data) -> int {
    std::sort(data.begin(), data.end());
    auto result = std::ranges::slide_view(data, 2) | std::views::filter([](const auto &a) { return (a[1] - a[0]) > 1; });
    return result.front()[0] + 1;
}

auto main(int argc, char *argv[]) -> int {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 5;

    auto args = std::span(argv, size_t(argc));

    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    filepath = filepath / std::format("{}/{:02d}", year, day) / filename;
    std::ifstream ifs(filepath);

    std::vector<std::uint16_t> data;

    constexpr short int NPOS = 10;
    for (std::string line; std::getline(ifs, line);) {
        std::uint16_t seat_id = 0;
        for (std::uint16_t i = 0; i < NPOS; i++) {
            switch (line[i]) {
                case 'B':
                case 'R':
                    seat_id += 1 << (NPOS - 1 - i);
                    break;
                default:
                    break;
            }
        }
        data.push_back(seat_id);
    }

    std::cout << std::format("{:=<55}\n", "");
    std::cout << std::format("Solution for {:d}, day {:02d}\n", year, day);
    std::cout << std::format("{:-<55}\n", "");
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    std::cout << std::format("{:-<55}\n", "");
    return 0;
}
