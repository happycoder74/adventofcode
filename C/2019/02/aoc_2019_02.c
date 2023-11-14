#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include "intcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr return_array = aoc_int32_array_new();
    char      **instructions = aoc_str_split(aoc_str_array_index(data, 0), ",", 0);
    int         opcode;

    char **p = instructions;

    while (*p != NULL) {
        opcode = atoi(*p);
        aoc_int32_array_append(return_array, opcode);
        p++;
    }
    aoc_str_freev(instructions);

    return return_array;
}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr      instructions = aoc_array_copy(aoc_data_get(data));
    IntCodeReturn_t *return_value;

    aoc_int32_array_set_index(instructions, 1, 12);
    aoc_int32_array_set_index(instructions, 2, 2);

    return_value = intcode(instructions, NULL);
    aoc_int32_array_free(instructions);
    return strdup_printf("%d", return_value->return_value);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr      instructions = NULL;
    IntCodeReturn_t *return_value;

    for (int verb = 0; verb < 100; verb++) {
        for (int noun = 0; noun < 100; noun++) {
            instructions = aoc_array_copy(aoc_data_get(data));
            aoc_int32_array_set_index(instructions, 1, verb);
            aoc_int32_array_set_index(instructions, 2, noun);

            return_value = intcode(instructions, NULL);
            if (return_value->return_value == 19690720) {
                aoc_int32_array_free(instructions);
                return strdup_printf("%d", 100 * verb + noun);
            }
            aoc_int32_array_free(instructions);
        }
    }

    aoc_int32_array_free(instructions);
    return NULL;
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
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

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

    return aoc_mem_gc();
}
