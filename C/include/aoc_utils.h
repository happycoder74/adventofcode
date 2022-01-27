#ifndef __AOC_UTILS_H_
#define __AOC_UTILS_H_

#include <glib.h>

#define TIMER(part, func, TYPE, show_res) TIMER_##TYPE(part, func, show_res)

#define TIMER_INT(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        int result = func; \
        g_timer_stop(timer); \
        gdouble elapsed = g_timer_elapsed(timer, NULL); \
		elapsed = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %d\t\t( %.3lf %s)\n", part, result, elapsed, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\t\t\t( %.3lf %s)\n", elapsed, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)

#define TIMER_STR(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        gchar *result = func; \
        g_timer_stop(timer); \
        gdouble elapsed = g_timer_elapsed(timer, NULL); \
		elapsed = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %s\t\t( %.3lf %s)\n", part, result, elapsed, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\t\t\t( %.3lf %s)\n", elapsed, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)


GArray *get_input(char *, int, int);
gint max(gint *, gint);
gint min(gint *, gint);
gint min_non_zero(gint *, gint);

// String functions similar to methods of  python strings


char *str_trim(char *str);
char *str_join(const char *, char **, size_t);
int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *, char *);
int str_endswith(char *, char *);

#endif
