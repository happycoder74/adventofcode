#include "aoc_header.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char line[100];
};

struct Group {
    struct Person persons[100];
    size_t        count;
};

struct Input {
    struct Group groups[2000];
    size_t       count;
};

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isgraph((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}

static int count_bits(unsigned int value) {
    unsigned int count = 0;

    while (value) {
        count += value & 1;
        value >>= 1;
    }

    return count;
}

int solve_part_1(void *inp) {
    struct Input      *input = (struct Input *)inp;
    struct Group      *group = NULL;
    unsigned short int values[30] = {0};

    int count = 0;

    for (unsigned int index = 0; index < input->count; index++) {
        group = input->groups + index;
        for (unsigned int group_index = 0; group_index < group->count; group_index++) {
            struct Person *person = group->persons + group_index;
            for (char *c = person->line; *c != '\0'; c++) {
                values[*c - 'a'] = 1;
            }
        }
        for (unsigned int i = 0; i < 30; i++) {
            count += values[i];
        }
        memset(values, 0, 30 * sizeof(values[0]));
    }

    return count;
}

int solve_part_2(void *inp) {
    struct Input  *input = (struct Input *)inp;
    struct Group  *group = NULL;
    struct Person *person = NULL;

    int count = 0;

    for (unsigned int index = 0; index < input->count; index++) {
        unsigned int value = 0;

        group = input->groups + index;
        for (unsigned int group_index = 0; group_index < group->count; group_index++) {
            unsigned int tmp_value = 0;
            person = group->persons + group_index;
            if (group_index == 0) {
                for (char *c = person->line; *c != '\0'; c++) {
                    value += 1 << (*c - 'a');
                }
            } else {
                for (char *c = person->line; *c != '\0'; c++) {
                    tmp_value += 1 << (*c - 'a');
                }
                value &= tmp_value;
            }
        }
        count += count_bits(value);
    }

    return count;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 6;

    struct Input *input = (struct Input *)calloc(1, sizeof(struct Input));

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

    size_t         index = 0;
    size_t         group_index = 0;
    struct Group  *group = NULL;
    struct Person *person = NULL;
    while (fgets(line, 254, fp) != NULL) {
        char *str = str_trim_trailing(line);

        group = &input->groups[index];

        if (!line[0]) {
            index++;
            group->count = group_index;
            group_index = 0;
            continue;
        } else {
            person = group->persons + group_index;
            char *line = (person->line);
            memmove(line, str, sizeof(char) * strlen(str));
            group_index++;
        }
    }
    group = &input->groups[index];
    group->count = group_index;
    input->count = index + 1;
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, input, 1);
    timer_func_new(2, solve_part_2, input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    free(input);
    aoc_timer_delete(timer);
    return 0;
}
