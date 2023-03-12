#include <glib.h>
#include <stdlib.h>
#include <aoc_timer.h>

void timer_func(int part, gpointer (func)(AocData_t *), AocData_t *aocdata, gboolean show_res) {
    gdouble elapsed, elapsed_unit;
    GTimer *timer = g_timer_new();
    gchar *result = (gchar *)func(aocdata);
    g_timer_stop(timer);

    elapsed = g_timer_elapsed(timer, NULL);
    elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000.;
    if (show_res) {
        g_print("Part %d answer: %s\r\033[35C( %6.3lf %-2s )\n",
                part, result, elapsed_unit, elapsed > 0.1 ? "s":"ms");

    } else {
        g_print("Time elapsed:\r\033[35C( %6.3lf %-2s)\n",
                elapsed_unit, elapsed > 0.1 ? "s":"ms");
    }

    g_timer_destroy(timer);
    if (result)
        g_free(result);
}


