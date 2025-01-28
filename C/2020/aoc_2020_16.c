#include "aoc_timer.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Range {
    uint32_t start;
    uint32_t end;
};

struct Ticket {
    uint32_t tickets[100];
    uint32_t ticket_count;
};

struct Input {
    struct Range  ranges[100];
    uint32_t      range_count;
    struct Ticket nearbys[1000];
    uint32_t      nearby_count;
    struct Ticket myticket;
};

static char *trim_end(char *str) {
    if (str == NULL) {
        return NULL;
    }

    char *end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';
    return str;
}

__attribute__((unused)) static void print_range(struct Range *range) {
    printf("[%d - %d]\n", range->start, range->end);
}
static int read_ticket(struct Ticket *ticket, char *line) {
    int   number_of_tokens = 0;
    char *token = strtok(line, ",");
    while (token != NULL) {
        ticket->tickets[ticket->ticket_count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    return number_of_tokens;
}

static uint8_t check_ranges(struct Input *input, uint32_t ticket) {
    struct Range *range = NULL;

    for (size_t r = 0; r < input->range_count; r++) {
        range = input->ranges + r;
        if ((range->start <= ticket) && (ticket <= range->end))
            return 1;
    }
    return 0;
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint32_t      invalid = 0;

    struct Ticket *nearby = NULL;
    for (size_t i = 0; i < input->nearby_count; i++) {
        nearby = input->nearbys + i;
        for (size_t n = 0; n < nearby->ticket_count; n++) {
            if (!check_ranges(input, nearby->tickets[n]))
                invalid += nearby->tickets[n];
        }
    }
    return invalid;
}

int solve_part_2(void) {
    return 0;
}

int main(int argc, char *argv[]) {
    char *data_directory = getenv("AOC_DATA_LOCATION");

    char      filepath[255] = {0};
    const int year = 2020;
    const int day = 16;

    struct Input input = {0};

    char filename[40] = "input.txt";
    if (argc > 1) {
        if (!strcmp(argv[1], "--test")) {
            snprintf(filename, sizeof(filename) - 1, "test_input.txt");
        } else {
            snprintf(filename, sizeof(filename) - 1, "%s", argv[1]);
        }
    }
    snprintf(filepath, sizeof(filepath), "%s/%d/%02d/%s", data_directory, year, day, filename);

    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Failed to open file: %s\n", filepath);
        return 1;
    }

    char field[40] = {0};
    char line[255] = {0};
    while (fgets(line, sizeof(line), file)) {
        char *str = trim_end(line);
        if ((!strncmp(str, "your", 4))) {
            fgets(line, sizeof(line), file);
            struct Ticket *myticket = &input.myticket;
            read_ticket(myticket, line);
        } else if ((strchr(str, ':') != NULL) && (strncmp(str, "near", 4))) {
            struct Range *range1 = &input.ranges[input.range_count++];
            struct Range *range2 = &input.ranges[input.range_count++];
            sscanf(line, "%s %d-%d or %d-%d", field, &range1->start, &range1->end, &range2->start,
                   &range2->end);
        } else if (isdigit(line[0])) {
            struct Ticket *nearby = &input.nearbys[input.nearby_count++];
            read_ticket(nearby, line);
        }
    }

    fclose(file);

    timer_func_new(1, solve_part_1, &input, 1);

    return 0;
}
