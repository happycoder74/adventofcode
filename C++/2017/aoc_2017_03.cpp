#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include "aoc_types.hpp"
#include <numeric>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

namespace aoc_2017_03 {

class Spiral {
  private:
    aoc::Grid           grid;
    std::pair<int, int> position;

  public:
    explicit Spiral() {
        position = {0, 0};
        grid.insert(position, 1);
    }
    void step() {
        int x = position.first;
        int y = position.second;

        if ((x > 0) && (std::abs(x) > abs(y))) {
            y += 1;
        } else if ((x < 0) && ((abs(x) > abs(y)) || (x == -y))) {
            y -= 1;
        } else if ((y > 0) && ((abs(y) > abs(x)) || (x == y))) {
            x -= 1;
        } else {
            x += 1;
        }

        position = {x, y};
    }

    auto grid_value() {
        return grid.get_value(position);
    }

    void update_value() {
        auto res = grid.deltas
                   // clang-format off
                   | std::views::transform([this](const auto &p) {
                           auto result = grid.get_value({position.first + p.first, position.second + p.second});
                           return result;
                     })
                   | std::views::common;
        // clang-format on

        unsigned result = std::reduce(res.begin(), res.end());
        grid.insert(position, result);
    }

    unsigned distance() {
        return abs(position.first) + abs(position.second);
    }
};

auto solve_part_1(const std::vector<std::string> &input) {
    unsigned target = std::stoul(input[0]);
    Spiral   s;

    for (unsigned i = 1; i < target; i++) {
        s.step();
    }

    return int(s.distance());
}

auto solve_part_2(const std::vector<std::string> &input) {
    unsigned target = std::stoul(input.front());
    Spiral   s;

    while (s.grid_value() <= target) {
        s.step();
        s.update_value();
    }

    return int(s.grid_value());
}

auto solve_all(const std::vector<std::string> &input) {
    aoc::timer(1, solve_part_1, input);
    aoc::timer(2, solve_part_2, input);
}
} // namespace aoc_2017_03

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2017;
    const int   day  = 3;

    std::vector<std::string> data;

    auto args = std::span(argv, argc);
    if (argc > 1) {
        filename = args[1];
    } else {
        filename = "input.txt";
    }

    data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(aoc_2017_03::solve_all, data);

    return 0;
}
