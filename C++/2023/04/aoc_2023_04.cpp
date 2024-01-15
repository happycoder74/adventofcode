#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cmath>
#include <ranges>

using card = std::pair<std::vector<int>, std::vector<int>>;

template <typename T> void vec_print(const std::vector<T> &vec, std::string title = "") {
    std::cout << title << " { ";
    for (auto &item : vec) {
        std::cout << item << " ";
    }
    std::cout << "}" << std::endl;
}

card split_deck(const std::string &row) {
    std::vector<std::string> res = aoc::string::split(row.substr(row.find(":") + 1), '|');

    std::vector<std::string> r1 = aoc::string::split(res.front(), ' ');
    auto                     av1 = r1 | std::views::transform([](const auto &s) -> int { return std::stoi(s); });
    std::vector<std::string> r2 = aoc::string::split(res.back(), ' ');
    auto                     av2 = r2 | std::views::transform([](const auto &s) -> int { return std::stoi(s, NULL); });

    std::vector<int> v1, v2;

    for (auto item : av1) {
        v1.push_back(item);
    }
    for (auto item : av2) {
        v2.push_back(item);
    }
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    return std::make_pair(v1, v2);
}

std::string solve_part_1(const std::vector<std::string> data) {
    auto deck = data | std::views::transform([](const auto &s) -> card { return split_deck(s); });
    int  sum = 0;
    for (auto c : deck) {
        std::vector<int> hand;

        std::set_intersection(c.second.begin(), c.second.end(), c.first.begin(), c.first.end(), std::back_inserter(hand));
        int v = static_cast<int>(std::pow(2.0, hand.size() - 1));
        if (v >= 1) {
            sum += v;
        }
    }
    return std::format("{}", sum);
}

std::string solve_part_2(std::vector<std::string> data) {
    return std::format("{}", 0);
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
    int  day = 4;

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
