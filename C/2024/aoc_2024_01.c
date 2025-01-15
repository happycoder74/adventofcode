#define _XOPEN_SOURCE 600
#include "aoc_io.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
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

int main() {

    FILE           *fp = NULL;
    char            filename[255];
    char            line[1000];
    const int       year = 2024;
    const int       day = 1;
    struct Input    input = {0};
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
    sprintf(filename, "%s/%d/%02d/input.txt", getenv("AOC_DATA_LOCATION"), year, day);

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 1000, fp) != NULL) {
        sscanf(line, "%d  %d", &input.arr1[input.len], &input.arr2[input.len]);
        input.len++;
    }

    clock_gettime(CLOCK_REALTIME, &stop);

    aoc_header(year, day);
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
    timer_func_new(1, solve_part_1, (void *)&input, 1);
    timer_func_new(2, solve_part_2, (void *)&input, 1);
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "--------------------------------------------------------\n");
    fprintf(stdout, "Total time:");
    fprintf(stdout, "%29.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
    return 0;
}
