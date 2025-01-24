#include "aoc_header.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction {
    char     operation;
    uint32_t value;
};

struct Position {
    int32_t x;
    int32_t y;
};

struct Direction {
    int32_t dx;
    int32_t dy;
};

struct Input {
    struct Instruction instructions[1000];
    size_t             count;
};

static void rotate(uint32_t angle, struct Direction *direction) {
    int32_t dx, dy;
    switch (angle) {
        case 90:
        case -270:
            dx = -direction->dy;
            dy = direction->dx;
            break;
        case 180:
        case -180:
            dx = -direction->dx;
            dy = -direction->dy;
            break;
        case -90:
        case 270:
            dx = direction->dy;
            dy = -direction->dx;
            break;
        default:
            fprintf(stderr, "Should not happen!\n");
            exit(EXIT_FAILURE);
    }
    direction->dx = dx;
    direction->dy = dy;
}

int solve_part_1(void *inp) {
    struct Input    *input = (struct Input *)inp;
    struct Direction direction = {.dx = 1, .dy = 0};
    struct Position  position = {.x = 0, .y = 0};

    for (size_t index = 0; index < input->count; index++) {
        struct Instruction *instruction = &input->instructions[index];
        switch (instruction->operation) {
            case 'F':
                position.x += instruction->value * direction.dx;
                position.y += instruction->value * direction.dy;
                break;
            case 'N':
                position.y += instruction->value;
                break;
            case 'S':
                position.y -= instruction->value;
                break;
            case 'E':
                position.x += instruction->value;
                break;
            case 'W':
                position.x -= instruction->value;
                break;
            case 'L':
                rotate(instruction->value, &direction);
                break;
            case 'R':
                rotate(-instruction->value, &direction);
                break;
                break;
            default:
                fprintf(stderr, "Should not end up here\n");
                exit(EXIT_FAILURE);
                break;
        }
    }

    return abs(position.x) + abs(position.y);
}

int solve_part_2(void *inp) {
    struct Input    *input = (struct Input *)inp;
    struct Direction waypoint = {.dx = 10, .dy = 1};
    struct Position  position = {.x = 0, .y = 0};

    for (size_t index = 0; index < input->count; index++) {
        struct Instruction *instruction = &input->instructions[index];
        switch (instruction->operation) {
            case 'F':
                position.x += instruction->value * waypoint.dx;
                position.y += instruction->value * waypoint.dy;
                break;
            case 'N':
                waypoint.dy += instruction->value;
                break;
            case 'S':
                waypoint.dy -= instruction->value;
                break;
            case 'E':
                waypoint.dx += instruction->value;
                break;
            case 'W':
                waypoint.dx -= instruction->value;
                break;
            case 'L':
                rotate(instruction->value, &waypoint);
                break;
            case 'R':
                rotate(-instruction->value, &waypoint);
                break;
            default:
                fprintf(stderr, "Should not end up here\n");
                exit(EXIT_FAILURE);
                break;
        }
    }

    return abs(position.x) + abs(position.y);
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 12;

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

    input.count = 0;
    while (fgets(line, 254, fp) != NULL) {
        struct Instruction *instruction = &input.instructions[input.count++];
        instruction->operation = line[0];
        instruction->value = atoi(line + 1);
    }

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
