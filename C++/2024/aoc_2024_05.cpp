#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

auto parse_instructions(const std::vector<std::vector<std::string>> &instructions) -> std::pair<std::unordered_map<int, std::vector<int>>, std::vector<std::vector<int>>> {
    auto map = std::unordered_map<int, std::vector<int>>{};

    for (auto &rule : instructions.front()) {
        auto n = rule                     //
                 | std::views::split('|') //
                 | std::views::transform([](const auto &s) {
                       return std::stoi(std::string(s.begin(), s.end()));
                   });

        int n1 = *n.begin();
        int n2 = *std::next(n.begin(), 1);
        map[n1].emplace_back(n2);
    }

    auto vec = instructions.back() //
               | std::views::transform([](const auto &line) -> std::vector<int> {
                     auto rng = line                     //
                                | std::views::split(',') //
                                | std::views::transform([](const auto &part) -> int {
                                      return std::stoi(std::string(part.begin(), part.end()));
                                  }) //
                                | std::ranges::to<std::vector>();
                     return rng;
                 }) //
               | std::ranges::to<std::vector>();

    return std::make_pair(map, vec);
}

auto is_right_order(std::unordered_map<int, std::vector<int>> &map, const std::vector<int> &update) -> bool {
    for (const auto &[index, node] : std::views::zip(std::views::iota(0), update)) {
        auto targets = map[node];
        if (targets.size() == 0) {
            continue;
        }

        for (auto target : update | std::views::take(index)) {
            for (auto check_target : targets) {
                if (check_target == target) {
                    return false;
                }
            }
        }
    }
    return true;
}

auto reorder(std::unordered_map<int, std::vector<int>> &map, const std::vector<int> &update) -> int {
    std::vector<int> reordered_update(update.size());
    std::vector<int> return_update(update.size());

    for (const auto &n : std::views::zip(std::views::iota(0), update)) {
        auto [index, node] = n;
        auto targets       = map[node];
        for (auto target_1 : update) {
            for (auto target_2 : targets) {
                if (target_1 == target_2) {
                    reordered_update[index] += 1;
                }
            }
        }
    }

    for (auto p : std::views::zip(update, reordered_update)) {
        auto &[v1, v2]    = p;
        return_update[v2] = v1;
    }

    return return_update[return_update.size() / 2];
}

auto solve_part_1(const std::pair<std::unordered_map<int, std::vector<int>>, std::vector<std::vector<int>>> &instructions) -> int {
    auto map     = instructions.first;
    auto updates = instructions.second;

    int result = std::accumulate(updates.begin(), updates.end(), int{}, [&map](const auto a, const auto &update) -> int {
        if (is_right_order(map, update)) {
            return a + update[update.size() / 2];
        }
        return a;
    });

    return result;
}

auto solve_part_2(const std::pair<std::unordered_map<int, std::vector<int>>, std::vector<std::vector<int>>> &instructions) -> int {
    auto map     = instructions.first;
    auto updates = instructions.second;

    int result = std::accumulate(updates.begin(), updates.end(), 0, [&map](const auto a, const auto &update) {
        if (!is_right_order(map, update)) {
            return a + reorder(map, update);
        }
        return a;
    });

    return result;
}

void solve_all(const std::vector<std::vector<std::string>> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 5;

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

    auto instructions = aoc::io::get_input_groups<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, instructions);

    return 0;
}
