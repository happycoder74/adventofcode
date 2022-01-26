#ifndef __AOC_UTILS_H_
#define __AOC_UTILS_H_

#include <glib.h>

#define TIMER_INT(part, func) \
    do { \
        GTimer *timer = g_timer_new(); \
        int result = func; \
        g_timer_stop(timer); \
        gdouble elapsed = g_timer_elapsed(timer, NULL); \
        printf("Part %d answer: %d\t\t( %.3lf %s)\n", part, result, elapsed > 0.1 ? elapsed : elapsed*1000, elapsed > 0.1? "s":"ms"); \
        g_timer_destroy(timer); \
    } while (0)

#define TIMER_STR(part, func) \
    do { \
        GTimer *timer = g_timer_new(); \
        gchar *result = func; \
        g_timer_stop(timer); \
        gdouble elapsed = g_timer_elapsed(timer, NULL); \
        printf("Part %d answer: %s\t\t( %.3lf %s)\n", part, result, elapsed > 0.1 ? elapsed : elapsed*1000, elapsed > 0.1? "s":"ms"); \
        g_timer_destroy(timer); \
    } while (0)


GArray *get_input(char *, int, int);
gint max(gint *, gint);
gint min(gint *, gint);
gint min_non_zero(gint *, gint);

// String functions similar to methods of  python strings


int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *, char *);
int str_endswith(char *, char *);

#endif
