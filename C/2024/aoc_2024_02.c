#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int solve_part_1(unsigned int data[1000][30], unsigned int dimension) {
    unsigned int result = 0;

    for (unsigned int i = 0; i < dimension; i++) {
        unsigned int nvalues = data[i][0];
        short int    increasing = (((int)data[i][2] - (int)data[i][1]) > 0);
        short int    valid = 1;

        for (unsigned int ival = 1; ival < nvalues; ival++) {
            int       diff = (data[i][ival + 1] - data[i][ival]);
            short int direction = (diff > 0);
            if ((direction != increasing) || (abs(diff) > 3) || (abs(diff) < 1)) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            result += 1;
        }
    }

    return result;
}

int solve_part_2(unsigned int data[1000][30], unsigned int dimension) {
    unsigned int result = 0;
    unsigned int checkline[30];
    unsigned int nvalues;
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int remove_level = 0; remove_level <= data[i][0]; remove_level++) {
            memset(checkline, 0, sizeof checkline);
            nvalues = data[i][0];

            unsigned int copy_level = 1;
            if (remove_level == 0) {
                memcpy(checkline, data[i], 30 * sizeof(unsigned int));
            } else {
                checkline[0] = data[i][0];
                for (unsigned int index = 1; index <= nvalues; index++) {
                    if (index != remove_level) {
                        checkline[copy_level++] = data[i][index];
                    }
                }
                nvalues -= 1;
            }
            short int increasing = (((int)checkline[2] - (int)checkline[1]) > 0);
            short int valid = 1;
            for (unsigned int ival = 1; ival < nvalues; ival++) {
                int       diff = (checkline[ival + 1] - checkline[ival]);
                short int direction = (diff > 0);
                if ((direction != increasing) || (abs(diff) > 3) || (abs(diff) < 1)) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                result += 1;
                break;
            }
        }
    }
    return result;
}

int main(void) {

    FILE           *fp = NULL;
    char            filename[255];
    unsigned int    data[1000][30];
    char            line[1000];
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    sprintf(filename, "%s/2024/02/input.txt", getenv("AOC_DATA_LOCATION"));

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    char        *pointer = NULL;
    unsigned int line_counter = 0;
    while (fgets(line, 1000, fp) != NULL) {
        unsigned int counter = 1;
        pointer = strtok(line, " ");
        while (pointer != NULL) {
            sscanf(pointer, "%u", &data[line_counter][counter++]);
            pointer = strtok(NULL, " ");
        }
        data[line_counter][0] = counter - 1;
        line_counter++;
    }

    fclose(fp);
    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %10d", solve_part_1(data, line_counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2(data, line_counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
    return 0;
}
