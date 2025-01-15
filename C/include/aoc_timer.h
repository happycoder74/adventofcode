#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#define _XOPEN_SOURCE 600
#include "aoc_types.h"
#include <time.h>

enum Border {
    BORDER_TOP = 1,
    BORDER_BOTTOM = 2
};

typedef struct Duration {
    double duration;
    char   unit[5];
} Duration;

void timer_func(int, void *(func)(AocData_t *), AocData_t *, int);
void timer_func_bench(int, void *(func)(AocData_t *), AocData_t *, int, unsigned, unsigned);
#ifndef _WIN32
void timer_func_new(int, int(func)(void *), void *, int);
void timer_func_new_str(int, void *(func)(void *), void *, int);
void aoc_timer_gen(char *title, struct timespec *start, struct timespec *end, enum Border border);
#endif

#endif
