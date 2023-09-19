#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <math.h>
#include "aoc_utils.h"
#include "aoc_string.h"

GArray *clean_input(GArray *data) {
    char *line;
    GArray *bitfields;
    size_t i, j, len;

    bitfields = g_array_sized_new(TRUE, FALSE, sizeof(GArray *), data->len);

    for (i = 0; i < data->len; i++) {
        line = g_array_index(data, char *, i);
        len = strlen(line);
        GArray *bitfield = g_array_new(TRUE, FALSE, sizeof(int));
        for (j = 0; j < len; j++) {
            int val = line[j] - '0';
            g_array_append_val(bitfield, val);
        }
        g_array_append_val(bitfields, bitfield);
    }
    return bitfields;

}

int common_value(GArray *data, int position, int method) {
    int sum = 0;
    GArray *bitfield;
    gdouble check;
    size_t i;

    for (i = 0; i < data->len; i++) {
        bitfield = g_array_index(data, GArray *, i);
        sum += g_array_index(bitfield, int, position);
    }
    check = (gdouble) sum / data->len;
    if (method == 1) { // 1 = most, 0 = least
        return check < 0.5;
    } else {
        return check >= 0.5;
    }
}

GArray *reduce(GArray *data, int value, int position) {
    GArray *reduced;
    GArray *item;
    size_t i;

    reduced = g_array_new(TRUE, FALSE, sizeof(GArray *));
    for (i = 0; i < data->len; i++) {
        item = g_array_index(data, GArray *, i);
        if (g_array_index(item, int, position) != value) {
            g_array_append_val(reduced, item);
        }
    }
    return reduced;
}

void print_bitfield(GArray *bitfield) {
    size_t i;
    for (i = 0; i < bitfield->len; i++) {
        int val = g_array_index(bitfield, int, i);
        printf("%d ", val);
    }
    printf("\n");
}

void print_bitfields_all(GArray *bitfields) {
    size_t i;
    for (i = 0; i < bitfields->len; i++) {
        print_bitfield(g_array_index(bitfields, GArray *, i));
    }
}

void *solve_part_1(AocData_t *data) {
    GArray *digits;
    uint32_t gamma_rate, epsilon_rate;
    GArray *bitfield = g_array_index(data->data, GArray *, 0);
    size_t length = bitfield->len;
    digits = g_array_new(FALSE, FALSE, sizeof(int));
    size_t count, i, j;

    for (j = 0; j < length; j++) {
        count = 0;
        for (i = 0; i < data->data->len; i++) {
            bitfield = g_array_index(data->data, GArray *, i);
            count += g_array_index(bitfield, int, j);
        }
        int value = (2 * count / data->data->len >= 1);
        g_array_append_val(digits, value);
    }

    gamma_rate = 0;
    for (i = 0; i < digits->len; i++) {
        gint j = digits->len - 1 - i;
        gamma_rate += g_array_index(digits, int, i) * pow(2, j);
    }

    epsilon_rate = gamma_rate ^ ((int)pow(2, bitfield->len) - 1);
    return strdup_printf("%d", gamma_rate * epsilon_rate);
}


int bitfield_sum(GArray *bitfield) {
    int value = 0;
    size_t i;

    for (i = 0; i < bitfield->len; i++) {
        int j = bitfield->len - 1 - i;
        int val = g_array_index(bitfield, int, i);
        value += val * (int)pow(2, j);
    }

    return value;
}

void *solve_part_2(AocData_t *data) {
    GArray *bitfield;
    GArray *oxygen_generator = NULL;
    GArray *co2_scrubber = NULL;

    bitfield = g_array_index(data->data, GArray *, 0);

    int oxygen_generator_value;
    int co2_scrubber_value;
    int value;
    size_t j;

    size_t digits = bitfield->len;
    for (j = 0; j < digits; j++) {
        if (j == 0) {
            value = common_value(data->data, j, 1);
            oxygen_generator = reduce(data->data, value, j);
            co2_scrubber = reduce(data->data, !value, j);
        } else {
            // Oxy generator:
            if (oxygen_generator->len > 1) {
                value = common_value(oxygen_generator, j, 1);
                oxygen_generator = reduce(oxygen_generator, value, j);
            }
            if (co2_scrubber->len > 1) {
                value = common_value(co2_scrubber, j, 0);
                co2_scrubber = reduce(co2_scrubber, value, j);
            }
        }
    }
    oxygen_generator_value = bitfield_sum(g_array_index(oxygen_generator, GArray *, 0));
    co2_scrubber_value = bitfield_sum(g_array_index(co2_scrubber, GArray *, 0));

    return strdup_printf("%d", oxygen_generator_value * co2_scrubber_value);
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

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

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
