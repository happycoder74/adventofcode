#include "aoc_2020_17.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *data_directory = getenv("AOC_DATA_LOCATION");

    char      filepath[255] = {0};
    const int year = 2020;
    const int day = 17;

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

    char  line[255] = {0};
    char *str = NULL;
    int   r = 0;
    input.w_min = 0;
    input.w_max = 0;
    input.z_min = 0;
    input.z_max = 0;
    input.x_min = 0;
    input.y_min = 0;
    input.x_max = 0;
    input.y_max = 0;
    while (fgets(line, sizeof(line), file)) {
        str = trim_end(line);
        if (input.x_max == 0) {
            input.x_max = strlen(str) - 1;
            input.y_max = input.x_max;
        }
        for (int c = 0; c < (int)strlen(str); c++) {
            if (str[c] == '#') {
                unsigned int key = get_key(c, r, 0, 0, &input);
                input.grid[key] = 1;
            }
        }
        r++;
    }

    fclose(file);

    struct Input clone = input;
    memmove(clone.grid, input.grid, sizeof(input.grid) / sizeof(input.grid[0]));
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &clone, 1);

    return 0;
}
