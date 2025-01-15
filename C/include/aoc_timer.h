#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include "aoc_types.h"

typedef struct Duration {
    double duration;
    char   unit[5];
} Duration;

void timer_func(int, void *(func)(AocData_t *), AocData_t *, int);
void timer_func_bench(int, void *(func)(AocData_t *), AocData_t *, int, unsigned, unsigned);
#ifndef _WIN32
void timer_func_new(int, int(func)(void *), void *, int);
void timer_func_new_str(int, void *(func)(void *), void *, int);
#endif

#endif
