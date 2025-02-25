#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <string.h>

struct Input {
    int    data[10000];
    size_t dimension;
};

void parse_data(char *line, int data[]) {
    size_t i = 0;
    for (i = 0; line[i]; i++) {
        data[i] = line[i] == '(' ? 1 : -1;
    }
}

int solve_part_1(void *data) {
    size_t i;
    int    level = 0;
    size_t limit = ((struct Input *)data)->dimension;
    for (i = 0; i < limit; i++) {
        level += ((struct Input *)data)->data[i];
    }

    return level;
}

int solve_part_2(void *data) {
    size_t        i = 0;
    int           level = 0;
    struct Input *inp = (struct Input *)data;
    for (i = 0; i < inp->dimension; i++) {
        level += inp->data[i];
        if (level < 0) {
            return i + 1;
        }
    }
    return 0;
}

int solve_all(void *data) {
    timer_func_new(1, solve_part_1, data, 1);
    timer_func_new(2, solve_part_2, data, 2);
    return 0;
}

int main(int argc, char **argv) {

    const int    year = 2015;
    const int    day = 1;
    struct Input input;

    AocTimer_t *timer = aoc_timer_new();

    aoc_timer_start(timer);
    AocData_t *data = get_data(argc, argv, year, day, NULL);
    char      *line = aoc_str_array_index(data->data, 0);

    parse_data(line, input.data);
    input.dimension = strlen(line);
    aoc_timer_stop(timer);
    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_TOP | BORDER_BOTTOM);
    timer_func_new(0, solve_all, &input, 0);

    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);
    aoc_data_free(data);
    aoc_timer_delete(timer);

    return aoc_mem_gc();
}
