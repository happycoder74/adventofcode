#include "aoc_header.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    unsigned int values[100];
    size_t       count;
};

static int uint_compare(const void *a, const void *b) {
    return *(unsigned int *)a - *(unsigned int *)b;
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    unsigned int  count1 = 0, count3 = 0;

    for (size_t i = 1; i < input->count - 1; i++) {
        unsigned int diff = input->values[i + 1] - input->values[i];
        if (diff == 1)
            count1++;
        if (diff == 3)
            count3++;
    }

    return (count1 + 1) * count3;
}

static unsigned int multiplier(unsigned int delta) {
    switch (delta) {
        case 4:
            return 7;
            break;
        case 3:
            return 4;
            break;
        case 2:
            return 2;
            break;
        default:
            return 1;
            break;
    }
}

uint64_t solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint64_t      result = 1;

    unsigned int indices[100] = {0};
    unsigned int ind_index = 1;
    indices[0] = 0;
    for (size_t i = 0; i < input->count - 1; i++) {
        if ((input->values[i + 1] - input->values[i]) == 3) {
            indices[ind_index++] = i + 1;
        }
    }
    for (unsigned i = 0; i < ind_index - 1; i++) {
        result *= multiplier(indices[i + 1] - indices[i] - 1);
    }

    return result;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 10;

    struct Input input = {0};

    AocTimer_t *timer = NULL;

    if ((argc > 1)) {
        if (!strcmp(argv[1], "--test")) {
            sprintf(filename, "test_input.txt");
        } else {
            sprintf(filename, "%s", argv[1]);
        }
    } else {
        sprintf(filename, "input.txt");
    }

    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    input.values[index++] = 0;
    while (fgets(line, 254, fp) != NULL) {
        input.values[index++] = atoi(line);
    }
    qsort(input.values, index, sizeof(unsigned int), uint_compare);
    input.values[index] = input.values[index - 1] + 3;
    input.count = index + 1;

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
