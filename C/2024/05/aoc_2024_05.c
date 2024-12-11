#include <ctype.h>
#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int solve_part_1(unsigned int table[100][100], unsigned int updates[200][100],
                 unsigned int n_updates) {

    unsigned int  count = 0;
    unsigned int *update = NULL;
    unsigned int *targets = NULL;

    for (unsigned int i_update = 0; i_update < n_updates; i_update++) {
        short int    right_order = 1;
        unsigned int node;
        update = updates[i_update];

        for (unsigned index = 1; index <= update[0]; index++) {
            node = update[index];
            targets = table[node];

            if (targets[0] == 0)
                continue;

            unsigned int target = 0;
            unsigned int ii = index + 1;
            for (unsigned jj = ii; jj <= update[0]; jj++) {
                target = update[jj];
                unsigned short int found = 0;
                /* Check if update number is in node target list */
                for (unsigned int target_index = 0; targets[target_index] != 0; target_index++) {
                    if (targets[target_index] == target) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    right_order = 0;
                    break;
                }
                ii++;
            }
            if (!right_order) {
                break;
            }
            ii = 1;
            for (unsigned jj = ii; jj < index; jj++) {
                target = update[jj];
                unsigned short int found = 0;
                for (unsigned int target_index = 0; targets[target_index] != 0; target_index++) {
                    if (targets[target_index] == target) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    right_order = 0;
                    break;
                }
                ii++;
            }
            if (!right_order) {
                break;
            }
        }
        if (right_order) {
            count += update[(update[0] / 2) + 1];
        }
    }

    return count;
}

int solve_part_2(void) {
    unsigned int count = 0;

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
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2());
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
}
