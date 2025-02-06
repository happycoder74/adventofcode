#include "aoc_timer.hpp"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

static inline bool is_valid(const std::string &passport) {
    constexpr int n_keys = 7;

    std::array<std::string, n_keys> required_keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    for (auto &key : required_keys) {
        if (!passport.contains(key))
            return false;
    }

    return true;
}

static inline bool is_valid_part_2(const std::string &passport) {
    std::stringstream ss(passport);
    std::string       part;
    while (ss >> part) {
        std::string key   = part.substr(0, part.find(':'));
        std::string value = part.substr(part.find(':') + 1);
        if (key == "byr") {
            auto          birth_year = std::stoi(value);
            constexpr int byr_min    = 1920;
            constexpr int byr_max    = 2002;
            if (!((byr_min <= birth_year) && (birth_year <= byr_max))) {
                return false;
            }
        } else if (key == "iyr") {
            auto          issue_year = std::stoi(value);
            constexpr int iyr_min    = 2010;
            constexpr int iyr_max    = 2020;
            if (!((iyr_min <= issue_year) && (issue_year <= iyr_max))) {
                return false;
            }
        } else if (key == "eyr") {
            auto          exp_year = std::stoi(value);
            constexpr int eyr_min  = 2020;
            constexpr int eyr_max  = 2030;
            if (!((eyr_min <= exp_year) && (exp_year <= eyr_max))) {
                return false;
            }
        } else if (key == "hcl") {
            constexpr int val_size = 7;
            if (value.size() != val_size) {
                return false;
            }
            if (value[0] != '#') {
                return false;
            }
            for (auto &c : value.substr(1)) {
                if (!std::isdigit(c) && ((c < 'a') || (c > 'f'))) {
                    return false;
                }
            }
        } else if (key == "pid") {
            constexpr int n_pid = 9;
            if (value.size() != n_pid) {
                return false;
            }
            for (auto &c : value) {
                if (!std::isdigit(c)) {
                    return false;
                }
            }
        } else if (key == "hgt") {
            int num = std::stoi(value);
            if (value.ends_with("cm")) {
                constexpr int hgt_min = 150;
                constexpr int hgt_max = 193;
                if (!((hgt_min <= num) && (num <= hgt_max))) {
                    return false;
                }
            } else if (value.ends_with("in")) {
                constexpr int hgt_min = 59;
                constexpr int hgt_max = 76;
                if (!((hgt_min <= num) && (num <= hgt_max))) {
                    return false;
                }
            } else {
                return false;
            }
        } else if (key == "ecl") {
            constexpr int n_ecl       = 7;
            bool          valid_color = false;

            const std::array<std::string, n_ecl> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            for (auto &e : valid_ecl) {
                if (e == value) {
                    valid_color = true;
                    break;
                }
            }
            if (!valid_color) {
                return false;
            }
        }
    }
    return true;
}

int solve_part_1(const std::vector<std::string> &data) {
    auto result = data | std::views::transform([](auto &&pp) { return is_valid(pp) ? 1 : 0; });
    return std::reduce(result.begin(), result.end());
}

int solve_part_2(const std::vector<std::string> &data) {
    auto result = 0;
    for (auto &pp : data) {
        if (is_valid(pp)) {
            if (is_valid_part_2(pp)) {
                result++;
            }
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2020;
    const int   day  = 4;

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

    filepath = filepath / std::format("{}/{:02d}", year, day) / filename;
    std::ifstream ifs(filepath);

    std::vector<std::string> data;

    std::string passport{};
    for (std::string line; std::getline(ifs, line);) {
        if (line.size() == 0) {
            data.push_back(passport);
            passport.clear();
        } else {
            passport.append(" ");
            passport.append(line);
        }
    }
    data.push_back(passport);

    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    return 0;
}
