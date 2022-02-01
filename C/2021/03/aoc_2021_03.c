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


int solve_part_2(GArray *data) {
    guint i;
    GArray *bitfield;
    gint count;
    GArray *oxygen_generator;
    GArray *co2_scrubber;
    GArray *to_remove;

    oxygen_generator = g_array_new(TRUE, TRUE, sizeof(GArray *));
    co2_scrubber = g_array_new(TRUE, TRUE, sizeof(GArray *));
    bitfield = g_array_index(data, GArray *, 0);

    int oxygen_generator_value;
    int co2_scrubber_value;
    int value, c;

    guint digits = bitfield->len;
    for (guint j = 0; j < digits; j++) {
        if (j == 0) {
            count = 0;
            for (i = 0; i < data->len; i++) {
                bitfield = g_array_index(data, GArray *, i);
                count += g_array_index(bitfield, int, j);
            }
            for (i = 0; i < data->len; i++) {
                bitfield = g_array_index(data, GArray *, i);
                if (2.0 * count / (data->len) >= 1) {
                    if (g_array_index(bitfield, int, j) == 1) {
                        g_array_append_val(oxygen_generator, bitfield);
                    } else {
                        g_array_append_val(co2_scrubber, bitfield);
                    }
                } else {
                    if (g_array_index(bitfield, int, j) == 0) {
                        g_array_append_val(oxygen_generator, bitfield);
                    } else {
                        g_array_append_val(co2_scrubber, bitfield);
                    }
                }
            }
        } else {
            to_remove = g_array_new(FALSE, FALSE, sizeof(guint));
            count = 0;
            for (i = 0; i < oxygen_generator->len; i++) {
                bitfield = g_array_index(oxygen_generator, GArray *, i);
                count += g_array_index(bitfield, int, j);
            }
            for (i = 0; i < oxygen_generator->len && oxygen_generator->len > 1; i++) {
                bitfield = g_array_index(oxygen_generator, GArray *, i);
                value = g_array_index(bitfield, int, j);
                if (2.0 * count / oxygen_generator->len >=1) {
                    if (value == 0) {
                        g_array_append_val(to_remove, i);
                    }
                } else {
                    if (value == 1) {
                        g_array_append_val(to_remove, i);
                    }
                }
            }

            for (c = to_remove->len - 1; c >= 0; c--) {
                oxygen_generator = g_array_remove_index(
                        oxygen_generator,
                        g_array_index(to_remove, int, c)
                        );
            }
            g_array_free(to_remove, TRUE);

            to_remove = g_array_new(FALSE, FALSE, sizeof(int));
            count = 0;
            for (i = 0; i < co2_scrubber->len; i++) {
                bitfield = g_array_index(co2_scrubber, GArray *, i);
                count += g_array_index(bitfield, int, j);
            }
            for (i = 0; i < co2_scrubber->len && co2_scrubber->len > 1; i++) {
                bitfield = g_array_index(co2_scrubber, GArray *, i);
                if (2.0 * count / co2_scrubber->len >=1) {
                    if (g_array_index(bitfield, int, j) == 1) {
                        g_array_append_val(to_remove, i);
                    }
                } else {
                    if (g_array_index(bitfield, int, j) == 0) {
                        g_array_append_val(to_remove, i);
                    }
                }
            }

            for (c = to_remove->len - 1; c >= 0; c--) {
                value = g_array_index(to_remove, int, c);
                co2_scrubber = g_array_remove_index(
                        co2_scrubber, value
                        );
            }
            g_array_free(to_remove, TRUE);
        }
    }

    oxygen_generator_value = 0;
    bitfield = g_array_index(oxygen_generator, GArray *, 0);
    for (i = 0; i < bitfield->len; i++) {
        int j = bitfield->len - 1 - i;
        int val = g_array_index(bitfield, int, i);
        oxygen_generator_value += val * (int)pow(2, j);
    }

    co2_scrubber_value = 0;
    bitfield = g_array_index(co2_scrubber, GArray *, 0);
    for (i = 0; i < bitfield->len; i++) {
        int j = bitfield->len - 1 - i;
        int val = g_array_index(bitfield, int, i);
        co2_scrubber_value += val * (int)pow(2, j);
    }

    g_array_free(oxygen_generator, TRUE);
    g_array_free(co2_scrubber, TRUE);

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
