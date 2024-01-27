#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <map>
#include <numeric>
#include <string>
#include <vector>

namespace aoc_2023_08 {

using node_t = std::pair<std::string, std::string>;
using network_t = std::map<std::string, node_t>;
using instructions_t = std::string;
using aoc_data_t = std::vector<std::string>;

std::pair<instructions_t, network_t> clean_input(aoc_data_t input_data) {
    network_t      network;
    instructions_t instructions = input_data[0];

    for (aoc_data_t::iterator it = input_data.begin() + 2; it < input_data.end(); it++) {
        auto        row = *it;
        std::string node = row.substr(0, 3);

        std::pair<std::string, std::string> destination;

        destination.first = row.substr(7, 3);
        destination.second = row.substr(12, 3);
        network[node] = destination;
    }
    return std::make_pair(instructions, network);
}

std::int64_t get_steps(std::string node, instructions_t instructions, network_t network, int part) {
    std::int64_t steps_required = 0;

    char step;

    while (true) {
        char step = instructions[0];
        std::rotate(instructions.begin(), instructions.begin() + 1, instructions.end());
        steps_required++;
        if (step == 'R') {
            node = network[node].second;
        } else {
            node = network[node].first;
        }
        if (part == 1) {
            if (node == "ZZZ") {
                break;
            }
        } else {
            if (node[2] == 'Z') {
                break;
            }
        }
    }
    return steps_required;
}

std::int64_t solve_part_1(const std::pair<instructions_t, network_t> &data) {
    std::int64_t steps = 0;

    std::string    node = "AAA";
    instructions_t instructions = data.first;
    network_t      network = data.second;

    return get_steps(node, instructions, network, 1);
}

std::int64_t lcm(std::int64_t a, std::int64_t b) {
    return (a * b) / (std::gcd(a, b));
}

std::int64_t solve_part_2(const std::pair<instructions_t, network_t> &data) {
    std::int32_t   prio_sum = 0;
    instructions_t instructions = data.first;
    network_t      network = data.second;

    std::vector<std::int64_t> steps_required;

    for (auto &node : network) {
        if (node.first.ends_with("A")) {
            steps_required.push_back(get_steps(node.first, instructions, network, 2));
        }
    }

    return std::accumulate(steps_required.begin(), steps_required.end(), steps_required[0], std::lcm<std::int64_t, std::int64_t>);
}

void *solve_all(const std::pair<instructions_t, network_t> &data) {
    aoc::timer(1, solve_part_1, data, 1);
    aoc::timer(2, solve_part_2, data, 1);
    return NULL;
}

} // namespace aoc_2023_08

int main(int argc, char **argv) {
    std::string filename;
    const int   year = 2023;
    const int   day = 8;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    std::vector<std::string> data = aoc::io::get_input_list<std::string>(filename, year, day);

    auto parsed_data = aoc_2023_08::clean_input(data);
    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    aoc::timer(0, aoc_2023_08::solve_all, parsed_data, 0);

    return 0;
}
