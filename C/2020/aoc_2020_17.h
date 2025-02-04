#ifndef AOC_2020_17_H_1PBRDOHW
#define AOC_2020_17_H_1PBRDOHW

#include "aoc_hash_light.h"

struct Input {
    AocHashTable *grid;

    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int z_min;
    int z_max;
    int w_min;
    int w_max;
};

int   get_key(int x, int y, int z, int w, struct Input *input);
char *trim_end(char *str);
int   solve_part_1(void *inp);
int   solve_part_2(void *inp);

#endif /* end of include guard: AOC_2020_17_H_1PBRDOHW */
