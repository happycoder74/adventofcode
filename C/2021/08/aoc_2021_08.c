#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr result;
    size_t      i;
    char      **split_line;

    result = aoc_array_new(AOC_PTR, data->length);
    for (i = 0; i < aoc_array_length(data); i++) {
        split_line = aoc_str_split(aoc_str_array_index(data, i), "|", 0);
        aoc_ptr_array_append(result, split_line);
    }

    // Note we do not free split line here, since the memory is used in the new array.
    aoc_str_array_free(data);
    return result;
}

int signal_sort(const void *a, const void *b) {
    const char *str1 = *((char **)a);
    const char *str2 = *((char **)b);

    return strlen(str1) - strlen(str2);
}

uint32_t count_set_bits(int number) {
    uint32_t number_of_set_bits = 0;
    while (number > 0) {
        number_of_set_bits += 1;
        number = number & (number - 1);
    }
    return number_of_set_bits;
}

static uint32_t string_to_bitfield(char *str) {
    uint32_t field = 0;

    for (char *c = str; *c != '\0'; c++) {
        field = field | (1 << (*c - 'a'));
    }

    return field;
}

uint32_t *decode_signal(char *signal) {
    int         signal_set_key[10] = {0};
    uint32_t   *signal_sets;
    char      **parts;
    uint32_t    set;
    AocArrayPtr signal_parts;

    signal_set_key[1] = 0;
    signal_set_key[7] = 1;
    signal_set_key[4] = 2;
    signal_set_key[8] = 9;

    signal_parts = aoc_str_array_new();
    parts = aoc_str_split(signal, " ", 0);
    size_t j = 0;
    while (parts[j] != NULL) {
        aoc_str_array_append(signal_parts, parts[j]);
        j++;
    }

    signal_sets = (uint32_t *)calloc(signal_parts->length, sizeof(uint32_t));
    aoc_str_array_sort(signal_parts, signal_sort);

    for (j = 0; j < aoc_array_length(signal_parts); j++) {
        char *part = aoc_str_array_index(signal_parts, j);
        set = string_to_bitfield(part);
        signal_sets[j] = set;
    }
    for (size_t i = 0; i < aoc_array_length(signal_parts); i++) {
        set = signal_sets[i];
        if (count_set_bits(set) == 5) {
            if (count_set_bits(set & signal_sets[signal_set_key[1]]) == 2) {
                signal_set_key[3] = i;
            } else if (count_set_bits(set & signal_sets[signal_set_key[4]]) == 2) {
                signal_set_key[2] = i;
            } else {
                signal_set_key[5] = i;
            }
        } else if (count_set_bits(set) == 6) {
            if (count_set_bits(set & (set ^ signal_sets[signal_set_key[4]])) == 2) {
                signal_set_key[9] = i;
            } else if (count_set_bits(set & (set ^ signal_sets[signal_set_key[5]])) == 2) {
                signal_set_key[0] = i;
            } else {
                signal_set_key[6] = i;
            }
        }
    }

    uint32_t *decoded = (uint32_t *)calloc(10, sizeof(uint32_t));
    for (size_t hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = signal_sets[signal_set_key[hkey]];
    }

    free(signal_sets);
    aoc_str_array_free(signal_parts);
    aoc_str_freev(parts);

    return decoded;
}

uint32_t decode(uint32_t *keys, char *signal) {
    uint32_t    int_message = 0;
    AocArrayPtr message;
    char      **parts;
    uint32_t    signal_sets[10];
    uint32_t    signal_set;
    uint32_t    set;

    parts = aoc_str_split(str_trim(signal), " ", 0);
    message = aoc_int32_array_new();

    size_t j = 0;
    while (parts[j] != NULL) {
        set = string_to_bitfield(parts[j]);
        signal_sets[j] = set;
        j++;
    }

    uint32_t multiplier = 1000;
    for (size_t i = 0; i < j; i++) {
        // This is the decoding loop, where the signal is compared to the keys in the
        // decoded list of hash_tables. Again not really sure this is the best way to do this.
        signal_set = signal_sets[i];
        for (size_t j = 0; j < 10; j++) {
            set = keys[j];
            if (set == signal_set) {
                int_message += multiplier * j;
                multiplier /= 10;
                aoc_int32_array_append(message, j);
            }
        }
    }

    aoc_str_freev(parts);

    return int_message;
}

void *solve_part_1(AocData_t *data) {
    char **split_line;
    char **output_value;
    char  *val;
    int    count = 0;

    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_ptr_array_index(aoc_data_get(data), i);
        output_value = aoc_str_split(str_trim(split_line[1]), " ", 0);

        int j = 0;
        while ((val = output_value[j]) != NULL) {
            if ((strlen(val) >= 2 && strlen(val) <= 4) || strlen(val) == 7) {
                count++;
            }
            j++;
        }
        aoc_str_freev(output_value);
    }
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    char    **split_line;
    int       array_sum;
    uint32_t *decoded;
    uint32_t  int_message = 0;
    int       message_sum;

    array_sum = 0;
    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_ptr_array_index(aoc_data_get(data), i);
        decoded = decode_signal(str_trim(split_line[0]));
        int_message = decode(decoded, str_trim(split_line[1]));

        array_sum += int_message;
        free(split_line[0]);
        free(split_line[1]);
        free(decoded);
    }

    return strdup_printf("%d", array_sum);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2021;
    const unsigned day = 8;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
