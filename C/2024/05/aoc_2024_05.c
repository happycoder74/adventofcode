#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned short int is_right_order(unsigned int table[100][100], unsigned int *update) {
    unsigned short int right_order = 1;

    unsigned int  node;
    unsigned int *targets = NULL;

    for (unsigned index = 1; (index <= update[0]) && (right_order); index++) {
        node = update[index];
        targets = table[node];

        if (targets[0] == 0)
            continue;

        unsigned int target = 0;
        unsigned     ii;

        unsigned short int found;
        for (ii = 1; (ii < index) && (!found); ii++) {
            target = update[ii];
            found = 0;
            for (unsigned int target_index = 0; targets[target_index] != 0; target_index++) {
                if (targets[target_index] == target) {
                    found = 1;
                    right_order = 0;
                    break;
                }
            }
        }
    }
    return right_order;
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

int solve_part_1(unsigned int table[100][100], unsigned int updates[200][100],
                 unsigned int n_updates) {

    unsigned int  count = 0;
    unsigned int *update = NULL;

    for (unsigned int i_update = 0; i_update < n_updates; i_update++) {
        update = updates[i_update];
        if (is_right_order(table, update)) {
            count += update[(update[0] / 2) + 1];
        }
    }

    return count;
}

int solve_part_2(unsigned int table[100][100], unsigned int updates[200][100],
                 unsigned int n_updates) {
    unsigned int  count = 0;
    unsigned int *update;
    unsigned int  reordered_update[200] = {0};

    for (unsigned int i_update = 0; i_update < n_updates; i_update++) {
        update = updates[i_update];
        if (!is_right_order(table, update)) {
            count += reorder(table, update);
        }
    }

    return count;
}

int main(int argc, char **argv) {

    FILE        *fp = NULL;
    char         filepath[255];
    char         filename[40] = "input.txt";
    unsigned int table[100][100] = {0};
    unsigned int rules[200][100] = {0};

    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if (argc > 1) {
        if (!strcmp("--test", argv[1])) {
            sprintf(filename, "test_input.txt");
        }
    }
    sprintf(filepath, "%s/2024/05/%s", getenv("AOC_DATA_LOCATION"), filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    char line[1000];

    unsigned int node, target;

    while (fgets(line, 1000, fp) != NULL) {
        if (isdigit(line[0])) {
            sscanf(line, "%u|%u", &node, &target);
            unsigned int column = 0;
            while (table[node][column] != 0) {
                column++;
            }
            table[node][column] = target;
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
            sscanf(pointer, "%u", &rules[line_counter][value + 1]);
            pointer = strtok(NULL, ", ");
            value++;
        }
        rules[line_counter++][0] = value;
    }

    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %10d", solve_part_1(table, rules, line_counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2(table, rules, line_counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
}
