#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_array.h"
#include "aoc_timer.h"

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr return_array = aoc_array_new(sizeof(int));
    char **instructions = aoc_str_split(aoc_str_array_index(data, 0), ",", 0);
    char **p = instructions;
    int opcode;

    while(*p) {
        opcode = atoi(*p);
        aoc_int_array_append(return_array, opcode);
        p++;
    }
    aoc_str_freev(instructions);

    return return_array;
}

int intcode(AocArrayPtr instructions) {
    int i = 0;
    int dest, op, op1, op2;
    while((op = aoc_int_array_index(instructions, i)) != 99) {
        dest = aoc_int_array_index(instructions, i + 3);
        op1 = aoc_int_array_index(instructions, i + 1);
        op2 = aoc_int_array_index(instructions, i + 2);
        switch(op) {
            case 1:
                aoc_int_array_index(instructions, dest) =
                    aoc_int_array_index(instructions, op1) +
                    aoc_int_array_index(instructions, op2);
                i += 4;
                break;
            case 2:
                aoc_int_array_index(instructions, dest) =
                    aoc_int_array_index(instructions, op1) *
                    aoc_int_array_index(instructions, op2);
                i += 4;
                break;
            default:
                return 0;
        }
    }
    return aoc_int_array_index(instructions, 0);

}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr instructions = aoc_array_sized_new(sizeof(int), aoc_data_length(data));
    memcpy(instructions->data, aoc_data_get(data)->data, aoc_data_length(data) * sizeof(int));
    int return_value;

    aoc_int_array_index(instructions, 1) = 12;
    aoc_int_array_index(instructions, 2) = 2;

    return_value = intcode(instructions);
    aoc_array_free(instructions);
    return strdup_printf("%d", return_value);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr instructions = NULL;
    int return_value;

    for (int verb = 0; verb < 100; verb++) {
        for (int noun = 0; noun < 100; noun++) {
            instructions = aoc_array_sized_new(sizeof(int), aoc_data_length(data));
            memcpy(instructions->data, aoc_data_get(data)->data, aoc_data_length(data) * sizeof(int));
            aoc_int_array_index(instructions, 1) = verb;
            aoc_int_array_index(instructions, 2) = noun;

            return_value = intcode(instructions);
            if (return_value == 19690720) {
                aoc_array_free(instructions);
                return strdup_printf("%d", 100*verb + noun);
            }
            aoc_array_free(instructions);
        }
     }

    aoc_array_free(instructions);
    return NULL;
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1); } return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, clean_input);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
