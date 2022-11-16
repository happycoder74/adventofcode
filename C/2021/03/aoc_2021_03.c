#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include <math.h>

GArray *clean_input(GArray *data) {
    gchar *line;
    GArray *bitfields;

    bitfields = g_array_sized_new(TRUE, FALSE, sizeof(GArray *), data->len);

    for (guint i = 0; i < data->len; i++) {
        line = g_array_index(data, gchar *, i);
        int len = strlen(line);
        GArray *bitfield = g_array_new(TRUE, FALSE, sizeof(int));
        for (int j = 0; j < len; j++) {
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

    for (guint i = 0; i < data->len; i++) {
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

    reduced = g_array_new(TRUE, FALSE, sizeof(GArray *));
    for (guint i = 0; i < data->len; i++) {
        item = g_array_index(data, GArray *, i);
        if (g_array_index(item, int, position) != value) {
            g_array_append_val(reduced, item);
        }
    }
    return reduced;
}

void print_bitfield(GArray *bitfield) {
    guint i;
    for (i = 0; i < bitfield->len; i++) {
        int val = g_array_index(bitfield, int, i);
        g_print("%d ", val);
    }
    g_print("\n");
}

void print_bitfields_all(GArray *bitfields) {
    for (guint i = 0; i < bitfields->len; i++) {
        print_bitfield(g_array_index(bitfields, GArray *, i));
    }
}

gpointer solve_part_1(AocData_t *data) {
    GArray *digits;
    gint gamma_rate, epsilon_rate;
    GArray *bitfield = g_array_index(data->data, GArray *, 0);
    gint length = bitfield->len;
    digits = g_array_new(FALSE, FALSE, sizeof(int));
    gint count;

    for (gint j = 0; j < length; j++) {
        count = 0;
        for (gint i = 0; i < (int)data->data->len; i++) {
            bitfield = g_array_index(data->data, GArray *, i);
            count += g_array_index(bitfield, int, j);
        }
        int value = (2 * count / data->data->len >= 1);
        g_array_append_val(digits, value);
    }

    gamma_rate = 0;
    for (gint i = 0; i < (int)digits->len; i++) {
        gint j = digits->len - 1 - i;
        gamma_rate += g_array_index(digits, int, i) * pow(2, j);
    }

    epsilon_rate = gamma_rate ^ ((int)pow(2, bitfield->len) - 1);
    return g_strdup_printf("%d", gamma_rate * epsilon_rate);
}


int bitfield_sum(GArray *bitfield) {
    int value = 0;
    for (guint i = 0; i < bitfield->len; i++) {
        int j = bitfield->len - 1 - i;
        int val = g_array_index(bitfield, int, i);
        value += val * (int)pow(2, j);
    }

    return value;
}

gpointer solve_part_2(AocData_t *data) {
    GArray *bitfield;
    GArray *oxygen_generator = NULL;
    GArray *co2_scrubber = NULL;

    bitfield = g_array_index(data->data, GArray *, 0);

    int oxygen_generator_value;
    int co2_scrubber_value;
    int value;

    guint digits = bitfield->len;
    for (guint j = 0; j < digits; j++) {
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

    return g_strdup_printf("%d", oxygen_generator_value * co2_scrubber_value);
}


gpointer solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2021, 3);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
