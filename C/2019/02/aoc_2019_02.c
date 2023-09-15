#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "glibconfig.h"

GArray *clean_input(GArray *data) {
    GArray *return_array = g_array_new(FALSE, TRUE, sizeof(int));
    gchar **instructions = g_strsplit(g_array_index(data, char *, 0), ",", 0);
    gchar **p = instructions;
    gint opcode;

    while(*p) {
        opcode = atoi(*p);
        g_array_append_val(return_array, opcode);
        p++;
    }
    g_strfreev(instructions);

    return return_array;
}

int intcode(GArray *instructions) {
    gint i = 0;
    int dest, op, op1, op2;
    while((op = g_array_index(instructions, int, i)) != 99) {
        dest = g_array_index(instructions, int, i + 3);
        op1 = g_array_index(instructions, int, i + 1);
        op2 = g_array_index(instructions, int, i + 2);
        switch(op) {
            case 1:
                g_array_index(instructions, int, dest) = 
                    g_array_index(instructions, int, op1) +
                    g_array_index(instructions, int, op2);
                i += 4;
                break;
            case 2:
                g_array_index(instructions, int, dest) = 
                    g_array_index(instructions, int, op1) *
                    g_array_index(instructions, int, op2);
                i += 4;
                break;
            default:
                return 0;
        }
    }
    return g_array_index(instructions, int, 0);

}

void *solve_part_1(AocData_t *data) {
    GArray *instructions = g_array_copy(data->data);
    int return_value;

    g_array_index(instructions, int, 1) = 12;
    g_array_index(instructions, int, 2) = 2;

    return_value = intcode(instructions);
    g_array_free(instructions, TRUE);
    return g_strdup_printf("%d", return_value);
}

void *solve_part_2(AocData_t *data) {
    GArray *instructions = NULL;
    int return_value;

    for (int verb = 0; verb < 100; verb++) {
        for (int noun = 0; noun < 100; noun++) {
            instructions = g_array_copy(data->data);
            g_array_index(instructions, int, 1) = verb;
            g_array_index(instructions, int, 2) = noun;
            
            return_value = intcode(instructions);
            if (return_value == 19690720) {
                g_array_free(instructions, TRUE);
                return g_strdup_printf("%d", 100*verb + noun);
            }
        }
     }

    g_array_free(instructions, TRUE);
    return NULL;
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    const int year = 2019;
    const int day = 2;
    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
