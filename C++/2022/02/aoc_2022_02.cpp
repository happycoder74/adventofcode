#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <map>
#include <utility>
#include <vector>

namespace aoc_2022_02 {
std::vector<std::pair<char, char>> transform_input(const std::vector<std::string> &input) {
    std::ifstream file;

    std::vector<std::pair<char, char>> return_vector;

    return_vector.reserve(input.size());
    for (auto &item : input) {
        return_vector.push_back(std::make_pair(item[0], item[2]));
    }
    return return_vector;
}

int solve_part_1(const std::vector<std::pair<char, char>> &input) {
    std::map<char, int> shape_points = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };
    std::array<std::array<int, 3>, 3> p = {
        {{3, 6, 0}, {0, 3, 6}, {6, 0, 3}}
    };

    std::string col = "XYZ";
    std::string row = "ABC";
    int         sum = 0;

    for (auto &item : input) {
        sum += p[row.find(item.first)][col.find(item.second)] + shape_points[item.second];
    }
    return sum;
}

int solve_part_2(const std::vector<std::pair<char, char>> &input) {
    std::map<char, int> shape_points = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
    };

    std::array<int, 3> p = {
        {0, 3, 6}
    };

    std::map<std::pair<char, char>, char> req_shape = {
        {{'A', 'X'}, 'Z'},
        {{'A', 'Y'}, 'X'},
        {{'A', 'Z'}, 'Y'},
        {{'B', 'X'}, 'X'},
        {{'B', 'Y'}, 'Y'},
        {{'B', 'Z'}, 'Z'},
        {{'C', 'X'}, 'Y'},
        {{'C', 'Y'}, 'Z'},
        {{'C', 'Z'}, 'X'}
    };

    int points = 0;

    std::string col = "XYZ";

    for (auto &item : input) {
        points += p[col.find(item.second)] + shape_points[req_shape[item]];
    }

    return points;
}

int solve_all(const std::vector<std::pair<char, char>> &input) {
    aoc::timer(1, aoc_2022_02::solve_part_1, input, true);
    aoc::timer(2, aoc_2022_02::solve_part_2, input, true);

    return 0;
}

} // namespace aoc_2022_02

int main(int argc, char *argv[]) {
    const int year = 2022;
    const int day = 2;

    std::vector<std::pair<char, char>> input = aoc_2022_02::transform_input(aoc::io::get_input_list<std::string>("input.txt", year, day));

    std::cout << "Solution for " << std::format("{:d}/{:02d}", year, day) << '\n';

    aoc::timer(0, aoc_2022_02::solve_all, input, false);

    return 0;
}
