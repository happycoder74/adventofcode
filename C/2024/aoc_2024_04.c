#include "aoc_header.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    char **matrix;
    size_t dimension;
};

static unsigned short int in_grid(int row, int col, struct Input *inp) {
    if ((row < 0) || (col < 0))
        return 0;
    if ((row >= (int)inp->dimension) || (col >= (int)inp->dimension))
        return 0;

    return 1;
}

int solve_part_1(void *input) {
    struct Input *inp = (struct Input *)input;

    unsigned int count = 0;

    for (int row = 0; row < (int)inp->dimension; row++) {
        for (int col = 0; col < (int)inp->dimension; col++) {
            if (inp->matrix[row][col] != 'X')
                continue;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (((dr == 0) && (dc == 0)) || !in_grid((row + 3 * dr), (col + 3 * dc), inp))
                        continue;
                    if ((inp->matrix[row + dr][col + dc] == 'M') &&
                        (inp->matrix[row + 2 * dr][col + 2 * dc] == 'A') &&
                        (inp->matrix[row + 3 * dr][col + 3 * dc] == 'S')) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int solve_part_2(void *input) {
    unsigned int  count = 0;
    struct Input *inp = (struct Input *)input;

    char pattern[4][5] = {
        {'M', 'M', 'S', 'S'},
        {'S', 'M', 'S', 'M'},
        {'S', 'S', 'M', 'M'},
        {'M', 'S', 'M', 'S'}
    };

    for (unsigned int i = 1; i < inp->dimension - 1; i++) {
        for (unsigned int j = 1; j < inp->dimension - 1; j++) {
            if (inp->matrix[i][j] != 'A') {
                continue;
            }
            for (unsigned int i_pattern = 0; i_pattern < 4; i_pattern++) {
                short int match = (inp->matrix[i - 1][j - 1] == pattern[i_pattern][0]);
                match = match && (inp->matrix[i - 1][j + 1] == pattern[i_pattern][1]);
                match = match && (inp->matrix[i + 1][j - 1] == pattern[i_pattern][2]);
                match = match && (inp->matrix[i + 1][j + 1] == pattern[i_pattern][3]);
                if (match) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int main(int argc, char **argv) {

    FILE     *fp = NULL;
    char      filepath[255];
    char      filename[40] = "input.txt";
    size_t    dimension = 200;
    const int year = 2024;
    const int day = 4;

    struct Input input = {0};
    AocTimer_t  *timer = aoc_timer_new();

    aoc_timer_start(timer);

    input.matrix = (char **)malloc(dimension * sizeof(char *));

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

    char   line[1000];
    size_t line_counter = 0;

    while (fgets(line, 1000, fp) != NULL) {
        input.matrix[line_counter] = (char *)calloc(strlen(line), sizeof(char));
        memmove(input.matrix[line_counter], line, strlen(line) * sizeof(char));
        line_counter++;
    }
    input.dimension = line_counter;

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_BOTTOM | BORDER_TOP);

    free(input.matrix);
    aoc_timer_delete(timer);
    return EXIT_SUCCESS;
}
