#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_array.h"

int sort_function(const void *a, const void *b) {
    int *int_a = (int *)a;
    int *int_b = (int *)b;

    return (*int_a) - (*int_b);
}


int arr_index(int *arr, int value, int length) {
    // Search for first occurance of value in array
    int i;
    for (i = 0; i < length; i++) {
        if (arr[i] == value) {
            return i;
        }
    }

    // return -1 if value not in array
    return -1;
}

char **transpose_array(AocArrayPtr data, int *columns) {
    char **col_array;
    int i, col;
    unsigned int row;
    char *line;

    (*columns) = strlen(aoc_str_array_index(data, 0));

    // Initialize and allocate memory for columns
    col_array = (char **)calloc(*columns, sizeof(char *));
    for (i = 0; i < *columns; i++)
        col_array[i] = (char *)calloc(aoc_array_length(data) + 1, sizeof(char));

    // "Transpose" the input array and make sure the char* arrays
    // are NULL terminated.
    for (row = 0; row < aoc_array_length(data); row++) {
        line = aoc_str_array_index(data, row);
        for (col = 0; col < *columns; col++) {
            col_array[col][row] = line[col];
            if (row == aoc_array_length(data) -1) {
                col_array[col][row + 1] = '\0';
            }
        }
    }

    return col_array;

}

void *solve_part_1(AocData_t *data) {
    unsigned int i;
    int col;
    int columns;
    char **col_array;
    char message[20];
    int count[26];
    int max_index;

    // Allocation of memory for base arrays
    col_array = transpose_array(aoc_data_get(data), &columns);

    message[0] = '\0';
    // Count characters in each column by using offset to 'a' as index.
    // Add character at each max position to return string 'message'
    for (col = 0; col < columns; col++) {
        for (size_t j = 0; j < 26; j++) {
            count[j] = 0;
        }
        for (i = 0; i < aoc_data_length(data); i++) {
            count[col_array[col][i] - 'a']++;
        }
        max_index = arr_index(count, max(count, 26), 26);
        message[col] = (char)(max_index + 'a');
    }
    message[columns] = '\0';

    /* Freeing up allocated memory */
    for (col = 0; col < columns; col++) {
        free(col_array[col]);
    }
    free(col_array);

    return strdup(message);
}

void *solve_part_2(AocData_t *data) {
    unsigned int i;
    int col;
    int columns;
    char **col_array;
    char message[20] = "";
    int count[26];
    int min_index;


    // Allocation of memory for base arrays
    col_array = transpose_array(aoc_data_get(data), &columns);

    // Count characters in each column by using offset to 'a' as index.
    // Add character at each min position to return string 'message'
    for (col = 0; col < columns; col++) {
        for (size_t j = 0; j < 26; j++) {
            count[j] = 0;
        }
        for (i = 0; i < aoc_data_length(data); i++) {
            count[col_array[col][i] - 'a']++;
        }
        min_index = arr_index(count, min_non_zero(count, 26), 26);
        message[col+1] = '\0';
        message[col] = (char)(min_index + 'a');
    }

    // Null terminate return string

    /* Freeing up allocated memory */
    for (col = 0; col < columns; col++) {
        free(col_array[col]);
    }
    free(col_array);

    return strdup(message);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new(argv[1], year, day);
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
