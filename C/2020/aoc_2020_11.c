#include "aoc_header.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    uint8_t grid[100][100];
    size_t  rows;
    size_t  columns;
};

static const int8_t delta[8][2] = {
    {-1, -1},
    {-1, 0 },
    {-1, 1 },
    {0,  -1},
    {0,  1 },
    {1,  -1},
    {1,  0 },
    {1,  1 }
};

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isgraph((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}

static uint8_t count_visible(struct Input *grid, size_t row, size_t column) {
    uint8_t visible = 0;

    for (size_t i = 0; i < 8; i++) {
        size_t step = 1;
        while (1) {
            int32_t neighbour_row = row + step * delta[i][0];
            int32_t neighbour_column = column + step * delta[i][1];
            if ((0 <= neighbour_row) && (neighbour_row < (int32_t)grid->rows) &&
                (0 <= neighbour_column) && (neighbour_column < (int32_t)grid->columns)) {
                uint8_t seat = grid->grid[neighbour_row][neighbour_column];
                if ((seat == '#') || (seat == 'L')) {
                    if (seat == '#') {
                        visible += 1;
                    }
                    break;
                }
            } else {
                break;
            }
            step++;
        }
    }

    return visible;
}

static uint8_t count_occupied(struct Input *grid, size_t row, size_t column) {
    uint8_t occupied = 0;

    for (size_t i = 0; i < 8; i++) {
        int32_t neighbour_row = row + delta[i][0];
        int32_t neighbour_column = column + delta[i][1];
        if ((0 <= neighbour_row) && (neighbour_row < (int32_t)grid->rows) &&
            (0 <= neighbour_column) && (neighbour_column < (int32_t)grid->columns)) {
            if (grid->grid[neighbour_row][neighbour_column] == '#') {
                occupied += 1;
            }
        }
    }

    return occupied;
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint32_t      occupied = 0;

    struct Input working_grid = {0};
    struct Input input_grid = {0};

    memmove(&input_grid, input, sizeof(struct Input));
    memmove(&working_grid, input, sizeof(struct Input));

    while (1) {
        uint8_t changed = 0;
        for (size_t row = 0; row < input->rows; row++) {
            for (size_t column = 0; column < input->columns; column++) {
                switch (input_grid.grid[row][column]) {
                    case 'L':
                        if (count_occupied(&input_grid, row, column) == 0) {
                            working_grid.grid[row][column] = '#';
                            occupied++;
                            changed = 1;
                        }
                        break;
                    case '#':
                        if (count_occupied(&input_grid, row, column) >= 4) {
                            working_grid.grid[row][column] = 'L';
                            occupied--;
                            changed = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (!changed)
            break;

        memmove(&input_grid, &working_grid, sizeof(struct Input));
    }

    return occupied;
}

int solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint32_t      visible = 0;

    struct Input working_grid = {0};
    struct Input input_grid = {0};

    memmove(&input_grid, input, sizeof(struct Input));
    memmove(&working_grid, &input_grid, sizeof(struct Input));

    while (1) {
        uint8_t changed = 0;
        for (size_t row = 0; row < input->rows; row++) {
            for (size_t column = 0; column < input->columns; column++) {
                switch (input_grid.grid[row][column]) {
                    case 'L':
                        if (count_visible(&input_grid, row, column) == 0) {
                            working_grid.grid[row][column] = '#';
                            visible++;
                            changed = 1;
                        }
                        break;
                    case '#':
                        if (count_visible(&input_grid, row, column) >= 5) {
                            working_grid.grid[row][column] = 'L';
                            visible--;
                            changed = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (!changed)
            break;

        memmove(&input_grid, &working_grid, sizeof(struct Input));
    }

    return visible;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 11;

    struct Input input = {0};

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

    size_t index = 0;
    char  *trimmed_line = NULL;
    while (fgets(line, 254, fp) != NULL) {
        trimmed_line = str_trim_trailing(line);
        uint8_t *row = input.grid[index++];
        memmove(row, trimmed_line, (strlen(trimmed_line)) * sizeof(uint8_t));
    }
    input.rows = index;
    input.columns = strlen(trimmed_line);

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
