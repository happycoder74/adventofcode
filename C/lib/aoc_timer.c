#define _XOPEN_SOURCE 600 // enable the clock_gettime functionality
#include "aoc_timer.h"
#include "aoc_alloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        sprintf(duration.unit, "\u03BCs");
    } else {
        duration.duration = elapsed;
        sprintf(duration.unit, "ns");
    }

    return duration;
}

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
