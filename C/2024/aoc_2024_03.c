#include <cstdlib>
#define _XOPEN_SOURCE 600
#include "aoc_io.h"
#include "aoc_timer.h"
#include <pcre2posix.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct Input {
    char           lines[10][4000];
    unsigned int   nlines;
    unsigned short part;
};

int solver(void *instructions) {
    struct Input *input = (struct Input *)instructions;
    regex_t       re;
    size_t        nmatches = 4;
    regmatch_t    matches[4];

    char pattern[] = "(mul\\((\\d{1,3}),(\\d{1,3})\\)|don\\'t\\(\\)|do\\(\\))";

    pcre2_regcomp(&re, pattern, 0);

    unsigned  result = 0;
    short int enabled = 1;
    for (unsigned int line_counter = 0; line_counter < input->nlines; line_counter++) {
        char  *str = input->lines[line_counter];
        size_t offset = 0;
        while (pcre2_regexec(&re, str + offset, nmatches, matches, 0) == 0) {
            unsigned int counter;
            for (counter = 0; (counter < nmatches) && (matches[counter].rm_so != -1); counter++) {
                size_t start = matches[counter].rm_so;
                size_t end = matches[counter].rm_eo;
                char   substring[100] = {0};
                strncpy(substring, str + offset + start, end - start);
                if ((strncmp(substring, "mul", 3) == 0) && enabled) {
                    unsigned int v1 = 0, v2 = 0;
                    sscanf(substring, "mul(%d,%d)", &v1, &v2);
                    result += v1 * v2;
                    counter += 3;
                } else if (strncmp(substring, "do(", 3) == 0) {
                    enabled = 1;
                    counter += 1;
                } else if (strncmp(substring, "don", 3) == 0) {
                    if (input->part == 2) {
                        enabled = 0;
                    }
                    counter += 1;
                }
            }
            offset += matches[counter - 1].rm_eo;
        }
    }
    return result;
}

int main(int argc, char **argv) {

    FILE     *fp = NULL;
    char      filepath[255];
    char      filename[40] = "input.txt";
    const int year = 2024;
    const int day = 3;

    struct Input    input = {0};
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
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
    unsigned int line_counter = 0;
    while (fgets(input.lines[line_counter], 4000, fp) != NULL) {
        line_counter++;
    }
    fclose(fp);
    input.nlines = line_counter;
    clock_gettime(CLOCK_REALTIME, &stop);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", &start, &stop, BORDER_BOTTOM);
    input.part = 1;
    timer_func_new(1, solver, (void *)&input, 1);
    input.part = 2;
    timer_func_new(2, solver, (void *)&input, 1);
    clock_gettime(CLOCK_REALTIME, &stop);
    aoc_timer_gen("Total time:", &start, &stop, BORDER_TOP | BORDER_BOTTOM);
    return EXIT_SUCCESS;
}
