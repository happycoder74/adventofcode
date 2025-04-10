#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <cstddef>
#include <cstdint>
#include <deque>
#include <ranges>
#include <vector>

using Item = std::pair<int64_t, std::pair<int64_t, int64_t>>;

[[nodiscard]] auto parse_instructions(const std::vector<std::string> &instructions) -> std::deque<Item> {
    std::vector<int64_t> z1 = instructions.front()    //
                              | std::views::stride(2) //
                              | std::views::transform([](const auto &v) -> int64_t {
                                    return v - '0';
                                }) //
                              | std::ranges::to<std::vector>();
    std::vector<int64_t> z2 = instructions.front()    //
                              | std::views::drop(1)   //
                              | std::views::stride(2) //
                              | std::views::transform([](const auto &v) -> int64_t {
                                    return v - '0';
                                }) //
                              | std::ranges::to<std::vector>();

    if ((instructions.size() % 2) != 0) {
        z2.push_back(0);
    }

    auto rng = std::ranges::zip_view(z1, z2) //
               | std::views::enumerate       //
               | std::views::transform([](const auto &t) -> std::pair<int64_t, std::pair<int64_t, int64_t>> {
                     auto [ind, entry] = t;
                     auto [e1, e2]     = entry;
                     return {
                         ind, {e1, e2}
                     };
                 });

    return {rng.begin(), rng.end()};
}

[[nodiscard]] auto solve_part_1(const std::deque<Item> &instructions) -> size_t {
    size_t           result     = 0;
    auto             new_layout = std::vector<std::pair<int64_t, int64_t>>{};
    std::deque<Item> disk       = instructions;

    while (!disk.empty()) {
        auto item = disk.front();
        disk.pop_front();
        auto [index, entry] = item;

        new_layout.emplace_back(index, entry.first);
        if (disk.empty())
            break;

        auto last_item                = disk.back();
        auto [last_index, last_entry] = last_item;
        disk.pop_back();
        auto available = entry.second - last_entry.first;
        if (available == 0) {
            new_layout.emplace_back(last_index, last_entry.first);
        } else if (available < 0) {
            new_layout.emplace_back(last_index, last_entry.first + available);
            disk.push_back(Item{
                last_index, {-available, last_entry.second + last_entry.first + available}
            });
        } else {
            while (available >= 0) {
                new_layout.emplace_back(last_item.first, last_item.second.first);
                last_item = disk.back();
                disk.pop_back();
                available -= last_item.second.first;
            }
            auto [last_index, last_entry] = last_item;
            new_layout.emplace_back(last_index, last_entry.first + available);
            disk.push_back(Item{
                last_index, {-available, last_entry.second}
            });
        }
    }
    size_t counter{};

    for (auto blocks : new_layout) {
        for ([[maybe_unused]] auto c : std::views::iota(0, blocks.second)) {
            result += counter * blocks.first;
            counter += 1;
        }
    }

    return result;
}

[[nodiscard]] auto solve_part_2(const std::deque<Item> &instructions) -> size_t {

    auto new_layout = std::vector<Item>{instructions.begin(), instructions.end()};
    auto index{new_layout.size() - 1};
    while (index > 0) {
        auto last_item = new_layout[index];
        for (auto ii : std::ranges::iota_view(size_t{}, index)) {
            auto item = new_layout[ii];
            if (item.second.second >= last_item.second.first) {
                auto move_item = new_layout[index];
                new_layout.erase(new_layout.begin() + index);
                new_layout.insert(                    //
                    new_layout.begin() + int(ii) + 1, //
                    {
                        move_item.first, {move_item.second.first, item.second.second - move_item.second.first}
                });
                new_layout[ii] = {
                    item.first, {item.second.first, 0}
                };
                auto corr_item    = new_layout[index];
                new_layout[index] = {
                    corr_item.first, {corr_item.second.first, corr_item.second.second + last_item.second.first + last_item.second.second}
                };
                index += 1;
                break;
            }
        }
        index -= 1;
    }
    auto counter = size_t{};
    auto result  = size_t{};

    for (auto blocks : new_layout) {
        for ([[maybe_unused]] auto i : std::ranges::iota_view(int64_t{}, blocks.second.first)) {
            result += counter * blocks.first;
            counter += 1;
        }
        counter += blocks.second.second;
    }
    return result;
}

void solve_all(const std::vector<std::string> &instructions) {
    auto parsed_instructions = aoc::timer(parse_instructions, instructions, "Preparation time:");
    aoc::timer(1, solve_part_1, parsed_instructions);
    aoc::timer(2, solve_part_2, parsed_instructions);
}

auto main(int argc, char **argv) -> int {
    std::string   filename;
    constexpr int year = 2024;
    constexpr int day  = 9;

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
