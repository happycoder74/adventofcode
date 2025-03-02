#include "aoc_timer.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <functional>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static inline bool is_valid(const std::string &passport) {
    constexpr int n_keys = 7;

    static constexpr std::array<std::string, n_keys> required_keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    return std::all_of(required_keys.begin(), required_keys.end(), [&passport](auto &r) { return passport.contains(r); });
}

static inline bool is_valid_part_2(const std::string &passport) {
    constexpr int byr_min    = 1920;
    constexpr int byr_max    = 2002;
    constexpr int iyr_min    = 2010;
    constexpr int iyr_max    = 2020;
    constexpr int eyr_min    = 2020;
    constexpr int eyr_max    = 2030;
    constexpr int hcl_len    = 7;
    constexpr int pid_len    = 9;
    constexpr int hgt_min_cm = 150;
    constexpr int hgt_max_cm = 193;
    constexpr int hgt_min_in = 59;
    constexpr int hgt_max_in = 76;

    // clang-format off
    const std::unordered_map<std::string, std::function<bool(const std::string &)>> validators = {
        {"cid", [](const auto &value) { return true; }},
        {"byr", [](const auto &value) { return (byr_min <= std::stoi(value)) && (std::stoi(value) <= byr_max); }},
        {"iyr", [](const auto &value) { return (iyr_min <= std::stoi(value)) && (std::stoi(value) <= iyr_max); }},
        {"eyr", [](const auto &value) { return (eyr_min <= std::stoi(value)) && (std::stoi(value) <= eyr_max); }},
        {"hcl", [](const auto &value) {
                        if ((value.size() != hcl_len) || (value[0] != '#')) {
                            return false;
                        }
                        return std::all_of(value.begin() + 1, value.end(), [](auto &c) {
                                return (std::isdigit(c) || (('a' <= c) && (c <= 'f')));
                                });
                    }},
        {"pid", [](const auto &value) {
                        return (value.size() == pid_len) && (std::find_if(value.begin(), value.end(), [] (auto &c) { return std::isdigit(c); }) != value.end());
                    }},
        {"ecl", [](const auto &value) {
                        const std::unordered_set<std::string> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
                        return valid_ecl.find(value) != valid_ecl.end();
                    }},
        {"hgt", [](const auto &value) {
                        int num = std::stoi(value);

                        if (value.ends_with("cm") && (hgt_min_cm <= num) && (num <= hgt_max_cm)) {
                                return true;
                        } else if (value.ends_with("in") && (hgt_min_in <= num) && (num <= hgt_max_in)) {
                                return true;
                        }
                        return false;
                    }}
    };

    auto result = passport
        | std::views::split(std::string_view(" "))
        | std::views::transform([&validators](auto r) {
                auto part    = r | std::views::split(std::string_view(":"));
                auto keypair = std::ranges::to<std::vector<std::string>>(part);
                auto func    = validators.at(keypair[0]);
                return func(keypair[1]);
            });

    // clang-format on

    return std::ranges::all_of(result, [](const auto &v) { return v; });
}

int solve_part_1(const std::vector<std::string> &data) {
    auto result = data | std::views::transform([](auto &&pp) { return is_valid(pp) ? 1 : 0; });
    return std::reduce(result.begin(), result.end());
}

int solve_part_2(const std::vector<std::string> &data) {
    auto result = 0;
    for (auto &pp : data) {
        if (is_valid(pp) && is_valid_part_2(pp)) {
            result++;
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
    std::vector<std::string> passport{};

    auto join_string = [](auto str) {
        auto joined = str | std::views::join_with(' ');
        return std::string(joined.begin(), joined.end());
    };

    for (std::string line; std::getline(ifs, line);) {
        if (line.size() == 0) {
            data.push_back(join_string(passport));
            passport.clear();
        } else {
            passport.push_back(line);
        }
    }
    data.push_back(join_string(passport));

    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    return 0;
}
