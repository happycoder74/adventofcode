#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int race_time;
    int race_distance;
} DataPoint_t;

AocArrayPtr clean_input(AocArrayPtr data) {
    DataPoint_t *data_point;
    AocArrayPtr  return_data = aoc_ptr_array_new();

    char *times = aoc_str_array_index(data, 0);
    char *start = strchr(times, ':') + 1;
    char *ptr = strtok(start, " ");
    while (ptr != NULL) {
        DataPoint_t *dp = (DataPoint_t *)malloc(sizeof(DataPoint_t));
        sscanf(ptr, "%d", &(dp->race_time));
        aoc_ptr_array_append(return_data, dp);
        ptr = strtok(NULL, " ");
    }
    char *distances = aoc_str_array_index(data, 1);
    start = strchr(distances, ':') + 1;
    ptr = strtok(start, " ");
    int i = 0;
    while (ptr != NULL) {
        DataPoint_t *dp = aoc_ptr_array_index(return_data, i++);
        sscanf(ptr, "%d", &(dp->race_distance));
        ptr = strtok(NULL, " ");
    }

    aoc_str_array_free(data);
    return return_data;
}

static void quadratic(double a, double b, double c, double *solutions) {
    solutions[0] = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    solutions[1] = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

    return;
}

void *solve_part_1(AocData_t *data) {

    AocArrayPtr races = data->data;
    uint64_t    product = 1;

    for (unsigned i = 0; i < races->length; i++) {
        double       solutions[2] = {0.0};
        DataPoint_t *dp = aoc_ptr_array_index(races, i);
        quadratic(-1, dp->race_time, -dp->race_distance, solutions);
        product *= (uint64_t)ceil(solutions[1]) - (uint64_t)floor(solutions[0]) - 1;
    }

    return strdup_printf("%lld", product);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr races = data->data;
    uint64_t    product = 1;
    char        time_string[100] = {0};
    char        distance_string[100] = {0};
    double      solutions[2];

    for (unsigned i = 0; i < races->length; i++) {
        DataPoint_t *dp = aoc_ptr_array_index(races, i);
        sprintf(time_string, "%s%d", time_string[0] == '\0' ? "" : time_string, dp->race_time);
        sprintf(distance_string, "%s%d", distance_string[0] == '\0' ? "" : distance_string, dp->race_distance);
    }

    quadratic(-1, atoi(time_string), -(double)atoll(distance_string), solutions);
    product = (uint64_t)ceil(solutions[1]) - (uint64_t)floor(solutions[0]) - 1;

    return strdup_printf("%lld", product);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int  year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    char *ptr = strtok(sourcefile, "_");
    ptr = strtok(NULL, "_");
    sscanf(ptr, "%d", &year);
    ptr = strtok(NULL, "_");
    sscanf(ptr, "%d", &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new_clean("test_input.txt", year, day, clean_input);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, clean_input);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
