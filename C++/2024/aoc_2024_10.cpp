#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstddef>
#include <deque>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ReturnType = std::tuple<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>, std::vector<std::vector<int>>>;

template <>
struct std::hash<std::pair<int, int>> {
    auto operator()(const pair<int, int> &v) const -> size_t {
        return std::size_t(v.first) << 32 | v.second;
    }
};

enum struct SolutionType {
    Distinct,
    NotDistinct
};

struct Node {
    std::pair<int, int> state;
};

struct Trail {
    std::vector<std::vector<int>>                                             m_data;
    std::vector<std::vector<int>>                                             m_contents;
    std::vector<std::pair<int, int>>                                          m_start;
    std::vector<std::pair<int, int>>                                          m_end;
    std::unordered_set<std::pair<int, int>>                                   m_goal;
    std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>> m_solution;

    Trail(const auto &t_trails, const auto &t_start, const auto &t_end) {
        m_data  = t_trails;
        m_start = t_start;
        m_end   = t_end;
        m_goal  = std::unordered_set<std::pair<int, int>>{m_end.begin(), m_end.end()};
    }

    [[nodiscard]] auto height() const {
        return static_cast<int>(m_data.size());
    }
    [[nodiscard]] auto width() const {
        return static_cast<int>(m_data.front().size());
    }

    [[nodiscard]] auto neighbours(const auto &state) const {
        auto [row, col] = state;
        auto candidates = std::array<std::pair<int, int>, 4>{
            {{std::pair(row - 1, col)}, //
             {std::pair(row + 1, col)},
             {std::pair(row, col - 1)},
             {std::pair(row, col + 1)}}
        };

        auto result = std::vector<std::pair<int, int>>{};
        for (auto &[r, c] : candidates) {
            if ((0 <= r) && (r < height()) && (0 <= c) && (c < width()) && (m_data[r][c] - m_data[row][col] == 1)) {
                result.emplace_back(r, c);
            }
        }

        return result;
    }

    [[nodiscard]] auto solve(SolutionType distinct = SolutionType::NotDistinct) -> int {
        auto count_trails = [&](const std::pair<int, int> &start, SolutionType sol_type) {
            auto queue = std::deque<Node>{};
            queue.emplace_back(start);
            auto explored = std::unordered_set<std::pair<int, int>>{};
            auto result   = int{};

            while (!queue.empty()) {
                Node node = queue.front();
                queue.pop_front();

                if (sol_type != SolutionType::Distinct) {
                    auto [it, ok] = explored.insert(node.state);
                    if (!ok)
                        continue;
                }
                if (m_goal.contains(node.state)) {
                    result += 1;
                    continue;
                }

                for (auto &state : neighbours(node.state)) {
                    if (std::ranges::none_of(queue, [&node](const auto &n) {
                            return node.state == n.state;
                        })) {
                        auto child = Node(state);
                        queue.emplace_front(child);
                    }
                }
            }
            return result;
        };

        auto result = std::transform_reduce(m_start.begin(), m_start.end(), int{}, std::plus{}, [&](const auto &p) {
            return count_trails(p, distinct);
        });
        return result;
    }
};

[[nodiscard]] auto parse_instructions([[maybe_unused]] const std::vector<std::string> &instructions) -> ReturnType {
    auto start  = std::vector<std::pair<int, int>>{};
    auto end    = std::vector<std::pair<int, int>>{};
    auto trails = std::vector<std::vector<int>>{};
    for (auto [irow, row] : std::views::enumerate(instructions)) {
        auto int_row = std::vector<int>{};
        int_row.reserve(row.size());
        std::ranges::transform(row, std::back_inserter(int_row), [](const auto c) {
            return static_cast<int>(c - '0');
        });
        trails.push_back(int_row);
        for (auto [icol, column] : std::views::enumerate(row)) {
            if (column == '0') {
                start.emplace_back(irow, icol);
            }
            if (column == '9') {
                end.emplace_back(irow, icol);
            }
        }
    }
    return {start, end, trails};
}

[[nodiscard]] auto solve_part_1([[maybe_unused]] const ReturnType &instructions) -> int {
    auto [start, end, trails] = instructions;
    auto trail                = Trail(trails, start, end);

    auto result = trail.solve(SolutionType::NotDistinct);
    return result;
}

[[nodiscard]] auto solve_part_2([[maybe_unused]] const ReturnType &instructions) -> int {

    auto [start, end, trails] = instructions;
    auto trail                = Trail(trails, start, end);

    auto result = trail.solve(SolutionType::Distinct);
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
    constexpr int day  = 10;

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
