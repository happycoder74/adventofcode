#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long solver(const long *param, const unsigned long np, const unsigned long delta) {
    unsigned long result = 0;
    unsigned long a_press;
    unsigned long b_press;

    for (unsigned long ip = 0; ip < np; ip++) {
        long a = param[0 + ip * 6];
        long c = param[1 + ip * 6];
        long b = param[2 + ip * 6];
        long d = param[3 + ip * 6];
        long bx = param[4 + ip * 6] + delta;
        long by = param[5 + ip * 6] + delta;

        if ((((d * bx - b * by) % (a * d - b * c)) != 0) ||
            (((-c * bx + a * by) % (a * d - b * c)) != 0)) {
            continue;
        }

        a_press = (d * bx - b * by) / (a * d - b * c);
        b_press = (-c * bx + a * by) / (a * d - b * c);

        result += 3 * a_press + b_press;
    }
    return result;
}

long solve_part_1(const long *param, const unsigned long np) {
    return solver(param, np, 0);
}

long solve_part_2(const long *param, const unsigned long np) {
    return solver(param, np, 10000000000000);
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  filepath[255];
    char  filename[40] = "input.txt";
    long  parameters[6 * 400];

    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if (argc > 1) {
        if (!strcmp("--test", argv[1])) {
            sprintf(filename, "test_input.txt");
        }
    }
    sprintf(filepath, "%s/2024/13/%s", getenv("AOC_DATA_LOCATION"), filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    unsigned long nparameters = 0;
    char          line[255];
    while (fgets(line, 255, fp) != NULL) {
        if (strlen(line) > 2) {
            if ((nparameters + 2) % 6 == 0) {
                sscanf(strchr(line, ':'), ": X=%ld, Y=%ld", &parameters[nparameters],
                       &parameters[nparameters + 1]);
            } else {
                sscanf(strchr(line, ':'), ": X+%ld, Y+%ld", &parameters[nparameters],
                       &parameters[nparameters + 1]);
            }
            nparameters += 2;
        }
    }
    fclose(fp);
    nparameters /= 6;

    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%25.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %15ld", solve_part_1(parameters, nparameters));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %15ld", solve_part_2(parameters, nparameters));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
}
