#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <vector>

template <>
struct std::hash<std::pair<uint64_t, uint64_t>> {
    auto operator()(const pair<uint64_t, uint64_t> &v) const -> size_t {
        return std::hash<uint64_t>()(v.first) ^ std::hash<uint64_t>()(v.second);
    }
};

template <class T>
auto divmod(T a, T b) -> std::pair<T, T> {
    auto left  = a / b;
    auto right = a % b;
    return {left, right};
}

struct StoneBlinker {
    std::vector<uint64_t>                                       stones;
    std::unordered_map<std::pair<uint64_t, uint64_t>, uint64_t> lookup;

    StoneBlinker(const std::vector<uint64_t> &t_stones) : stones(t_stones) {
    }

    std::vector<uint64_t> blink(uint64_t stone) {
        auto result = std::vector<uint64_t>{};
        if (stone == 0) {
            result.push_back(1);
        } else {
            auto no_digits = static_cast<uint64_t>(std::floor(std::log10(stone))) + 1;
            if (no_digits % 2 == 0) {
                auto [left, right] = divmod(stone, static_cast<uint64_t>(pow(10, no_digits / 2)));
                result.push_back(left);
                result.push_back(right);
            } else {
                result.push_back(2024 * stone);
            }
        }
        lookup[{stone, 1}] = static_cast<uint64_t>(result.size());
        return result;
    }
    uint64_t dp(auto stone, uint64_t times) {
        if (lookup.contains({stone, times})) {
            return lookup[{stone, times}];
        } else {
            auto stone_result = blink(stone);
            if (times > 1) {
                auto sum = uint64_t{};
                for (auto s : stone_result) {
                    auto part = dp(s, times - 1);
                    sum += part;
                }
                lookup[{stone, times}] = sum;
            }
            auto val = lookup[{stone, times}];
            return val;
        }
    }
    uint64_t solve(auto iterations = 1) {
        return std::accumulate(stones.begin(), stones.end(), uint64_t{}, [&](const uint64_t a, const uint64_t stone) {
            return a + dp(stone, iterations);
        });
    }
};

[[nodiscard]] auto parse_instructions(const std::vector<std::string> &instructions) -> std::vector<uint64_t> {
    auto rng = instructions.front()     //
               | std::views::split(' ') //
               | std::views::transform([](const auto &s) -> uint64_t {
                     return std::stoull(std::string(s.begin(), s.end()));
                 }) //
               | std::ranges::to<std::vector>();

    return rng;
}

[[nodiscard]] auto solve_part_1(const std::vector<uint64_t> &instructions) -> uint64_t {
    auto       s          = StoneBlinker(instructions);
    const auto iterations = 25;
    return s.solve(iterations);
}

[[nodiscard]] auto solve_part_2(const std::vector<uint64_t> &instructions) -> uint64_t {
    auto       s          = StoneBlinker(instructions);
    const auto iterations = 75;
    return s.solve(iterations);
}

void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 11;

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
