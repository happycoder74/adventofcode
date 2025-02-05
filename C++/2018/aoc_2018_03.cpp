#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

struct InputData {
    std::pair<int, int> coords;
    std::pair<int, int> size;
};

const int SIZE_X = 1100;
const int SIZE_Y = 1100;

inline auto populate_map(const std::vector<InputData> &data) -> std::vector<int> {
    std::vector<int> m(SIZE_X * SIZE_Y, 0);
    for (const auto &it : data) {
        for (int r = 0; r < it.size.second; r++) {
            for (int c = 0; c < it.size.first; c++) {
                int x = it.coords.first + c;
                int y = it.coords.second + r;
                m[x + y * SIZE_X] += 1;
            }
        }
    }
    return m;
}

auto solve_part_1(const std::vector<InputData> &data) -> int {
    std::vector<int> m = populate_map(data);

    std::vector<int> vec;
    vec.reserve(data.size());
    std::ranges::transform(m, back_inserter(vec), [](const int p) { return p >= 2 ? 1 : 0; });
    return std::accumulate(vec.begin(), vec.end(), 0);
}

inline auto check_claim(const std::vector<int> &m, const InputData &claim) -> bool {
    for (int r = 0; r < claim.size.second; r++) {
        for (int c = 0; c < claim.size.first; c++) {
            int x = claim.coords.first + c;
            int y = claim.coords.second + r;
            if (m[x + y * SIZE_X] != 1) {
                return false;
            }
        }
    }
    return true;
}

auto solve_part_2(const std::vector<InputData> &data) -> int {
    std::vector<int> m = populate_map(data);

    auto it = std::ranges::find_if(data, [&m](const auto claim) { return check_claim(m, claim); });

    return int(it - data.begin()) + 1;
}

inline auto convert(const std::string &str) -> InputData {
    InputData         ret;
    std::stringstream ss(str);
    std::string       tmp;
    std::string       coords;
    std::string       size;
    char              tmp_c = ' ';

    ss >> tmp >> tmp >> coords >> size;
    std::stringstream ss_coords(coords);
    ss_coords >> ret.coords.first >> tmp_c >> ret.coords.second;
    std::stringstream ss_size(size);
    ss_size >> ret.size.first >> tmp_c >> ret.size.second;

    return ret;
}

auto parse_data(const std::vector<std::string> &data) -> std::vector<InputData> {
    std::vector<InputData> vec;
    std::transform(data.begin(), data.end(), std::back_inserter(vec), convert);

    return vec;
}

template <typename T>
void solve_all(const T &data) {
    std::vector<InputData> parsed_data = parse_data(data);

    aoc::timer(1, solve_part_1, parsed_data);
    aoc::timer(2, solve_part_2, parsed_data);
}

int main(int argc, char **argv) {
    std::string       filepath(std::getenv("AOC_DATA_LOCATION"));
    std::string       filename;
    std::stringstream ss;
    const int         year = 2018;
    const int         day  = 3;

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

    std::vector<std::string> data;

    while (std::getline(ifs, line)) {
        data.push_back(line);
    }

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);
    return 0;
}
