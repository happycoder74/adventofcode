#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <cstdlib>
#include <iostream>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

template <>
struct std::hash<std::pair<int, int>> {
    inline auto operator()(const pair<int, int> &v) const -> size_t {
        return std::size_t(v.first) << 32 | v.second;
    }
};

namespace aoc_2015_03 {

class SantaAgent {
  private:
    std::unordered_map<std::pair<int, int>, int> coords;
    std::pair<int, int>                          loc = {0, 0};

  public:
    SantaAgent() {
        coords[loc] += 1;
    };

    void make_move(char direction) {
        switch (direction) {
            case '^':
                loc.first++;
                break;
            case '>':
                loc.second++;
                break;
            case 'v':
                loc.first--;
                break;
            case '<':
                loc.second--;
                break;
            default:
                std::cerr << "Invalid instruction" << '\n';
                exit(EXIT_FAILURE);
        }
        coords.insert({loc, 1});
    };

    auto get_locations() -> int {
        return int(coords.size());
    };

    auto export_coords() -> std::unordered_map<std::pair<int, int>, int> {
        return coords;
    }
};

auto solve_part_1(const std::vector<std::string> &instructions) -> int {
    SantaAgent santa;

    for (auto &inst : instructions.front()) {
        santa.make_move(inst);
    }
    return santa.get_locations();
}

auto solve_part_2(const std::vector<std::string> &instructions) -> int {
    SantaAgent santa;
    SantaAgent robosanta;

    const std::string &instruction = instructions.front();
    for (std::string::const_iterator inst = instruction.begin(); inst != instruction.end(); inst++) {
        if ((inst - instruction.begin()) % 2 == 0) {
            santa.make_move(*inst);
        } else {
            robosanta.make_move(*inst);
        }
    }

    std::unordered_map<std::pair<int, int>, int> santa_visited     = santa.export_coords();
    std::unordered_map<std::pair<int, int>, int> robosanta_visited = robosanta.export_coords();

    santa_visited.insert(robosanta_visited.begin(), robosanta_visited.end());
    return int(santa_visited.size());
}

void solve_all(const std::vector<std::string> &instructions) {
    aoc::timer(1, solve_part_1, instructions);
    aoc::timer(2, solve_part_2, instructions);
}
} // namespace aoc_2015_03

auto main(int argc, char **argv) -> int {
    std::vector<std::string> data;

    constexpr int year = 2015;
    constexpr int day  = 3;
    std::string   filename;

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
    data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(aoc_2015_03::solve_all, data);

    return 0;
}
