#include <stdio.h>
#include <stdlib.h>

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

#define MAX(_A_, _B_) (_A_) > (_B_) ? (_A_) : (_B_)

int solve_part_2(int *arr1, unsigned int len1, int *arr2, unsigned int len2) {
    unsigned int *table = NULL;

    unsigned int max1 = 0, max2 = 0;

    for (unsigned int i = 0; i < len1; i++) {
        if (arr1[i] > max1)
            max1 = arr1[i];
        if (arr2[i] > max2)
            max2 = arr2[i];
    }

    table = calloc(MAX(max1, max2), sizeof(unsigned int));

    for (unsigned int i = 0; i < len1; i++) {
        table[arr2[i]] += 1;
    }

    int result = 0;
    for (unsigned int i = 0; i < len1; i++) {
        result += arr1[i] * table[arr1[i]];
    }

    return result;
}

int main() {

    FILE        *fp = NULL;
    int          arr1[1000];
    int          arr2[1000];
    char         line[1000];
    char        *res;
    unsigned int counter = 0;

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

    fprintf(stdout, "=======\n");
    fprintf(stdout, "Solution to part 1: %d\n", solve_part_1(arr1, counter, arr2, counter));
    fprintf(stdout, "Solution to part 2: %d\n", solve_part_2(arr1, counter, arr2, counter));
    return 0;
}
