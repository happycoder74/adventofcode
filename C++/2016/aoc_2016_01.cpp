#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <array>
#include <unordered_set>

enum class Part {
    ONE,
    TWO
};

using Point = std::pair<int, int>;
using Step  = std::pair<char, int>;

template <>
struct std::hash<std::pair<int, int>> {
    inline auto operator()(const pair<int, int> &v) const -> size_t {
        return std::size_t(v.first) << 32 | v.second;
    }
};

auto manhattan_distance(const Point &p) -> unsigned int {
    return std::abs(p.first) + std::abs(p.second);
}

auto solution(const std::string &instructions, Part part) -> int {
    std::vector<Step>         step;
    Point                     pos = {0, 0};
    std::unordered_set<Point> locations{pos};

    std::array<Point, 4> directions{
        {{0, 1}, {-1, 0}, {0, -1}, {1, 0}}
    };

    std::stringstream ss{instructions};
    char              turn  = '\0';
    int               steps = 0;

    while (!ss.fail()) {
        ss >> turn >> steps;
        switch (turn) {
            case 'L':
                std::rotate(directions.begin(), directions.begin() + 1, directions.end());
                break;
            case 'R':
                std::rotate(directions.rbegin(), directions.rbegin() + 1, directions.rend());
                break;
        }

        auto current_direction = directions.front();

        if (part == Part::ONE) {
            pos.first  = pos.first + current_direction.first * steps;
            pos.second = pos.second + current_direction.second * steps;
        } else {
            for (auto step = 1; step <= steps; ++step) {
                pos.first += current_direction.first;
                pos.second += current_direction.second;
                if (locations.contains(pos)) {
                    return int(manhattan_distance(pos));
                } else {
                    locations.insert(pos);
                }
            }
        }
        ss.seekg(ss.tellg() + static_cast<std::stringstream::pos_type>(1));
    }
    return int(manhattan_distance(pos));
}

auto solve_part_1(const std::string &instructions) -> int {
    return solution(instructions, Part::ONE);
}

auto solve_part_2(const std::string &instructions) -> int {
    return solution(instructions, Part::TWO);
}

void solve_all(const std::string &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}

auto main(int argc, char **argv) -> int {
    std::string filename;

    constexpr int year = 2016;
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

    auto line = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(solve_all, line.front());

    return 0;
}
