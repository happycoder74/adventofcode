#define _XOPEN_SOURCE 600
#include "aoc_timer.h"
#include "aoc_alloc.h"
#include "aoc_types.h"
#include <stdio.h>
#ifndef _WIN32
#include <time.h>
struct _AocTimer_t {
    struct timespec start;
    struct timespec stop;
};
#endif
#include <unistd.h>

AocTimer_t *aoc_timer_new() {
    AocTimer_t *timer = (AocTimer_t *)malloc(sizeof(AocTimer_t));
    return timer;
}

void aoc_timer_delete(AocTimer_t *timer) {
    if (timer) {
        free(timer);
    }
}

#ifndef _WIN32
void aoc_timer_start(AocTimer_t *timer) {
    if (timer) {
        clock_gettime(CLOCK_REALTIME, &(timer->start));
    }
}
void aoc_timer_stop(AocTimer_t *timer) {
    if (timer) {
        clock_gettime(CLOCK_REALTIME, &(timer->stop));
    }
}
#else
void aoc_timer_start(AocTimer_t *timer) {
    QueryPerformanceFrequency(&(timer->freq));
    QueryPerformanceCounter(&(timer->startTime));
}
void aoc_timer_stop(AocTimer_t *timer) {
    QueryPerformanceCounter(&(timer->endTime));
}
#endif

static Duration convert_duration(double elapsed) {

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
        free(result);
    }
}

void timer_func_new(int part, int (func)(void *), void *aocdata, int show_res) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
    int result = func(aocdata);
    QueryPerformanceCounter(&endTime);
    double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
    Duration duration = convert_duration(timeDifference);
    if (show_res) {
        printf("Part %d answer: %20d%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
    } else {
        printf("Time elapsed : %30.2lf %-2s\n", duration.duration, duration.unit);
    }
}

void timer_func_new_str(int part, void *(func)(void *), void *aocdata, int show_res) {
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
        free(result);
    }
}

void aoc_timer_gen(char *title, AocTimer_t *timer, enum Border border) {

    double   timeDifference = ((timer->endTime.QuadPart - timer->startTime.QuadPart) * 1e9 / timer->freq.QuadPart);
    Duration duration = convert_duration(timeDifference);
    if (border & BORDER_TOP) {
        fprintf(stdout, "--------------------------------------------------------\n");
    }
    fprintf(stdout, "%-20s%25.3lf %s\n", title,
            duration.duration, duration.unit);
    if (border & BORDER_BOTTOM) {
        fprintf(stdout, "--------------------------------------------------------\n");
    }
}
#endif


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
        free(result);
}

void timer_func_new(int part, int(func)(void *), void *input, int show_res) {
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
    int result = func(input);
    clock_gettime(CLOCK_REALTIME, &stop);

    Duration duration = convert_duration((stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec));

    if (show_res) {
        printf("Part %d answer: %-20d%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
    } else {
        printf("Time elapsed : %30.2lf %-2s\n", duration.duration, duration.unit);
    }
}

void timer_func_new_str(int part, void *(func)(void *), void *input, int show_res) {
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
    char *result = (char *)func(input);
    clock_gettime(CLOCK_REALTIME, &stop);

    Duration duration = convert_duration((stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec));

    if (show_res) {
        printf("Part %d answer: %-20s%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
    } else {
        printf("Time elapsed : %30.2lf %-2s\n", duration.duration, duration.unit);
    }

    if (result)
        free(result);
}

void aoc_timer_gen(char *title, AocTimer_t *timer, enum Border border) {

    Duration duration = convert_duration((timer->stop.tv_sec * 1e9 + timer->stop.tv_nsec) - (timer->start.tv_sec * 1e9 + timer->start.tv_nsec));
    if (border & BORDER_TOP) {
        fprintf(stdout, "--------------------------------------------------------\n");
    }
    fprintf(stdout, "%-20s%20.3lf %s (%lu ns)\n", title,
            duration.duration, duration.unit,
            (timer->stop.tv_nsec - timer->start.tv_nsec + (timer->stop.tv_sec - timer->start.tv_sec) * (int)1e9));
    if (border & BORDER_BOTTOM) {
        fprintf(stdout, "--------------------------------------------------------\n");
    }
}
#endif


