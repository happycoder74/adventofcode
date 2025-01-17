#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include "aoc_types.h"

#ifndef _WIN32
typedef struct _AocTimer_t AocTimer_t;
#else
// clang-format off
#include <windows.h>
#include <winbase.h>
// clang-format on
typedef struct AocTimer_t {
    LARGE_INTEGER freq;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
} AocTimer_t;
#endif

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
void        aoc_timer_gen(char *title, AocTimer_t *timer, enum Border border);
void        aoc_timer_start(AocTimer_t *timer);
void        aoc_timer_stop(AocTimer_t *timer);
void        timer_func_new(int, int(func)(void *), void *, int);
void        timer_func_new_str(int, void *(func)(void *), void *, int);
AocTimer_t *aoc_timer_new();
void        aoc_timer_delete(AocTimer_t *timer);

#endif
