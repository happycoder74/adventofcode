#define _XOPEN_SOURCE 600
#include "aoc_timer.h"
#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_types.h"
#include <stdio.h>
#ifndef _WIN32
#include <time.h>
#endif
#include <unistd.h>

typedef struct Duration {
    double duration;
    char   unit[5];
} Duration;

Duration convert_duration(double elapsed) {

    Duration duration;

    if (elapsed > 1e9) {
        duration.duration = elapsed / 1e9;
        snprintf(duration.unit, 5, "s");
    } else if (elapsed > 1e6) {
        duration.duration = elapsed / 1e6;
        snprintf(duration.unit, 5, "ms");
    } else if (elapsed > 1e3) {
        duration.duration = elapsed / 1e3;
        // Need a UTF-8 enabled terminal to display correctly
        // chcp 65001 in windows command
        snprintf(duration.unit, 5, "\u03BCs");
    } else {
        duration.duration = elapsed;
        snprintf(duration.unit, 5, "ns");
    }

    return duration;
}

#ifdef _WIN32
// clang-format off
#include <windows.h>
#include <winbase.h>
// clang-format off
void timer_func(int part, void *(func)(AocData_t *), AocData_t *aocdata, int show_res) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
    char         *result = (char *)func(aocdata);
    QueryPerformanceCounter(&endTime);
    double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
    Duration duration = convert_duration(timeDifference);
    if (show_res) {
        printf("Part %d answer: %-20s%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
    } else {
        printf("Time elapsed : %30.2lf %-2s\n", duration.duration, duration.unit);
    }

    if (result) {
        aoc_free(result);
    }
}
#endif

void timer_func_bench(int part, void *(func)(AocData_t *), AocData_t *aocdata, int show_res, unsigned warmup, unsigned iterations) {
    char *result = NULL;
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
#else
    struct timespec start, stop;
#endif
    AocArrayPtr warmup_timings = aoc_double_array_new();
    AocArrayPtr benchmark_timings = aoc_double_array_new();

    for (unsigned warmup_counter = 0; warmup_counter < warmup; warmup_counter++) {
#ifdef _WIN32
        QueryPerformanceCounter(&startTime);
#else
        clock_gettime(CLOCK_REALTIME, &start);
#endif
        result = (char *)func(aocdata);
#ifdef _WIN32
        QueryPerformanceCounter(&endTime);
        double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
        clock_gettime(CLOCK_REALTIME, &stop);
        double   timeDifference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
        aoc_double_array_append(warmup_timings, timeDifference);
    }

    for (unsigned bench_counter = 0; bench_counter <= iterations; bench_counter++) {
#ifdef _WIN32
        QueryPerformanceCounter(&startTime);
#else
        clock_gettime(CLOCK_REALTIME, &start);
#endif
        result = (char *)func(aocdata);
#ifdef _WIN32
        QueryPerformanceCounter(&endTime);
        double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
        clock_gettime(CLOCK_REALTIME, &stop);
        double   timeDifference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
        aoc_double_array_append(benchmark_timings, timeDifference);
    }

    double meanTimeDifference = aoc_double_array_mean(benchmark_timings);
    double stddev = aoc_double_array_stddev(benchmark_timings);
    Duration duration = convert_duration(meanTimeDifference);
    Duration stddevduration = convert_duration(stddev);

    if (show_res) {
        printf("Part %d answer: %-20s%10.2lf %-2s (+/- %.2lf %s)\n",
                part, result, duration.duration, duration.unit,
                stddevduration.duration, stddevduration.unit);
    } else {
        printf("Time elapsed : %30.2lf %-2s\n", duration.duration, duration.unit);
    }

    if (result) {
        aoc_free(result);
    }
}

#ifndef _WIN32
#include <time.h>
void timer_func(int part, void *(func)(AocData_t *), AocData_t *aocdata, int show_res) {
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
    char *result = (char *)func(aocdata);
    clock_gettime(CLOCK_REALTIME, &stop);

    Duration duration = convert_duration((stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec));

    if (show_res) {
        printf("Part %d answer: %-20s%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
    } else {
        printf("Time elapsed : %30.2lf %-2s\n", duration.duration, duration.unit);
    }

    if (result)
        aoc_free(result);
}
#endif
