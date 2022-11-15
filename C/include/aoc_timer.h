#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include <glib.h>

void timer_func_str(int, gchar *(*solver)(GArray *), GArray *, int);

#define TIMER(part, func, TYPE, show_res) TIMER_##TYPE(part, func, show_res)

#define TIMER_INT(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        int result = func; \
        g_timer_stop(timer); \
        gdouble elapsed, elapsed_unit; \
        elapsed = g_timer_elapsed(timer, NULL); \
		elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %d\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)

#define TIMER_ULONG(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        unsigned long long result = func; \
        g_timer_stop(timer); \
        gdouble elapsed, elapsed_unit; \
        elapsed = g_timer_elapsed(timer, NULL); \
		elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %llu\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)

#define TIMER_LONG(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        long long result = func; \
        g_timer_stop(timer); \
        gdouble elapsed, elapsed_unit; \
        elapsed = g_timer_elapsed(timer, NULL); \
		elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %lld\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)

#define TIMER_STR(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        gchar *result = func; \
        g_timer_stop(timer); \
        gdouble elapsed, elapsed_unit; \
        elapsed = g_timer_elapsed(timer, NULL); \
		elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %s\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)

#endif
