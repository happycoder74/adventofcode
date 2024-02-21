#include "aoc_timer.h"
#include "aoc_alloc.h"
#include <stdio.h>
#include <unistd.h>

typedef struct Duration {
    double duration;
    char   unit[5];
} Duration;

Duration convert_duration(double elapsed) {

    Duration duration;

    if (elapsed > 1e9) {
        duration.duration = elapsed / 1e9;
        sprintf(duration.unit, "s");
    } else if (elapsed > 1e6) {
        duration.duration = elapsed / 1e6;
        sprintf(duration.unit, "ms");
    } else if (elapsed > 1e3) {
        duration.duration = elapsed / 1e3;
        // Need a UTF-8 enabled terminal to display correctly
        sprintf(duration.unit, "\u03BCs");
    } else {
        duration.duration = elapsed;
        sprintf(duration.unit, "ns");
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

#else
#define _XOPEN_SOURCE 600
void timer_func(int part, void *(func)(AocData_t *), AocData_t *aocdata, int show_res) {
    double          elapsed, elapsed_unit;
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
