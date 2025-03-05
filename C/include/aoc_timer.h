#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include "aoc_types.h"
#include <stdint.h>

typedef struct _AocTimer_t AocTimer_t;

enum Border {
    BORDER_TOP = 1,
    BORDER_BOTTOM = 2
};

typedef struct Duration {
    double duration;
    char   unit[5];
} Duration;

void        timer_func(int, void *(func)(AocData_t *), AocData_t *, int);
void        timer_func_bench(int, void *(func)(AocData_t *), AocData_t *, int, unsigned, unsigned);
void        aoc_timer_gen(char *title, AocTimer_t *timer, int border);
void        aoc_timer_start(AocTimer_t *timer);
void        aoc_timer_stop(AocTimer_t *timer);
void        timer_func_new(int, int(func)(void *), void *, int);
void        timer_func_new_long(int, long(func)(void *), void *, int);
void        timer_func_uint64(int, uint64_t(func)(void *), void *, int, uint64_t *);
void        timer_func_new_str(int, void *(func)(void *), void *, int);
void        timer_func_str_void(int part, void *(func)(void), int show_res);
void        timer_func_int_void(int part, int(func)(void), int show_res);
AocTimer_t *aoc_timer_new();
void        aoc_timer_delete(AocTimer_t *timer);

#endif
