#include "aoc_header.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static unsigned short int lights[10000000] = {0};

enum Operation {
    ON,
    OFF,
    TOGGLE
};

struct Record {
    unsigned int   x0;
    unsigned int   x1;
    unsigned int   y0;
    unsigned int   y1;
    enum Operation operation;
};

struct Input {
    struct Record records[1000];
    size_t        count;
};

int solve_part_1(void *inp) {
    struct Input  *input = (struct Input *)inp;
    struct Record *record = NULL;

    for (size_t index = 0; index < input->count; index++) {
        record = input->records + index;
        for (size_t r = record->y0; r <= record->y1; r++) {
            for (size_t c = record->x0; c <= record->x1; c++) {
                switch (record->operation) {
                    case ON:
                        lights[c + r * 1000] = 1;
                        break;
                    case OFF:
                        lights[c + r * 1000] = 0;
                        break;
                    case TOGGLE:
                        lights[c + r * 1000] ^= 1;
                        break;
                    default:
                        fprintf(stderr, "Should not happen!\n");
                        exit(EXIT_FAILURE);
                }
            }
        }
    }
    int count = 0;

    for (unsigned int i = 0; i < 1000000; i++) {
        count += lights[i];
    }

    return count;
}

int solve_part_2(void *inp) {
    struct Input  *input = (struct Input *)inp;
    struct Record *record = NULL;
    memset(lights, 0, 1000000 * sizeof(lights[0]));

    for (size_t index = 0; index < input->count; index++) {
        record = input->records + index;
        for (size_t r = record->y0; r <= record->y1; r++) {
            for (size_t c = record->x0; c <= record->x1; c++) {
                switch (record->operation) {
                    case ON:
                        lights[c + r * 1000] += 1;
                        break;
                    case OFF:
                        if (lights[c + r * 1000] <= 1)
                            lights[c + r * 1000] = 0;
                        else
                            lights[c + r * 1000] -= 1;
                        break;
                    case TOGGLE:
                        lights[c + r * 1000] += 2;
                        break;
                    default:
                        fprintf(stderr, "Should not happen!\n");
                        exit(EXIT_FAILURE);
                }
            }
        }
    }
    int brightness = 0;

    for (unsigned int i = 0; i < 1000000; i++) {
        brightness += lights[i];
    }

    return brightness;
}

int main(int argc, char **argv) {
    FILE              *fp = NULL;
    unsigned short int test = 0;
    char               filepath[255];
    char               line[255] = {0};

    struct Input input = {0};
    const int    year = 2015;
    const int    day = 6;

    AocTimer_t *timer = aoc_timer_new();

    aoc_timer_start(timer);
    if ((argc > 1) && !strcmp(argv[1], "--test")) {
        test = 1;
    }

    snprintf(filepath, 254, "%s/%d/%02d/%sinput.txt", getenv("AOC_DATA_LOCATION"), year, day,
             test ? "test_" : "");

    if (!(fp = fopen(filepath, "r"))) {
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    while (fgets(line, 254, fp) != NULL) {
        char *ptr = line;
        while (!isdigit((unsigned char)*ptr)) {
            ptr++;
        }
        sscanf(ptr, "%d,%d through %d,%d", &input.records[index].x0, &input.records[index].y0,
               &input.records[index].x1, &input.records[index].y1);

        if (strstr(line, "on")) {
            input.records[index].operation = ON;
        } else if (strstr(line, "off")) {
            input.records[index].operation = OFF;
        } else {
            input.records[index].operation = TOGGLE;
        }

        index++;
    }
    input.count = index;

    fclose(fp);

    aoc_timer_stop(timer);
    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_BOTTOM | BORDER_TOP);
    aoc_timer_delete(timer);

    return EXIT_SUCCESS;
}
