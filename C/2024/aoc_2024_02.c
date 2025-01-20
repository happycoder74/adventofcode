#include "aoc_header.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Input {
    unsigned int data[1000][30];
    size_t       dimension;
};

int solve_part_1(void *instructions) {
    struct Input *input = (struct Input *)instructions;
    unsigned int  result = 0;

    for (unsigned int i = 0; i < input->dimension; i++) {
        unsigned int nvalues = input->data[i][0];
        short int    increasing = (((int)input->data[i][2] - (int)input->data[i][1]) > 0);
        short int    valid = 1;

        for (unsigned int ival = 1; ival < nvalues; ival++) {
            int       diff = (input->data[i][ival + 1] - input->data[i][ival]);
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

int solve_part_2(void *instructions) {
    struct Input *input = (struct Input *)instructions;
    unsigned int  result = 0;
    unsigned int  checkline[30];
    unsigned int  nvalues;
    for (unsigned int i = 0; i < input->dimension; i++) {
        for (unsigned int remove_level = 0; remove_level <= input->data[i][0]; remove_level++) {
            memset(checkline, 0, sizeof checkline);
            nvalues = input->data[i][0];

            unsigned int copy_level = 1;
            if (remove_level == 0) {
                memcpy(checkline, input->data[i], 30 * sizeof(unsigned int));
            } else {
                checkline[0] = input->data[i][0];
                for (unsigned int index = 1; index <= nvalues; index++) {
                    if (index != remove_level) {
                        checkline[copy_level++] = input->data[i][index];
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

int main(int argc, char **argv) {

    FILE *fp = NULL;
    char  filepath[255];
    char  filename[40] = "input.txt";
    char  line[1000];

    struct Input input = {0};
    int          year = 2024;
    int          day = 2;
    AocTimer_t  *timer = aoc_timer_new();

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

    char        *pointer = NULL;
    unsigned int line_counter = 0;
    while (fgets(line, 1000, fp) != NULL) {
        unsigned int counter = 1;
        pointer = strtok(line, " ");
        while (pointer != NULL) {
            sscanf(pointer, "%u", &input.data[line_counter][counter++]);
            pointer = strtok(NULL, " ");
        }
        input.data[line_counter][0] = counter - 1;
        line_counter++;
    }
    input.dimension = line_counter;

    fclose(fp);
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
