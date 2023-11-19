#include "aoc_timer.h"
#include "aoc_alloc.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void timer_func(int part, void *(func)(AocData_t *), AocData_t *aocdata, gboolean show_res) {
    gdouble elapsed, elapsed_unit;
    GTimer *timer = g_timer_new();
    char   *result = (char *)func(aocdata);
    g_timer_stop(timer);

    elapsed = g_timer_elapsed(timer, NULL);
    elapsed_unit = elapsed > 0.1 ? elapsed : elapsed * 1000.;
    if (show_res) {
        printf("Part %d answer: %s\r\033[35C( %6.3lf %-2s )\n", part, result, elapsed_unit, elapsed > 0.1 ? "s" : "ms");

    } else {
        printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n", elapsed_unit, elapsed > 0.1 ? "s" : "ms");
    }

    g_timer_destroy(timer);
    if (result)
        aoc_free(result);
}
