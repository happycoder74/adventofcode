#include "aoc_io.hpp"
#include "aoc_string.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <execution>
#include <functional>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <>
struct std::hash<std::pair<int, int>> {
    auto operator()(const pair<int, int> &v) const -> size_t {
        return std::size_t(v.first) << 32 | v.second;
    }
};

struct Itertools {
  public:
    template <class T>
    static auto combinations(const T &iterable, int repeat) -> std::vector<T> {
        auto n = int(iterable.size());
        if (repeat > n) {
            return std::vector<T>{};
        }
        auto combo   = std::vector<T>{};
        auto indices = std::ranges::iota_view(0, repeat) | std::ranges::to<std::vector>();
        combo.push_back(T(iterable.begin(), iterable.begin() + repeat));
        bool loop_ok = true;
        while (loop_ok) {
            int  i{};
            bool nobreak = true;
            for (auto ii : std::views::iota(0, repeat) | std::views::reverse) {
                if (indices[ii] != ii + n - repeat) {
                    i       = ii;
                    nobreak = false;
                    break;
                }
            }
            if (nobreak) {
                loop_ok = false;
                break;
            }
            indices[i] += 1;
            for (auto jj : std::views::iota(i + 1, int(repeat))) {
                indices[jj] = indices[jj - 1] + 1;
            }
            auto tmp = T{};
            for (auto index : indices) {
                tmp.push_back(iterable[index]);
            }
            combo.emplace_back(tmp);
        }
        return combo;
    }
};

using Antenna = std::unordered_map<char, std::vector<std::pair<int, int>>>;

auto parse_instructions(const std::vector<std::string> &instructions) -> std::pair<Antenna, std::pair<int, int>> {
    auto antennas = Antenna{};
    auto limits   = std::pair<int, int>{instructions.size(), instructions.front().size()};
    for (auto [row, line] : std::ranges::zip_view(std::ranges::iota_view(0), instructions)) {
        for (auto [col, token] : std::ranges::zip_view(std::ranges::iota_view(0), line)) {
            if (token != '.') {
                antennas[token].emplace_back(row, col);
            }
        }
    }

    return {antennas, limits};
}

bool in_bound(auto &node, auto &limits) {
    if ((node.first < 0) || (node.first >= limits.first))
        return false;
    if ((node.second < 0) || (node.second >= limits.second))
        return false;
    return true;
}

auto solve_part_1(const std::pair<Antenna, std::pair<int, int>> &instructions) -> int {
    auto antinodes   = std::unordered_set<std::pair<int, int>>{};
    auto antenna_map = instructions.first;

    for (auto &[v1, antennas] : antenna_map) {
        auto combinations = Itertools::combinations(antennas, 2);
        auto offsets      = std::vector<std::pair<int, int>>{};
        offsets.reserve(combinations.size());
        std::ranges::transform(combinations, std::back_inserter(offsets), [](const auto &vec) -> std::pair<int, int> {
            auto v1 = vec.front();
            auto v2 = vec.back();
            return {v1.first - v2.first, v1.second - v2.second};
        });
        for (auto [offset, pair] : std::ranges::zip_view(offsets, combinations)) {
            auto node = std::pair<int, int>{};
            node      = {pair.front().first + offset.first, pair.front().second + offset.second};
            if (in_bound(node, instructions.second))
                antinodes.insert(node);
            node = {pair.back().first - offset.first, pair.back().second - offset.second};
            if (in_bound(node, instructions.second))
                antinodes.insert(node);
        }
    }

    return int(antinodes.size());
}

auto solve_part_2(const std::pair<Antenna, std::pair<int, int>> &instructions) -> int {
    auto antinodes   = std::unordered_set<std::pair<int, int>>{};
    auto antenna_map = instructions.first;

    for (auto &[v1, antennas] : antenna_map) {
        auto combinations = Itertools::combinations(antennas, 2);
        for (auto &pair : combinations) {
            antinodes.insert(pair.front());
            antinodes.insert(pair.back());
            auto offset = std::pair<int, int>{pair.front().first - pair.back().first, pair.front().second - pair.back().second};
            auto node   = std::pair<int, int>{};
            node        = {pair.front().first + offset.first, pair.front().second + offset.second};
            while (in_bound(node, instructions.second)) {
                antinodes.insert(node);
                node.first += offset.first;
                node.second += offset.second;
            }
            node = {pair.back().first - offset.first, pair.back().second - offset.second};
            while (in_bound(node, instructions.second)) {
                antinodes.insert(node);
                node.first -= offset.first;
                node.second -= offset.second;
            }
        }
    }

    return int(antinodes.size());
}

void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 8;

    auto args = std::span(argv, argc);
    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    auto instructions = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
