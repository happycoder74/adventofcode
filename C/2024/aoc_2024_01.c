#define _XOPEN_SOURCE 600
#include "aoc_io.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Input {
    int    arr1[1001];
    int    arr2[1001];
    size_t len;
};

static int compare(const void *a, const void *b) {
    int *v_a = (int *)a;
    int *v_b = (int *)b;
    if (*v_a < *v_b) {
        return -1;
    } else if (*v_a > *v_b) {
        return 1;
    }

    return 0;
}

int solve_part_1(void *input) {
    struct Input *inp = (struct Input *)input;
    int          *arr1 = inp->arr1;
    int          *arr2 = inp->arr2;
    size_t        len = inp->len;

    qsort(arr1, len, sizeof(int), compare);
    qsort(arr2, len, sizeof(int), compare);

    unsigned int result = 0;

    for (unsigned int i = 0; i < len; i++) {
        result += abs(arr1[i] - arr2[i]);
    }
    return result;
}

int solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    int           result = 0;
    unsigned int  count1 = 1;

    for (unsigned int i = 0; i < input->len; i++) {
        unsigned count2 = 0;
        if (input->arr1[i + 1] == input->arr1[i]) {
            count1++;
        } else {
            for (unsigned int j = 0; j < input->len; j++) {
                if (input->arr2[j] == input->arr1[i])
                    count2++;
            }
            result += count1 * input->arr1[i] * count2;
            count1 = 1;
        }
    }

    /* for (unsigned int i = 0; i < len1; i++) { */
    /*     if (arr1[i] > max1) */
    /*         max1 = arr1[i]; */
    /*     if (arr2[i] > max2) */
    /*         max2 = arr2[i]; */
    /* } */

    /* table = calloc(MAX(max1, max2), sizeof(unsigned int)); */

    /* for (unsigned int i = 0; i < len1; i++) { */
    /*     table[arr2[i]] += 1; */
    /* } */

    /* int result = 0; */
    /* for (unsigned int i = 0; i < len1; i++) { */
    /*     result += arr1[i] * table[arr1[i]]; */
    /* } */

    /* free(table); */
    return result;
}

int main(int argc, char **argv) {

    FILE        *fp = NULL;
    char         filename[40] = "input.txt";
    char         filepath[255];
    char         line[1000];
    const int    year = 2024;
    const int    day = 1;
    struct Input input = {0};
    AocTimer_t   timer = {0};

    aoc_timer_start(&timer);

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

    while (fgets(line, 1000, fp) != NULL) {
        sscanf(line, "%d  %d", &input.arr1[input.len], &input.arr2[input.len]);
        input.len++;
    }

    aoc_timer_stop(&timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", &timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, (void *)&input, 1);
    timer_func_new(2, solve_part_2, (void *)&input, 1);
    aoc_timer_stop(&timer);
    aoc_timer_gen("Total time:", &timer, BORDER_TOP | BORDER_BOTTOM);
    return EXIT_SUCCESS;
}
