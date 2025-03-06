#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <iterator>
#include <set>
#include <span>
#include <string>
#include <vector>

namespace aoc_2022_03 {

static auto prio(char p) {
    if (std::isupper(p)) {
        return p - 'A' + 27;
    }
    return p - 'a' + 1;
}

auto clean_input(const std::vector<std::string> &input_data) {
    std::vector<std::pair<std::string, std::string>> rucksacks;
    rucksacks.reserve(input_data.size());
    for (auto &row : input_data) {
        std::pair<std::string, std::string> packs;
        packs.first  = row.substr(0, row.length() / 2);
        packs.second = row.substr(row.length() / 2, row.length() / 2);
        rucksacks.push_back(packs);
    }
    return rucksacks;
}

auto solve_part_1(const std::vector<std::pair<std::string, std::string>> &data) {
    std::int32_t prio_sum = 0;

    for (auto &pack : data) {
        std::set<char> first(pack.first.begin(), pack.first.end());
        std::set<char> second(pack.second.begin(), pack.second.end());

        std::vector<char> common;
        std::ranges::set_intersection(first, second, std::back_inserter(common));
        prio_sum += prio(common[0]);
    }

    return prio_sum;
}

void solve_all(const std::vector<std::string> &data) {
    std::vector<std::pair<std::string, std::string>> input;

    input = clean_input(data);

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, input);
        // aoc::timer(2, solve_part_2, data, 1);
    }
}

} // namespace aoc_2022_03

int main(int argc, char **argv) {
    std::vector<std::string> data;

    constexpr int year = 2022;
    constexpr int day  = 3;

    auto args = std::span(argv, argc);
    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            data = aoc::io::get_input_list<std::string>("test_input.txt", year, day);
        } else {
            data = aoc::io::get_input_list<std::string>(args[1], year, day);
        }
    } else {
        data = aoc::io::get_input_list<std::string>("input.txt", year, day);
    }

    aoc::io::header(year, day);
    aoc::timer(aoc_2022_03::solve_all, data);

    return 0;
}
