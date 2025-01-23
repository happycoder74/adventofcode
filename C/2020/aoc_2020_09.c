#include "aoc_header.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    uint64_t values[1000];
    size_t   count;
    uint8_t  test;
    uint64_t to_part_2;
};

uint64_t solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;

    const size_t offset = input->test ? 5 : 25;
    for (uint64_t index = 0; index < input->count - offset; index++) {
        uint64_t value = input->values[index + offset];
        uint8_t  found = 0;
        for (size_t i = index; (i < (index + offset - 1)) && (!found); i++) {
            for (size_t j = i + 1; (j < (index + offset)) && (!found); j++) {
                if ((input->values[i] + input->values[j]) == value) {
                    found = 1;
                }
            }
        }
        if (!found) {
            input->to_part_2 = value;
            return value;
        }
    }

    fprintf(stderr, "Should not end up here\n");
    return 0;
}

uint64_t solve_part_2(void *inp) {

    struct Input *input = (struct Input *)inp;

    const size_t offset = input->test ? 5 : 25;
    for (uint64_t index = 0; index < input->count - offset; index++) {
        for (size_t i = index; i < (index + offset - 1); i++) {
            for (size_t j = i + 1; j < (index + offset); j++) {
                uint64_t sum = 0;
                uint64_t smallest = UINT64_MAX;
                uint64_t largest = 0;
                for (uint64_t k = i; k <= j; k++) {
                    sum += input->values[k];
                    largest = input->values[k] > largest ? input->values[k] : largest;
                    smallest = input->values[k] < smallest ? input->values[k] : smallest;
                }
                if (sum == input->to_part_2) {
                    /* printf("Found %d (index %d) and %d (index %d) = %d\n", (int)input->values[i],
                     */
                    /*        (int)i, (int)input->values[j], (int)j, (int)sum); */
                    return smallest + largest;
                }
            }
        }
    }

    fprintf(stderr, "Should not end up here\n");
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 9;

    struct Input input = {0};

    AocTimer_t *timer = NULL;

    if ((argc > 1)) {
        if (!strcmp(argv[1], "--test")) {
            sprintf(filename, "test_input.txt");
            input.test = 1;
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
    while (fgets(line, 254, fp) != NULL) {
        input.values[index++] = strtoull(line, NULL, 0);
    }
    input.count = index;
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_uint64(1, solve_part_1, &input, 1, NULL);
    timer_func_uint64(2, solve_part_2, &input, 1, NULL);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
