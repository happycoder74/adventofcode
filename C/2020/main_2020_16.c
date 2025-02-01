#include "aoc_2020_16.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char line[255] = {0};
    while (fgets(line, sizeof(line), file)) {
        char *str = trim_end(line);
        if ((!strncmp(str, "your", 4))) {
            char *ignored = fgets(line, sizeof(line), file);
            if (!ignored) {
                fprintf(stderr, "Hmmm...\n");
            }
            struct Ticket *myticket = &input.myticket;
            read_ticket(myticket, line);
        } else if ((strchr(str, ':') != NULL) && (strncmp(str, "near", 4))) {
            struct Class *class = &input.classes[input.class_count++];
            struct Range *range1 = &class->range1;
            struct Range *range2 = &class->range2;

            char *splitstart = strchr(line, ':');
            memmove(class->name, line, (splitstart - line));
            sscanf(splitstart + 1, "%d-%d or %d-%d", &range1->start, &range1->end, &range2->start,
                   &range2->end);

        } else if (isdigit(line[0])) {
            struct Ticket *nearby = &input.nearbys[input.nearby_count++];
            read_ticket(nearby, line);
        }
    }

    fclose(file);

    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_uint64(2, solve_part_2, &input, 1, NULL);

    return 0;
}
