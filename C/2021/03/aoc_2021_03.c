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

int solve_part_1(GArray *data) {
    GArray *digits;
    gint gamma_rate, epsilon_rate;
    GArray *bitfield = g_array_index(data, GArray *, 0);
    gint length = bitfield->len;
    digits = g_array_new(FALSE, FALSE, sizeof(int));
    gint count;

    for (gint j = 0; j < length; j++) {
        count = 0;
        for (gint i = 0; i < (int)data->len; i++) {
            bitfield = g_array_index(data, GArray *, i);
            count += g_array_index(bitfield, int, j);
        }
        int value = (2 * count / data->len >= 1);
        g_array_append_val(digits, value);
    }

    gamma_rate = 0;
    for (gint i = 0; i < (int)digits->len; i++) {
        gint j = digits->len - 1 - i;
        gamma_rate += g_array_index(digits, int, i) * pow(2, j);
    }

    epsilon_rate = gamma_rate ^ ((int)pow(2, bitfield->len) - 1); 
    return gamma_rate * epsilon_rate;
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

int solve_part_2(GArray *data) {
    GArray *bitfield;
    GArray *oxygen_generator;
    GArray *co2_scrubber;

    bitfield = g_array_index(data, GArray *, 0);

    int oxygen_generator_value;
    int co2_scrubber_value;
    int value;

    guint digits = bitfield->len;
    for (guint j = 0; j < digits; j++) {
        if (j == 0) {
            value = common_value(data, j, 1);
            oxygen_generator = reduce(data, value, j);
            co2_scrubber = reduce(data, !value, j);
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

    return oxygen_generator_value * co2_scrubber_value;
}


int solve_all(gchar *filename, int year, int day) {
    GArray *data;
    gdouble elapsed;
    gchar *unit;

    GTimer *timer = g_timer_new();
    data = clean_input(get_input(filename, year, day));
    g_timer_stop(timer);

    elapsed = g_timer_elapsed(timer, NULL);
    unit = elapsed > 0.1 ? g_strdup("s") : g_strdup("ms");
    elapsed = elapsed > 0.1 ? elapsed : elapsed * 1000;

    g_timer_destroy(timer);

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

        g_print("Input time:\r\033[35C( %6.3lf %s )\n", elapsed, unit);
        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2021, 3), INT, 0);
    g_free(filename);
}
