#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace aoc_2015_03 {

class SantaAgent {
  private:
    std::map<std::pair<int, int>, int> coords;

    std::pair<int, int> loc = {0, 0};

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
        coords[loc] += 1;
    };
    int get_locations() {
        return coords.size();
    };
    std::map<std::pair<int, int>, int> export_coords() {
        return coords;
    }
};

int solve_part_1(const std::vector<std::string> &instructions) {
    SantaAgent santa;

    for (auto &inst : instructions.front()) {
        santa.make_move(inst);
    }
    return santa.get_locations();
}

int solve_part_2(const std::vector<std::string> &instructions) {
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

    std::map<std::pair<int, int>, int> santa_visited = santa.export_coords();
    std::map<std::pair<int, int>, int> robosanta_visited = robosanta.export_coords();

    santa_visited.insert(robosanta_visited.begin(), robosanta_visited.end());
    return santa_visited.size();
}

int solve_all(const std::vector<std::string> &instructions) {
    aoc::timer(1, solve_part_1, instructions, true);
    aoc::timer(2, solve_part_2, instructions, true);
    return 0;
}
} // namespace aoc_2015_03

int main(int argc, char **argv) {
    std::vector<std::string> data;

    const int year = 2015;
    const int day = 3;

    std::string filename;
    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }
    data = aoc::io::get_input_list<std::string>(filename, year, day);

    aoc::io::header(year, day);
    aoc::timer(0, aoc_2015_03::solve_all, data, 0);

    return 0;
}
