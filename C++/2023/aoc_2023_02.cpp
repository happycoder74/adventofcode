#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <array>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using Cube = std::array<int, 3>;
using Game = std::vector<std::pair<int, Cube>>;

constexpr int green = 0;
constexpr int red   = 1;
constexpr int blue  = 2;

constexpr int color_index(const std::string &color) {
    if (color == "green")
        return green;
    if (color == "red")
        return red;
    return blue;
}

Game find_games(const std::vector<std::string> &data) {
    // clang-format off
    auto rng = data
                | std::views::transform([](const auto &line) -> std::pair<int, Cube> {
                        std::array<int, 3> cubes{0, 0, 0};

                        std::string::size_type pos = line.find(':');

                        int         game_no  = std::stoi(line.substr(4, pos));
                        std::string game_str = line.substr(pos + 2);

                        std::ranges::replace(game_str, ';', ',');

                        for (const auto &s : game_str | std::views::split(std::string_view{", "})) {
                            std::string sv(std::string(s.begin(), s.end()));
                            std::string color_string = std::string(std::ranges::find(s, ' ') + 1, s.end());
                            int cube_count  = std::stoi(sv);
                            int color       = color_index(color_string);
                            cubes.at(color) = std::max(cube_count, cubes.at(color));
                        }
                        return {game_no, cubes};
                    })
                | std::ranges::to<std::vector>();
    // clang-format on
    return rng;
}

constexpr int red_limit   = 12;
constexpr int green_limit = 13;
constexpr int blue_limit  = 14;

int solve_part_1(const Game &games) {
    // clang-format off
    auto winners = games
                    | std::views::transform([](const auto &item) -> int {
                            Cube cube = item.second;
                            if ((cube.at(red) <= red_limit) && (cube.at(green) <= green_limit) && (cube.at(blue) <= blue_limit)) {
                                return item.first;
                            } else {
                                return 0;
                            }
                        })
                   | std::views::common;
    // clang-format on

    return std::reduce(winners.begin(), winners.end());
}

int solve_part_2(const Game &games) {
    // clang-format off
    auto winners = games
                    | std::views::transform([](const auto &item) -> int {
                            Cube cube = item.second;
                            return cube.at(red) * cube.at(green) * cube.at(blue);
                        })
                    | std::views::common;
    // clang-format on

    return std::reduce(winners.begin(), winners.end());
}

void solve_all(const std::vector<std::string> &data) {
    if (data.size() > 0) {
        Game games = aoc::timer(find_games, data, "Preparation time:");
        aoc::timer(1, solve_part_1, games);
        aoc::timer(2, solve_part_2, games);
    }
}

int main(int argc, char **argv) {
    std::vector<std::string> data;

    constexpr int year = 2023;
    constexpr int day  = 2;

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
    aoc::timer(solve_all, data);

    return 0;
}
