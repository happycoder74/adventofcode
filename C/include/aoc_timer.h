#ifndef __AOC_TIMER_H__
#define __AOC_TIMER_H__

#include "aoc_types.h"

void timer_func(int, void *(func)(AocData_t *), AocData_t *, int);
void timer_func_bench(int, void *(func)(AocData_t *), AocData_t *, int, unsigned, unsigned);

#endif
