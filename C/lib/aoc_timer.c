#include "aoc_timer.h"
#include "aoc_alloc.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Duration {
    double duration;
    char   unit[5];
} Duration;

Duration convert_duration(double elapsed) {

    Duration duration;

    if (elapsed > 1) {
        duration.duration = elapsed;
        sprintf(duration.unit, "s");
    } else if (elapsed > 1e-3) {
        duration.duration = elapsed * 1e3;
        sprintf(duration.unit, "ms");
    } else if (elapsed > 1e-6) {
        duration.duration = elapsed * 1e6;
        sprintf(duration.unit, "\u03BCs");
    } else {
        duration.duration = elapsed * 1e9;
        sprintf(duration.unit, "ns");
    }

    return duration;
}

void timer_func(int part, void *(func)(AocData_t *), AocData_t *aocdata, gboolean show_res) {
    gdouble elapsed, elapsed_unit;
    GTimer *timer = g_timer_new();
    char   *result = (char *)func(aocdata);
    g_timer_stop(timer);

    Duration duration = convert_duration(g_timer_elapsed(timer, NULL));

    if (show_res) {
        printf("Part %d answer: %-20s%20.2lf %-2s\n", part, result, duration.duration, duration.unit);

    } else {
        printf("Time elapsed : %40.2lf %-2s\n", duration.duration, duration.unit);
    }

    g_timer_destroy(timer);
    if (result)
        aoc_free(result);
}
