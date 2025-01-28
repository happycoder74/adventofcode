#include "aoc_header.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction {
    char line[10];
};

struct Input {
    struct Instruction instructions[1000];
    unsigned short int visited[1000];
    size_t             count;
};

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isgraph((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}

int solve_part_1(void *inp) {
    struct Input       *input = (struct Input *)inp;
    struct Instruction *instruction = NULL;
    int                 accumulator = 0;
    unsigned int        ip = 0;
    while (input->visited[ip] == 0) {
        instruction = input->instructions + ip;
        input->visited[ip] = 1;
        if (!strncmp(instruction->line, "nop", 3)) {
            ip += 1;
        } else if (!strncmp(instruction->line, "acc", 3)) {
            accumulator += atoi(instruction->line + 4);
            ip += 1;
        } else if (!strncmp(instruction->line, "jmp", 3)) {
            ip += atoi(instruction->line + 4);
        }
    }

    return accumulator;
}

int solve_part_2(void *inp) {
    struct Input       *input = (struct Input *)inp;
    struct Instruction *instruction = NULL;

    for (unsigned int ip_change = 0; ip_change < input->count; ip_change++) {
        instruction = input->instructions + ip_change;
        if (!strncmp(instruction->line, "acc", 3))
            continue;
        if (!strncmp(instruction->line, "jmp", 3)) {
            memcpy(instruction->line, "nop", 3 * sizeof(char));
        } else if (!strncmp(instruction->line, "nop", 3)) {
            memcpy(instruction->line, "jmp", 3 * sizeof(char));
        }
        int          accumulator = 0;
        unsigned int ip = 0;
        while (input->visited[ip] == 0) {
            instruction = input->instructions + ip;
            input->visited[ip] = 1;
            if (!strncmp(instruction->line, "nop", 3)) {
                ip += 1;
            } else if (!strncmp(instruction->line, "acc", 3)) {
                accumulator += atoi(instruction->line + 4);
                ip += 1;
            } else if (!strncmp(instruction->line, "jmp", 3)) {
                ip += atoi(instruction->line + 4);
            }

            if (ip >= input->count) {
                return accumulator;
            }
        }
        memset(input->visited, 0, 1000 * sizeof(unsigned short int));
        instruction = input->instructions + ip_change;
        if (!strncmp(instruction->line, "jmp", 3)) {
            memcpy(instruction->line, "nop", 3 * sizeof(char));
        } else if (!strncmp(instruction->line, "nop", 3)) {
            memcpy(instruction->line, "jmp", 3 * sizeof(char));
        }
    }

    printf("Failed to find a solution\n");
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 8;

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

    size_t index = 0;
    while (fgets(line, 254, fp) != NULL) {
        char *str = str_trim_trailing(line);
        memmove(input.instructions[index].line, str, sizeof(char) * strlen(str));
        index++;
    }
    input.count = index;
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
