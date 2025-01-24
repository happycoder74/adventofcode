#include "aoc_header.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct Bus {
    uint32_t bus_id;
    int32_t  offset;
};

struct Input {
    uint32_t   timestamp;
    struct Bus bus_list[100];
    struct Bus bus_list_sorted[100];
    size_t     bus_count;
};

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    int           result = 0;

    uint32_t min_wait = UINT32_MAX;
    for (size_t index = 0; index < input->bus_count; index++) {
        uint32_t id = input->bus_list[index].bus_id;
        uint32_t wait_time = (id - (input->timestamp % id));
        if (wait_time < min_wait) {
            min_wait = wait_time;
            result = min_wait * id;
        }
    }

    return result;
}

uint64_t solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;

    struct Bus *bus_list = input->bus_list;
    struct Bus *bus = bus_list;

    uint64_t timestamp = 0;
    int      start = 1;
    uint64_t step = bus->bus_id;
    while (1) {
        timestamp += step;
        uint8_t valid = 1;
        for (size_t bus_index = start; bus_index < input->bus_count; bus_index++) {
            bus = bus_list + bus_index;
            if ((timestamp + bus->offset) % bus->bus_id) {
                valid = 0;
                break;
            }
            start += 1;
            step *= bus->bus_id;
        }
        if (valid) {
            return timestamp;
        }
    }
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 13;

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

    input.bus_count = 0;
    if (!fgets(line, 254, fp)) {
        fprintf(stderr, "Premature end of file\n");
    }
    input.timestamp = atoi(line);
    if (!fgets(line, 254, fp)) {
        fprintf(stderr, "Premature end of file\n");
    }
    char  *token = strtok(line, ",");
    size_t index = 0;
    while (token) {
        if (strcmp(token, "x")) {
            input.bus_list[input.bus_count].bus_id = atoi(token);
            input.bus_list[input.bus_count].offset = index;
            input.bus_count++;
        }
        index++;
        token = strtok(NULL, ",");
    }
    memmove(&input.bus_list_sorted, &input.bus_list, input.bus_count * sizeof(struct Bus));

    fclose(fp);

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_uint64(2, solve_part_2, &input, 1, NULL);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
