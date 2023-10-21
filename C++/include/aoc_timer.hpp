#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include <chrono>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

namespace aoc {

template <typename T> void timer(int part, T (*func)(std::string), std::string data, bool show_res) {
    auto                          t1 = Clock::now();
    T                             result = func(data);
    auto                          t2 = Clock::now();
    std::chrono::duration<double> diff = (t2 - t1);
    double                        elapsed = diff.count();
    double                        elapsed_unit = elapsed > 0.1 ? elapsed : elapsed * 1000;
    if (show_res) {
        std::cout << std::format("Part {} answer: {}\r\033[35C( {:6.3f} {} )\n", part, result, elapsed_unit, elapsed > 0.1 ? "s" : "ms");
    } else {
        std::cout << std::format("Time elapsed:\r\033[35C( {:6.3f} {} )\n", elapsed_unit, elapsed > 0.1 ? "s" : "ms");
    }
}

template <typename T> void timer(int part, T (*func)(std::vector<T>), std::vector<T> data, bool show_res) {
    auto                          t1 = Clock::now();
    T                             result = func(data);
    auto                          t2 = Clock::now();
    std::chrono::duration<double> diff = (t2 - t1);
    double                        elapsed = diff.count();
    double                        elapsed_unit = elapsed > 0.1 ? elapsed : elapsed * 1000;
    if (show_res) {
        std::cout << std::format("Part {} answer: {}\r\033[35C( {:6.3f} {} )\n", part, result, elapsed_unit, elapsed > 0.1 ? "s" : "ms");
    } else {
        std::cout << std::format("Time elapsed:\r\033[35C( {:6.3f} {} )\n", elapsed_unit, elapsed > 0.1 ? "s" : "ms");
    }
}

template <typename ClockType, typename Resolution> std::string elapsed_time(const std::chrono::time_point<ClockType, Resolution> t1, const std::chrono::time_point<ClockType, Resolution> t2);

} // namespace aoc

#endif
