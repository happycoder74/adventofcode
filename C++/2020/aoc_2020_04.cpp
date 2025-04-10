#include "aoc_timer.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static inline auto is_valid(const std::string &passport) -> bool {
    constexpr int n_keys = 7;

    static constexpr std::array<std::string, n_keys> required_keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    return std::all_of(required_keys.begin(), required_keys.end(), [&passport](auto &r) {
        return passport.contains(r);
    });
}

static auto is_valid_part_2(const std::string &passport) -> bool {
    enum struct PP_CLASS {
        CID,
        BYR,
        EYR,
        IYR,
        HCL,
        PID,
        HGT,
        ECL
    };

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

    auto validate_byr = [](const auto &value) {
        return (byr_min <= std::stoi(value)) && (std::stoi(value) <= byr_max);
    };
    auto validate_iyr = [](const auto &value) {
        return (iyr_min <= std::stoi(value)) && (std::stoi(value) <= iyr_max);
    };
    auto validate_eyr = [](const auto &value) {
        return (eyr_min <= std::stoi(value)) && (std::stoi(value) <= eyr_max);
    };
    auto validate_hcl = [](const auto &value) {
        if ((value.size() != hcl_len) || (value[0] != '#')) {
            return false;
        }
        return std::all_of(value.begin() + 1, value.end(), [](auto &c) {
            return (std::isdigit(c) || (('a' <= c) && (c <= 'f')));
        });
    };
    auto validate_pid = [](const auto &value) {
        return (value.size() == pid_len) && (std::find_if(value.begin(), value.end(), [](auto &c) {
                                                 return std::isdigit(c);
                                             }) != value.end());
    };
    auto validate_ecl = [](const auto &value) {
        const std::unordered_set<std::string> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        return valid_ecl.find(value) != valid_ecl.end();
    };
    auto validate_hgt = [](const auto &value) {
        int num = std::stoi(value);

        if (value.ends_with("cm") && (hgt_min_cm <= num) && (num <= hgt_max_cm)) {
            return true;
        } else if (value.ends_with("in") && (hgt_min_in <= num) && (num <= hgt_max_in)) {
            return true;
        }
        return false;
    };
    // clang-format off
    std::unordered_map<std::string, PP_CLASS> validators = {
        {"cid", PP_CLASS::CID},
        {"byr", PP_CLASS::BYR},
        {"iyr", PP_CLASS::IYR},
        {"eyr", PP_CLASS::EYR},
        {"hcl", PP_CLASS::HCL},
        {"pid", PP_CLASS::PID},
        {"ecl", PP_CLASS::ECL},
        {"hgt", PP_CLASS::HGT}};

    auto result = passport
        | std::views::split(std::string_view(" "))
        | std::views::transform([&](auto r) {
                auto part    = r | std::views::split(std::string_view(":"));
                auto keypair = std::ranges::to<std::vector<std::string>>(part);
                switch (validators[keypair[0]]) {
                    case PP_CLASS::CID:
                        return true;
                    case PP_CLASS::BYR:
                        return validate_byr(keypair[1]);
                    case PP_CLASS::IYR:
                        return validate_iyr(keypair[1]);
                    case PP_CLASS::EYR:
                        return validate_eyr(keypair[1]);
                    case PP_CLASS::HCL:
                        return validate_hcl(keypair[1]);
                    case PP_CLASS::PID:
                        return validate_pid(keypair[1]);
                    case PP_CLASS::ECL:
                        return validate_ecl(keypair[1]);
                    case PP_CLASS::HGT:
                        return validate_hgt(keypair[1]);
                    default:
                        return false;
                        break;
                }
            });

    // clang-format on

    return std::ranges::all_of(result, [](const auto &v) {
        return v;
    });
}

auto solve_part_1(const std::vector<std::string> &data) -> int {
    auto result = data | std::views::transform([](auto &&pp) {
                      return is_valid(pp) ? 1 : 0;
                  });
    return std::reduce(result.begin(), result.end());
}

auto solve_part_2(const std::vector<std::string> &data) -> int {
    auto result = 0;
    for (auto &pp : data) {
        if (is_valid(pp) && is_valid_part_2(pp)) {
            result++;
        }
    }
    return result;
}

auto main(int argc, char *argv[]) -> int {
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

    filepath = filepath / std::format("{}", year) / std::format("{:02d}", day) / filename;
    std::ifstream ifs(filepath);

    std::vector<std::string> data;
    std::vector<std::string> passport{};

    auto join_string = [](auto str) {
#ifdef __cpp_lib_ranges_join_with
        auto joined = str | std::views::join_with(' ');
#else
        auto joined = str | std::views::transform([](const auto &s) {
                          auto ret_s = std::string(s);
                          ret_s.append(" ");
                          return ret_s;
                      });
#endif
        auto return_string = std::accumulate(joined.begin(), joined.end(), std::string{});
        return_string.pop_back();
        return return_string;
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

    std::cout << std::format("{:=<55}\n", "");
    std::cout << std::format("Solution for {:d}, day {:02d}\n", year, day);
    std::cout << std::format("{:-<55}\n", "");
    aoc::timer(1, solve_part_1, data);
    aoc::timer(2, solve_part_2, data);
    std::cout << std::format("{:-<55}\n", "");
    return 0;
}
