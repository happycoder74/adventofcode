#include "aoc_header.h"
#include "aoc_timer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Instruction {
    enum Direction {
        LEFT,
        RIGHT
    } direction;
    uint32_t steps;
};

struct Input {
    struct Instruction instructions[5000];
    size_t             len;
};

int solve_part_1(void *input) {
    struct Input *inp    = (struct Input *)input;
    int32_t       value  = 50;
    size_t        result = 0;

    for (size_t i = 0; i < inp->len; ++i) {
        struct Instruction *instruction = &inp->instructions[i];
        switch (instruction->direction) {
            case LEFT:
                value -= instruction->steps;
                break;
            case RIGHT:
                value += instruction->steps;
                break;
            default:
                fprintf(stderr, "Invalid instruction");
                exit(EXIT_FAILURE);
        }
        if ((value % 100) == 0) {
            result++;
        }
    }

    return result;
}

int solve_part_2(void *input) {
    struct Input *inp    = (struct Input *)input;
    int           result = 0;
    int           value  = 50;
    int           delta  = 0;

    for (size_t i = 0; i < inp->len; ++i) {
        struct Instruction *instruction = &inp->instructions[i];
        switch (instruction->direction) {
            case LEFT:
                delta = -instruction->steps;
                break;
            case RIGHT:
                delta = instruction->steps;
                break;
            default:
                fprintf(stderr, "Invalid instruction");
                exit(EXIT_FAILURE);
        }

        result += abs(delta) / 100 +
                  (int)(value == 0 || value + delta % 100 < 0 || value + delta % 100 > 100);
        value = (((value + delta) % 100) + 100) % 100;
    }

    return result;
}

int main() {

    FILE        *fp           = NULL;
    char         filename[40] = "input.txt";
    char         filepath[255];
    char         line[1000];
    const int    year  = 2025;
    const int    day   = 1;
    struct Input input = {0};
    AocTimer_t  *timer = aoc_timer_new();

    aoc_timer_start(timer);

    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file (%s)\n", filepath);
        exit(EXIT_FAILURE);
    }

    printf("input length: %zu\n", input.len);
    while (fgets(line, 1000, fp) != NULL) {
        struct Instruction *instruction = &input.instructions[input.len];
        char                direction   = line[0];
        switch (direction) {
            case 'L':
                instruction->direction = LEFT;
                break;
            case 'R':
                instruction->direction = RIGHT;
                break;
            default:
                break;
        }
        char *n = &line[1];
        sscanf(n, "%u", &instruction->steps);
        input.len++;
    }

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, (void *)&input, 1);
    timer_func_new(2, solve_part_2, (void *)&input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return EXIT_SUCCESS;
}
