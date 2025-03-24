#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <ranges>
#include <string>

auto parse_input(const std::string &instructions) {
    int  i   = 0;
    auto rng = instructions //
               | std::views::transform([&](auto &c) mutable {
                     if (c == '(') {
                         i += 1;
                     } else {
                         i -= 1;
                     }
                     return i;
                 }) //
               | std::views::common;
    return std::vector<int>(rng.begin(), rng.end());
}

auto solve_part_1(const std::vector<int> &instructions) -> int {
    return instructions.back();
}

auto solve_part_2(const std::vector<int> &instructions) -> int {
#ifdef __cpp_lib_ranges_enumerate
    auto enumerated_rng = instructions | std::views::enumerate;
#else
    auto enumerated_rng = std::views::zip(std::views::iota(0), instructions);
#endif
    auto rng = enumerated_rng //
               | std::views::filter([](const auto &kv) {
                     auto &[k, v] = kv;
                     return v < 0;
                 }) //
               | std::views::take(1) | std::views::keys;
    auto index = rng.front();
    return int(index + 1);
}

void solve_all(const std::string &instructions) {
    auto parsed_instructions = aoc::timer(parse_input, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string filename;

    constexpr int year = 2015;
    constexpr int day  = 1;

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

    std::vector<std::string> line = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, line.front());

    return 0;
}
