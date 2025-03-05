#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <numeric>
#include <set>
#include <vector>

int solve_part_1(const std::vector<int> &data) {
    return std::accumulate(data.begin(), data.end(), int());
}

int solve_part_2(const std::vector<int> &data) {
    std::set<int> frequencies;
    int           frequency = 0;
    frequencies.insert(frequency);
    while (true) {
        for (std::vector<int>::const_iterator it = data.begin(); it != data.end(); it++) {
            frequency += *it;
            if (frequencies.find(frequency) != frequencies.end())
                return frequency;
            frequencies.insert(frequency);
        }
    }
    return 0;
}

template <typename T>
void solve_all(const T &data) {
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
}

int main(int argc, char **argv) {
    std::string       filepath(std::getenv("AOC_DATA_LOCATION"));
    std::string       filename;
    std::stringstream ss;
    const int         year = 2018;
    const int         day  = 1;

    if (argc > 1) {
        if (std::string(argv[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = argv[1];
        }
    } else {
        filename = "input.txt";
    }

    ss << filepath << "/" << year << "/" << std::setfill('0') << std::setw(2) << day << "/" << filename;
    filepath = ss.str();
    std::ifstream ifs(filepath.c_str());
    std::string   line;

    std::vector<int> data;

    while (std::getline(ifs, line)) {
        data.push_back(std::atoi(line.c_str()));
    }

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);
    return 0;
}
