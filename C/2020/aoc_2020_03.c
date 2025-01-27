#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    char   treemap[500][40];
    size_t rows;
    size_t columns;
};

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    int           count = 0;
    unsigned int  slope_x = 3;
    unsigned int  slope_y = 1;

    unsigned int pos_x = 0;
    unsigned int pos_y = 0;

    while (pos_y <= input->rows) {
        if (input->treemap[pos_y][pos_x] == '#')
            count++;
        pos_x = (pos_x + slope_x) % input->columns;
        pos_y += slope_y;
    }

    return count;
}

uint64_t solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint64_t      count = 1;
    unsigned int  slope_x[5] = {1, 3, 5, 7, 1};
    unsigned int  slope_y[5] = {1, 1, 1, 1, 2};

    for (unsigned int slope = 0; slope < 5; slope++) {
        unsigned int pos_x = 0;
        unsigned int pos_y = 0;
        unsigned     slope_count = 0;
        while (pos_y <= input->rows) {
            if (input->treemap[pos_y][pos_x] == '#')
                slope_count++;
            pos_x = (pos_x + slope_x[slope]) % input->columns;
            pos_y += slope_y[slope];
        }

        count *= slope_count;
    }
    return count;
}

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isgraph((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}

int main(int argc, char **argv) {
    FILE              *fp = NULL;
    char               line[255];
    char               filepath[255];
    unsigned short int test = 0;

    const unsigned int year = 2020;
    const unsigned int day = 3;

    struct Input input = {0};
    AocTimer_t  *timer = NULL;

    if ((argc > 1) && !strcmp(argv[1], "--test")) {
        test = 1;
    }

    snprintf(filepath, 254, "%s/%d/%02d/%sinput.txt", getenv("AOC_DATA_LOCATION"), year, day,
             test ? "test_" : "");

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    size_t columns = 0;
    while (fgets(line, 254, fp) != NULL) {
        char *str = str_trim_trailing(line);
        if (index == 0) {
            columns = strlen(str);
        }
        memmove(&input.treemap[index], str, columns * sizeof(char));
        index++;
    }
    input.columns = columns;
    input.rows = index;
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_uint64(2, solve_part_2, &input, 1, NULL);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
