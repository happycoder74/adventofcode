#include "aoc_header.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short int is_right_order(unsigned int table[100][100], unsigned int *update) {
    for (unsigned index = 1; index <= update[0]; index++) {
        unsigned int  node = update[index];
        unsigned int *targets = table[node];

        if (targets[0] == 0)
            continue;

        for (unsigned ii = 1; ii < index; ii++) {
            unsigned target = update[ii];
            for (unsigned int target_index = 0; targets[target_index] != 0; target_index++) {
                if (targets[target_index] == target) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

unsigned int reorder(unsigned int table[100][100], unsigned int *update) {
    unsigned int  reordered_update[200] = {0};
    unsigned int  return_update[200] = {0};
    unsigned int *targets = NULL;

    for (unsigned int index = 1; index <= update[0]; index++) {
        unsigned int node = update[index];
        targets = table[node];
        for (unsigned int ii = 1; ii <= update[0]; ii++) {
            for (unsigned int jj = 0; targets[jj] != 0; jj++) {
                if (update[ii] == targets[jj]) {
                    reordered_update[index] += 1;
                }
            }
        }
    }

    for (unsigned int i = 1; i <= update[0]; i++) {
        return_update[reordered_update[i] + 1] = update[i];
    }

    return return_update[(update[0] / 2) + 1];
}

struct Input {
    unsigned int table[100][100];
    unsigned int updates[200][100];
    size_t       n_updates;
};

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;

    unsigned int  count = 0;
    unsigned int *update = NULL;

    for (unsigned int i_update = 0; i_update < input->n_updates; i_update++) {
        update = input->updates[i_update];
        if (is_right_order(input->table, update)) {
            count += update[(update[0] / 2) + 1];
        }
    }

    return count;
}

int solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    unsigned int  count = 0;
    unsigned int *update;

    for (unsigned int i_update = 0; i_update < input->n_updates; i_update++) {
        update = input->updates[i_update];
        if (!is_right_order(input->table, update)) {
            count += reorder(input->table, update);
        }
    }

    return count;
}

int main(int argc, char **argv) {

    FILE        *fp = NULL;
    char         filepath[255];
    char         filename[40] = "input.txt";
    const int    year = 2024;
    const int    day = 5;
    struct Input input = {0};

    AocTimer_t *timer = aoc_timer_new();

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

    char line[1000];

    unsigned int node, target;

    while (fgets(line, 1000, fp) != NULL) {
        if (isdigit(line[0])) {
            sscanf(line, "%u|%u", &node, &target);
            unsigned int column = 0;
            while (input.table[node][column] != 0) {
                column++;
            }
            input.table[node][column] = target;
        } else {
            break;
        }
    }
    size_t line_counter = 0;
    char  *pointer = NULL;
    while (fgets(line, 1000, fp) != NULL) {
        pointer = strtok(line, ", ");
        unsigned int value = 0;

        while (pointer != NULL) {
            sscanf(pointer, "%u", &input.updates[line_counter][value + 1]);
            pointer = strtok(NULL, ", ");
            value++;
        }
        input.updates[line_counter++][0] = value;
    }
    input.n_updates = line_counter;

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return EXIT_SUCCESS;
}
