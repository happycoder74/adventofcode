#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
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

static uint32_t bitfield_diff(uint32_t b1, uint32_t b2) {
    return b1 & (b1 ^ b2);
}

uint32_t *decode_signal(char *signal) {
    int      signal_set_key[10] = {0};
    uint32_t set;

    signal_set_key[1] = 0;
    signal_set_key[7] = 1;
    signal_set_key[4] = 2;
    signal_set_key[8] = 9;

    size_t j = 0;

    uint32_t signal_sets[10] = {0};

    char *pos = NULL;
    char *prev = signal;
    for (j = 0; ((pos = strchr(signal + (size_t)pos, ' ')) != NULL); j++) {
        *pos = '\0';
        pos = pos - (uintptr_t)signal + 1;
        set = string_to_bitfield(prev);
        signal_sets[j] = set;
        switch (strlen(prev)) {
            case 2:
                signal_set_key[1] = j;
                break;
            case 3:
                signal_set_key[7] = j;
                break;
            case 4:
                signal_set_key[4] = j;
                break;
            case 7:
                signal_set_key[8] = j;
                break;
        }
        prev = signal + (size_t)pos;
    }
    set = string_to_bitfield(prev);
    signal_sets[j] = set;
    switch (strlen(prev)) {
        case 2:
            signal_set_key[1] = j;
            break;
        case 3:
            signal_set_key[7] = j;
            break;
        case 4:
            signal_set_key[4] = j;
            break;
        case 7:
            signal_set_key[8] = j;
            break;
    }
    for (size_t i = 0; i < 10; i++) {
        set = signal_sets[i];
        switch (count_set_bits(set)) {
            case 5:
                if (count_set_bits(set & signal_sets[signal_set_key[1]]) == 2) {
                    signal_set_key[3] = i;
                } else if (count_set_bits(set & signal_sets[signal_set_key[4]]) == 2) {
                    signal_set_key[2] = i;
                } else {
                    signal_set_key[5] = i;
                }
                break;
            case 6:
                if (count_set_bits(set & (set ^ signal_sets[signal_set_key[4]])) == 2) {
                    signal_set_key[9] = i;
                } else if (count_set_bits(
                               bitfield_diff(bitfield_diff(signal_sets[signal_set_key[8]], set),
                                             signal_sets[signal_set_key[1]])) == 0) {
                    signal_set_key[6] = i;
                } else {
                    signal_set_key[0] = i;
                }
                break;
        }
    }

    uint32_t *decoded = (uint32_t *)calloc(10, sizeof(uint32_t));
    for (size_t hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = signal_sets[signal_set_key[hkey]];
    }

    return decoded;
}

uint32_t decode(uint32_t *keys, char *signal) {
    uint32_t int_message = 0;
    uint32_t signal_set;
    uint32_t set;
    uint32_t signal_sets[10] = {0};

    size_t j = 0;
    char  *pos = NULL;
    char  *prev = signal;
    while ((pos = strchr(signal + (size_t)pos, ' ')) != NULL) {
        *pos = '\0';
        pos = pos - (uintptr_t)signal + 1;
        set = string_to_bitfield(prev);
        signal_sets[j] = set;
        prev = signal + (size_t)pos;
        j++;
    }
    set = string_to_bitfield(prev);
    signal_sets[j] = set;
    j++;

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
            }
        }
    }

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
