#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

void print_map(std::map<char, int> &m) {
    std::cout << "{\n";
    for (std::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::pair<char, int> p = *it;
        std::cout << "\t\"" << p.first << "\": " << p.second << "\n";
    }
}

bool is_two(const std::pair<char, int> &val) {
    return val.second == 2;
}
bool is_three(const std::pair<char, int> &val) {
    return val.second == 3;
}

int solve_part_1(const std::vector<std::string> &data) {
    std::pair<int, int> sum = std::make_pair(0, 0);

    for (std::vector<std::string>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::string         s = *it;
        std::map<char, int> s_map;
        for (std::string::iterator it2 = s.begin(); it2 != s.end(); ++it2) {
            s_map[*it2] += 1;
        }
        bool has_two   = (std::find_if(s_map.begin(), s_map.end(), is_two) != s_map.end());
        bool has_three = (std::find_if(s_map.begin(), s_map.end(), is_three) != s_map.end());
        sum.first += has_two;
        sum.second += has_three;
    }

    return sum.first * sum.second;
}

std::map<char, int> to_map(const std::string &str) {
    std::map<char, int> s_map;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        s_map[*it] += 1;
    }
    return s_map;
}

bool is_equal(const char a, const char b) {
    return a == b;
}

std::string solve_part_2(const std::vector<std::string> &data) {
    for (std::vector<std::string>::const_iterator it = data.begin(); it != data.end() - 1; ++it) {
        for (std::vector<std::string>::const_iterator it2 = it + 1; it2 != data.end(); ++it2) {
            const std::string &a = *it;
            const std::string &b = *it2;
            std::string        check;
            for (std::string::const_iterator csit1 = a.begin(), csit2 = b.begin(); csit1 != a.end() && csit2 != b.end(); ++csit1, ++csit2) {
                if (*csit1 == *csit2) {
                    check.push_back(*csit1);
                }
            }
            if (check.size() == a.size() - 1)
                return check;
        }
    }
    return "(none)";
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
    const int         day  = 2;

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
