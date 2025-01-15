#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int solve_part_1(int *arr1, unsigned int len1, int *arr2, unsigned int len2) {
    qsort(arr1, len1, sizeof(int), compare);
    qsort(arr2, len2, sizeof(int), compare);

    unsigned int result = 0;

    for (unsigned int i = 0; i < len1; i++) {
        result += abs(arr1[i] - arr2[i]);
    }
    return result;
}

int solve_part_2(int *arr1, unsigned int len1, int *arr2) {
    int result = 0;
    unsigned int count1 = 1;

    for (unsigned int i = 0; i < len1; i++) {
        unsigned count2 = 0;
        if (arr1[i + 1] == arr1[i]) {
            count1++;
        } else {
            for (unsigned int j = 0; j < len1; j++) {
                if (arr2[j] == arr1[i])
                    count2++;
            }
            result += count1 * arr1[i] * count2;
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

    FILE        *fp = NULL;
    int          arr1[1001] = {0};
    int          arr2[1001] = {0};
    char         line[1000];
    char        *res;
    unsigned int counter = 0;
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);
    fp = fopen("/home/christian/projects/adventofcode/data/2024/01/input.txt", "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        res = fgets(line, 1000, fp);
        if (res != NULL) {
            sscanf(line, "%d  %d", &arr1[counter], &arr2[counter]);
            counter++;
        } else {
            break;
        }
    }

    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %10d", solve_part_1(arr1, counter, arr2, counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2(arr1, counter, arr2));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
    return 0;
}
