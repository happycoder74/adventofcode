#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int    seats[1000] = {0};
static size_t seat_index = 0;

static int int_compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isgraph((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}

int solve_part_1(void *inp) {
    qsort(seats, seat_index, sizeof(int), int_compare);
    return seats[seat_index - 1];
}

int solve_part_2(void *inp) {
    for (unsigned int i = 0; i < seat_index - 1; i++) {
        if ((seats[i + 1] - seats[i]) > 1)
            return seats[i] + 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 5;

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

    while (fgets(line, 254, fp) != NULL) {
        unsigned short int seat_id = 0;
        char              *code = str_trim_trailing(line);
        for (unsigned short int i = 0; i < 10; i++) {
            switch (code[i]) {
                case 'B':
                case 'R':
                    seat_id += 1 << (9 - i);
                    break;
                default:
                    break;
            }
        }
        seats[seat_index++] = seat_id;
    }
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, NULL, 1);
    timer_func_new(2, solve_part_2, NULL, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
