#include "aoc_2020_17.h"
#include "aoc_hash.h"
#include "aoc_hash_light.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_key_value(void *key, void *value, void *data) {
    printf("Key: %s\n", (char *)key);
    return;
}

void copy_func(void *key, void *value, void *data) {
    AocHashTable *clone = (AocHashTable *)data;
    aoc_hash_table_add(clone, key);
    return;
}
int main(int argc, char *argv[]) {
    char *data_directory = getenv("AOC_DATA_LOCATION");

    char      filepath[255] = {0};
    const int year = 2020;
    const int day = 17;

    struct Input  input = {0};
    AocHashTable *clone = NULL;

    char filename[40] = "input.txt";
    if (argc > 1) {
        if (!strcmp(argv[1], "--test")) {
            snprintf(filename, sizeof(filename) - 1, "test_input.txt");
        } else {
            snprintf(filename, sizeof(filename) - 1, "%s", argv[1]);
        }
    }
    snprintf(filepath, sizeof(filepath), "%s/%d/%02d/%s", data_directory, year, day, filename);

    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Failed to open file: %s\n", filepath);
        return 1;
    }

    char  line[255] = {0};
    char *str = NULL;
    int   r = 0;
    input.w_min = 0;
    input.w_max = 0;
    input.z_min = 0;
    input.z_max = 0;
    input.x_min = 0;
    input.y_min = 0;
    input.x_max = 0;
    input.y_max = 0;
    input.grid = aoc_hash_table_create(AOC_PTR);
    while (fgets(line, sizeof(line), file)) {
        str = trim_end(line);
        if (input.x_max == 0) {
            input.x_max = strlen(str) - 1;
            input.y_max = input.x_max;
        }
        for (int c = 0; c < (int)strlen(str); c++) {
            if (str[c] == '#') {
                unsigned int key = get_key(c, r, 0, 0, &input);
                aoc_hash_table_add(input.grid, (void *)(uint64_t)key);
            }
        }
        r++;
    }

    fclose(file);

    clone = aoc_hash_table_new_similar(input.grid);
    aoc_hash_table_foreach(input.grid, copy_func, clone);
    timer_func_new(1, solve_part_1, &input, 1);
    aoc_hash_table_destroy(&input.grid);
    input.grid = aoc_hash_table_new_similar(clone);
    aoc_hash_table_foreach(clone, copy_func, input.grid);
    timer_func_new(2, solve_part_2, &input, 1);

    aoc_hash_table_destroy(&clone);
    aoc_hash_table_destroy(&input.grid);
    return 0;
}
