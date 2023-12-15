#include <algorithm>
#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace day01::calories {
uint64_t max_calories(const std::vector<std::string> &data) {
    auto by_elf = data | std::views::lazy_split(std::string{}) | std::views::transform([](const auto &elf) -> uint64_t {
                      auto to_unsigned = [](const auto &in) { return std::stoull(in); };
                      auto rng = elf | std::views::transform(to_unsigned) | std::views::common; // std::reduce requires a common range
                      return std::reduce(rng.begin(), rng.end());
                  });
    auto it = std::ranges::max_element(by_elf);
    return *it; // and return
}
uint64_t top_three(const std::vector<std::string> &data) {
    auto by_elf = data | std::views::lazy_split(std::string{}) |          // group by elf: range{range{string}}
                  std::views::transform([](const auto &elf) -> uint64_t { // sum up the calories for each elf: range{uint64_t}
                      auto to_unsigned = [](const auto &in) { return std::stoull(in); };
                      auto rng = elf | std::views::transform(to_unsigned) | std::views::common; // range{string} -> range{uint64_t}
                      return std::reduce(rng.begin(), rng.end());                               // range{uint64_t} -> uint64_t
                  });
    std::vector<uint64_t> top(3);
    std::ranges::partial_sort_copy(by_elf, top, std::greater<>{});
    return std::reduce(top.begin(), top.end());
}
} // namespace day01::calories
int test() {
    std::vector<std::string> test_data{"1000", "2000", "3000", "", "4000", "", "5000", "6000", "", "7000", "8000", "9000", "", "10000"};
    assert(day01::calories::max_calories(test_data) == 24000);

    return 0;
}

int parse_and_run(std::string path) {
    std::vector<std::string> data;
    std::fstream             file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << std::quoted(path) << "\n";
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    namespace krn = std::chrono;
    using Clock = krn::high_resolution_clock;
    using ms = krn::microseconds;

    krn::time_point<Clock, ms> p = krn::time_point_cast<ms>(Clock::now());
    std::cout << "The elf with the maximum number of calorie is carrying " << day01::calories::max_calories(data) << " calories worth of food.\n";
    std::cout << std::setprecision(10) << krn::duration<double, std::ratio<1, 1000>>(Clock::now() - p) << std::endl;
    p = krn::time_point_cast<ms>(Clock::now());
    std::cout << "The top 3 elfs are carrying " << day01::calories::top_three(data) << " calories worth of food.\n";
    std::cout << std::setprecision(10) << krn::duration<double, std::ratio<1, 1000>>(Clock::now() - p) << std::endl;

    return 0;
}

int main(void) {
    return parse_and_run("c:/home/yy11510/projects/adventofcode/data/2022/01/input.txt");
}
