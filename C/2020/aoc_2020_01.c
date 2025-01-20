#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    int                data[200];
    unsigned short int set[2021];
    size_t             count;
};

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    for (size_t i = 0; i < input->count; i++) {
        if (input->set[2020 - input->data[i]]) {
            return input->data[i] * (2020 - input->data[i]);
        }
    }
    return 0;
}

int solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;

    for (size_t i = 0; i < input->count - 2; i++) {
        size_t remaining = 2020 - input->data[i];
        for (size_t j = i + 1; j < input->count - 1; j++) {
            if (input->data[j] > (int)remaining)
                continue;
            const size_t num_k = remaining - input->data[j];
            if (input->set[num_k])
                return input->data[i] * input->data[j] * num_k;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  filepath[255];
    char  line[255];

    snprintf(filepath, 254, "%s/2020/01/%sinput.txt", getenv("AOC_DATA_LOCATION"),
             (argc > 1) ? (!strcmp(argv[1], "--test") ? "test_" : "") : "");

    fp = fopen(filepath, "r");
    struct Input input = {0};

    size_t index = 0;
    while ((fgets(line, 254, fp)) != NULL) {
        input.data[index] = atoi(line);
        input.set[input.data[index]] = 1;
        index++;
    }
    input.count = index;

    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);

    return 0;
}
