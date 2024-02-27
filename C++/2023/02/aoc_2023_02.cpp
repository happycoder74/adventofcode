#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

using cube_t = std::map<std::string, int>;
using game_t = std::map<int, cube_t>;

game_t find_games(const std::vector<std::string> &data) {
    game_t games;
    for (auto &line : data) {
        std::map<std::string, int> cubes = {
            {"green", 0},
            {"red",   0},
            {"blue",  0}
        };
        std::string::size_type pos = line.find(':');

        int         game_no = std::stoi(line.substr(4, pos));
        std::string game_str = line.substr(pos + 1);

        while ((pos = game_str.find(';')) != std::string::npos) {
            game_str.replace(pos, 1, ",");
        }

        for (const auto &s : game_str | std::views::split(std::string(","))) {
            std::string sv = std::string(s.begin() + 1, s.end());

            int cube_count = std::stoi(sv.substr(0, sv.find(' ')));

            std::string color = sv.substr(sv.find(' ') + 1);
            cubes[color] = std::max(cube_count, cubes[color]);
        }
        games[game_no] = cubes;
    }
    return games;
};

std::string solve_part_1(const std::vector<std::string> &data) {
    game_t games = find_games(data);

    auto winners = games | std::views::transform([](const auto &item) -> int {
                       cube_t cube = item.second;
                       if ((cube["red"] <= 12) && (cube["green"] <= 13) && (cube["blue"] <= 14)) {
                           return item.first;
                       } else {
                           return 0;
                       }
                   }) |
                   std::views::common;

    return std::string(std::format("{}", std::reduce(winners.begin(), winners.end())));
}

std::string solve_part_2(const std::vector<std::string> &data) {
    game_t games = find_games(data);

    auto winners = games | std::views::transform([](const auto &item) -> int {
                       cube_t cube = item.second;
                       return cube["red"] * cube["green"] * cube["blue"];
                   }) |
                   std::views::common;

    return std::string(std::format("{}", std::reduce(winners.begin(), winners.end())));
}

void *solve_all(const std::vector<std::string> &data) {

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
    int  day = 2;

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
    aoc::timer(0, solve_all, data, 0);

    return 0;
}
