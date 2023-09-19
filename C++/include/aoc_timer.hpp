#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <fmt/core.h>

typedef std::chrono::high_resolution_clock Clock;

namespace aoc {

template<typename T>
void timer(int part, T(*func)(std::string), std::string data, bool show_res) {
    auto t1 = Clock::now();
    T result = func(data);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = (t2 - t1);
    double elapsed = diff.count();
    double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000;
    if (show_res) {
        std::cout << fmt::format("Part {} answer: {}\r\033[35C( {:6.3f} {} )\n",
                                 part, result, elapsed_unit, elapsed > 0.1? "s":"ms");
    } else {
        std::cout << fmt::format("Time elapsed:\r\033[35C( {:6.3f} {} )\n",
                                 elapsed_unit, elapsed > 0.1? "s":"ms");
    }
}

template<typename T>
void timer(int part, T(*func)(std::vector<T>), std::vector<T> data, bool show_res) {
    auto t1 = Clock::now();
    T result = func(data);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = (t2 - t1);
    double elapsed = diff.count();
    double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000;
    if (show_res) {
        std::cout << fmt::format("Part {} answer: {}\r\033[35C( {:6.3f} {} )\n",
                                 part, result, elapsed_unit, elapsed > 0.1? "s":"ms");
    } else {
        std::cout << fmt::format("Time elapsed:\r\033[35C( {:6.3f} {} )\n",
                                 elapsed_unit, elapsed > 0.1? "s":"ms");
    }
}

} // namespace aoc 
    


#define TIMER(part, func, TYPE, show_res) \
    { \
        auto t1 = Clock::now(); \
        TYPE result = func; \
        auto t2 = Clock::now(); \
        std::chrono::duration<double> diff = (t2 - t1); \
        double elapsed = diff.count(); \
		double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
            std::cout << fmt::format("Part {} answer: {}\r\033[35C( {:6.3f} {} )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
            std::cout << fmt::format("Time elapsed:\r\033[35C( {:6.3f} {} )\n", \
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
    }

#define TIMER_INT(part, func, show_res) \
    do { \
        auto t1 = Clock::now(); \
        int result = func; \
        auto t2 = Clock::now(); \
        std::chrono::duration<double> diff = (t2 - t1); \
        double elapsed = diff.count(); \
		double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
            std::cout << fmt::format("Part {} answer: {}\r\033[35C( {:6.3f} {} )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
            std::cout << fmt::format("Time elapsed:\r\033[35C( {:6.3f} {} )\n", \
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
    } while (0)

#define TIMER_ULONG(part, func, show_res) \
    do { \
        auto t1 = Clock::now(); \
        unsigned long int result = func; \
        auto t2 = Clock::now(); \
        double elapsed = t2 - t1; \
		double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %llu\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
    } while (0)

#define TIMER_LONG(part, func, show_res) \
    do { \
        auto t1 = Clock::now(); \
        int result = func; \
        auto t2 = Clock::now(); \
        double elapsed = t2 - t1; \
		double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %lld\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
    } while (0)

#define TIMER_STR(part, func, show_res) \
    do { \
        auto t1 = Clock::now(); \
        int result = func; \
        auto t2 = Clock::now(); \
        double elapsed = std::chrono::duration<double>(t2 - t1).count; \
		double elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %s\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
    } while (0)

#endif
