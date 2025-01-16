#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t solver(const long *param, const unsigned long np, const uint64_t delta) {
    uint64_t result = 0;
    uint64_t a_press;
    uint64_t b_press;

    for (unsigned long ip = 0; ip < np; ip++) {
        int64_t a = param[0 + ip * 6];
        int64_t c = param[1 + ip * 6];
        int64_t b = param[2 + ip * 6];
        int64_t d = param[3 + ip * 6];
        int64_t bx = param[4 + ip * 6] + delta;
        int64_t by = param[5 + ip * 6] + delta;

        if ((((d * bx - b * by) % (a * d - b * c)) != 0) ||
            (((-c * bx + a * by) % (a * d - b * c)) != 0)) {
            continue;
        }

        a_press = (d * bx - b * by) / (a * d - b * c);
        b_press = (-c * bx + a * by) / (a * d - b * c);

        result += 3 * a_press + b_press;
    }
    return result;
}

struct Input {
    long          parameters[6 * 400];
    unsigned long nparameters;
};

void *solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    char         *output = (char *)calloc(100, sizeof(char));
    snprintf(output, 99, "%" PRIu64, solver(input->parameters, input->nparameters, 0));
    return output;
}

void *solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    char         *output = (char *)calloc(100, sizeof(char));
    snprintf(output, 99, "%" PRIu64, solver(input->parameters, input->nparameters, 10000000000000));
    return output;
}

int main(int argc, char **argv) {
    FILE     *fp = NULL;
    char      filepath[255];
    char      filename[40] = "input.txt";
    const int year = 2024;
    const int day = 13;

    struct Input input = {0};
    AocTimer_t  *timer = aoc_timer_new();

    aoc_timer_start(timer);

    if (argc > 1) {
        if (!strcmp("--test", argv[1])) {
            snprintf(filename, 39, "test_input.txt");
        }
    }
    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file (%s)\n", filepath);
        exit(EXIT_FAILURE);
    }

    char line[255];
    while (fgets(line, 255, fp) != NULL) {
        if (strlen(line) > 2) {
            if ((input.nparameters + 2) % 6 == 0) {
                sscanf(strchr(line, ':'), ": X=%ld, Y=%ld", &input.parameters[input.nparameters],
                       &input.parameters[input.nparameters + 1]);
            } else {
                sscanf(strchr(line, ':'), ": X+%ld, Y+%ld", &input.parameters[input.nparameters],
                       &input.parameters[input.nparameters + 1]);
            }
            input.nparameters += 2;
        }
    }
    fclose(fp);
    input.nparameters /= 6;

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new_str(1, solve_part_1, &input, 1);
    timer_func_new_str(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_BOTTOM | BORDER_TOP);

    aoc_timer_delete(timer);
    return EXIT_SUCCESS;
}
