#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include "benchmark/benchmark.h"
#include <algorithm>
#include <map>
#include <ranges>

using card = std::pair<std::vector<int>, std::vector<int>>;
using parsed_input = std::vector<card>;

card split_deck(const std::string &row) {
    std::vector<std::string> res = aoc::string::split(row.substr(row.find(':') + 1), '|');

    std::vector<std::string> r1 = aoc::string::split(res.front(), ' ');
    std::vector<std::string> r2 = aoc::string::split(res.back(), ' ');

    auto av1 = r1 | std::views::transform([](const auto &s) -> int { return std::stoi(s); });
    auto av2 = r2 | std::views::transform([](const auto &s) -> int { return std::stoi(s, NULL); });

    std::vector<int> v1(std::ranges::begin(av1), std::ranges::end(av1));
    std::vector<int> v2(std::ranges::begin(av2), std::ranges::end(av2));

    std::ranges::sort(v1);
    std::ranges::sort(v2);

    return std::make_pair(v1, v2);
}

std::vector<card> parse_input(const std::vector<std::string>& data) {
    std::vector<card> return_data;
    auto              deck = data | std::views::transform([](const auto &s) -> card { return split_deck(s); });

    for (auto item : deck) {
        return_data.push_back(item);
    }

    return return_data;
}

std::string solve_part_1(const parsed_input& data) {
    int sum = 0;
    for (auto c : data) {
        std::vector<int> hand;
        std::set_intersection(c.second.begin(), c.second.end(), c.first.begin(), c.first.end(), std::back_inserter(hand));
        if (hand.size() >= 1) {
            sum += 1 << (hand.size() - 1);
        }
    }
    return std::format("{}", sum);
}

std::string solve_part_2(const parsed_input &data) {
    std::map<int, int> deck;

    for (int i = 0; i < static_cast<int>(data.size()); i++) {
        deck[i] += 1;
        card             c = data[i];
        std::vector<int> hand;
        std::set_intersection(c.second.begin(), c.second.end(), c.first.begin(), c.first.end(), std::back_inserter(hand));
        for (int j = 0; j < static_cast<int>(hand.size()); j++) {
            deck[i + j + 1] += deck[i];
        }
    }
    int sum = 0;
    for (auto &item : deck) {
        sum += item.second;
    }
    return std::format("{}", sum);
}

void *solve_all(const parsed_input& data) {

    if (data.size() > 0) {
        aoc::timer(1, solve_part_1, data, 1);
        aoc::timer(2, solve_part_2, data, 1);
    }

    return NULL;
}

static void BM_solve_part_1(benchmark::State &state) {
    std::vector<std::string> input_data = aoc::io::get_input_list<std::string>("test_input.txt", 2023, 4);
    parsed_input             data = parse_input(input_data);
    for (auto _ : state) {
        solve_part_1(data);
    }
}

static void BM_solve_part_2(benchmark::State &state) {
    std::vector<std::string> input_data = aoc::io::get_input_list<std::string>("input.txt", 2023, 4);
    parsed_input             data = parse_input(input_data);
    for (auto _ : state) {
        solve_part_2(data);
    }
}

BENCHMARK(BM_solve_part_1);
BENCHMARK(BM_solve_part_2);

BENCHMARK_MAIN();
