#include "aoc_header.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct Input {
    uint32_t numbers[10];
    size_t   count;
};

int solver(struct Input *input, uint64_t rounds) {
    uint32_t *numbers = (uint32_t *)calloc(rounds, sizeof(uint32_t));
    uint32_t  last_turn = 0;

    uint32_t turn = 1;
    for (turn = 1; turn <= input->count; turn++) {
        numbers[input->numbers[turn - 1]] = turn;
    }
    int next_number = input->numbers[input->count - 1];
    for (turn = turn - 1; turn < rounds; turn++) {
        if ((last_turn = numbers[next_number]) == 0) {
            last_turn = 0;
        }
        numbers[next_number] = turn;
        if (last_turn) {
            next_number = turn - last_turn;
        } else {
            next_number = 0;
        }
    }

    free(numbers);
    return next_number;
}

int solve_part_1(void *inp) {
    return solver((struct Input *)inp, 2020);
}

int solve_part_2(void *inp) {
    return solver((struct Input *)inp, 30000000);
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 15;

    struct Input input = {0};

    AocTimer_t *timer = NULL;

    if ((argc > 1)) {
        if (!strcmp(argv[1], "--test")) {
            snprintf(filename, 40, "test_input.txt");
        } else {
            snprintf(filename, 40, "%s", argv[1]);
        }
    } else {
        snprintf(filename, 40, "input.txt");
    }

    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    if (!fgets(line, 254, fp))
        fprintf(stderr, "Error when reading file\n");

    char *token = strtok(line, ",");
    while (token) {
        input.numbers[input.count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    fclose(fp);

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
