#define _XOPEN_SOURCE 600
#include "aoc_timer.h"
#include "aoc_alloc.h"
#include "aoc_types.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#ifndef _WIN32
#include <time.h>
#else
// clang-format off
#include <windows.h>
#include <winbase.h>
// clang-format on
#endif

struct _AocTimer_t {
#ifndef _WIN32
    struct timespec start;
    struct timespec stop;
#else
    LARGE_INTEGER freq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
#endif
};
#include <unistd.h>

AocTimer_t *aoc_timer_new(void) {
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

inline void print_result_str(const int part, const char *result, const Duration duration) {
    printf("Part %d answer: %-28s%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
}

inline void print_result_int(const int part, const int result, const Duration duration) {
    printf("Part %d answer: %-28d%10.2f %-2s\n", part, result, duration.duration, duration.unit);
}

inline void print_result_long(const int part, const long result, const Duration duration) {
    printf("Part %d answer: %-28ld%10.2lf %-2s\n", part, result, duration.duration, duration.unit);
}
inline void print_result_uint64(const int part, const uint64_t result, const Duration duration) {
    printf("Part %d answer: %-28" PRIu64 "%10.2lf %-2s\n", part, result, duration.duration,
           duration.unit);
}

#ifdef _WIN32
// clang-format off
#include <windows.h>
#include <winbase.h>
#else
#include <time.h>
#endif
// clang-format off
void timer_func(int part, void *(func)(AocData_t *), AocData_t *aocdata, int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif
    char         *result = (char *)func(aocdata);
#ifdef _WIN32
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
    Duration duration = convert_duration(timeDifference);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    Duration duration = convert_duration((stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec));
#endif
    if (show_res) {
        print_result_str(part, result, duration);
    }
    if (result) {
        free(result);
    }
}

void timer_func_int(int part, int (func)(AocData_t *), AocData_t *aocdata, int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif
    int result = func(aocdata);
#ifdef _WIN32
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
    Duration duration = convert_duration(timeDifference);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    Duration duration = convert_duration((stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec));
#endif
    if (show_res) {
        print_result_int(part, result, duration);
    }
}

void timer_func_new_str(int part, void *(func)(void *), void *aocdata, int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif
    char         *result = (char *)func(aocdata);
#ifdef _WIN32
    QueryPerformanceCounter(&endTime);
    double   timeDifference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
    Duration duration = convert_duration(timeDifference);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    Duration duration = convert_duration((stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec));
#endif
    if (show_res) {
        print_result_str(part, result, duration);
    }
    if (result) {
        free(result);
    }
}


void timer_func_new_long(int part, long(func)(void *), void *input, int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
#else
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
#endif
    long result = func(input);
#ifdef _WIN32
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
    Duration duration = convert_duration(time_difference);

    if (show_res) {
        print_result_long(part, result, duration);
    }
}


void aoc_timer_gen(char *title, AocTimer_t *timer, int border) {

#ifdef _WIN32
    double   timeDifference = ((timer->endTime.QuadPart - timer->startTime.QuadPart) * 1e9 / timer->freq.QuadPart);
#else
    double timeDifference = (timer->stop.tv_sec * 1e9 + timer->stop.tv_nsec) - (timer->start.tv_sec * 1e9 + timer->start.tv_nsec);
#endif
    Duration duration = convert_duration(timeDifference);
    if (border & BORDER_TOP) {
        fprintf(stdout, "--------------------------------------------------------\n");
    }
    fprintf(stdout, "%-30s%11.3lf %s (%lu ns)\n", title,
            duration.duration, duration.unit,
            (unsigned long)(timeDifference));
    if (border & BORDER_BOTTOM) {
        fprintf(stdout, "--------------------------------------------------------\n");
    }
}

void timer_func_uint64(int part, uint64_t(func)(void *), void *input, int show_res, uint64_t *result_output) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif
    uint64_t result = func(input);
#ifdef _WIN32
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
    Duration duration = convert_duration(time_difference);
    if (show_res) {
        print_result_uint64(part, result, duration);
        if (result_output) {
            *result_output = (uint64_t)result;
        }
    }
}

void timer_func_str_void(int part, void *(func)(void), int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif

    char *result = (char *)func();

#ifdef _WIN32
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif

    Duration duration = convert_duration(time_difference);
    if (show_res) {
        print_result_str(part, result, duration);
    }
}

void timer_func_int_void(int part, int(func)(void), int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif

    int result = func();

#ifdef _WIN32
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
    Duration duration = convert_duration(time_difference);

    if (show_res) {
        print_result_int(part, result, duration);
    }
}

void timer_func_new(int part, int(func)(void *), void *input, int show_res) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif

    int result = func(input);

#ifdef _WIN32
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
    Duration duration = convert_duration(time_difference);

    if (show_res) {
        print_result_int(part, result, duration);
    }
}

void timer_void(void (func)(void *), void *data, const char *message) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif

    func(data);

#ifdef _WIN32
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
    Duration duration = convert_duration(time_difference);

    printf("%-30s%23.2lf %-2s\n", message, duration.duration, duration.unit);
}

void *timer_return(void *(func)(void *), void *data, const char *message) {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER endTime;
#else
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
#endif

    void *result = func(data);

#ifdef _WIN32
    QueryPerformanceCounter(&endTime);
    double   time_difference = ((endTime.QuadPart - startTime.QuadPart) * 1e9 / freq.QuadPart);
#else
    clock_gettime(CLOCK_REALTIME, &stop);
    double time_difference = (stop.tv_sec * 1e9 + stop.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
#endif
    Duration duration = convert_duration(time_difference);

    printf("%-30s%23.2lf %-2s\n", message, duration.duration, duration.unit);
    return result;
}
