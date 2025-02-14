#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

enum struct Conversions {
    NS_TO_S  = 1000000000,
    NS_TO_MS = 1000000,
    NS_TO_US = 1000
};

using Clock    = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<double>;

namespace aoc {

template <class C, class R> inline auto convert_duration(std::chrono::duration<C, R> duration) -> const std::string {
    std::stringstream ss;

    auto unit = duration.count();
    if (unit > static_cast<int>(Conversions::NS_TO_S))
        ss << std::chrono::duration<double, std::ratio<1>>(duration);
    else if (unit > static_cast<int>(Conversions::NS_TO_MS))
        ss << std::chrono::duration<double, std::milli>(duration);
    else if (unit > static_cast<int>(Conversions::NS_TO_US))
        ss << std::chrono::duration<double, std::micro>(duration);
    else
        ss << duration;

    return ss.str();
}

template <typename T, typename U> void timer(int part, T (*func)(U &), U data, bool show_res = true) {
    auto              t1              = Clock::now();
    T                 result          = func(data);
    auto              t2              = Clock::now();
    const std::string duration_string = convert_duration(t2 - t1);
    if (show_res) {
        std::cout << std::format("Part {} answer: {:<20}{:>20}\n", part, result, duration_string);
    } else {
        std::cout << std::format("Time elapsed : {:>40}\n", duration_string);
    }
}

template <typename T, typename U> void timer(int part, T (*func)(const U &), U data, bool show_res = true) {
    auto t1     = Clock::now();
    T    result = func(data);
    auto t2     = Clock::now();

    const std::string duration_string = convert_duration(t2 - t1);
    if (show_res) {
        std::cout << std::format("Part {} answer: {:<20}{:>20}\n", part, result, duration_string);
    } else {
        std::cout << std::format("Time elapsed : {:>40}\n", duration_string);
    }
}

template <typename T, typename U, typename W> void timer(int part, T (*func)(U &, W), U data, W data2, bool show_res = true) {
    auto              t1              = Clock::now();
    T                 result          = func(data, data2);
    auto              t2              = Clock::now();
    const std::string duration_string = convert_duration(t2 - t1);
    if (show_res) {
        std::cout << std::format("Part {} answer: {:<20}{:>20}\n", part, result, duration_string);
    } else {
        std::cout << std::format("Time elapsed : {:>40}\n", duration_string);
    }
}

template <typename U> void timer(void (*func)(const U &), U data) {
    auto t1 = Clock::now();
    func(data);
    auto t2 = Clock::now();

    const std::string duration_string = convert_duration(t2 - t1);
    std::cout << std::format("Time elapsed : {:>40}\n", duration_string);
}


} // namespace aoc

#endif
