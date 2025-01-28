#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr cards = aoc_str_array_new();
    for (unsigned i = 0; i < data->length; i++) {
        char *str = aoc_str_array_index(data, i);
        char *ptr = strchr(str, ':');
        aoc_str_array_append(cards, ptr + 1);
    }

    aoc_str_array_free(data);
    return cards;
}

unsigned int solver(AocData_t *data) {
    AocArrayPtr cards = aoc_data_get(data);
    AocArrayPtr winning_numbers = NULL;
    AocArrayPtr numbers = NULL;

    unsigned  number_of_cards = 0;
    unsigned *cards_array = (unsigned *)calloc(cards->length, sizeof(unsigned));

    unsigned points = 0;

    char card[201];
    for (unsigned index = 0; index < cards->length; index++) {
        if (!winning_numbers) {
            winning_numbers = aoc_uint32_array_new();
        }
        if (!numbers) {
            numbers = aoc_uint32_array_new();
        }
        strncpy(card, aoc_str_array_index(cards, index), 200);
        cards_array[index] += 1;

        char    *winners = strtok(card, "|");
        char    *my_numbers = strtok(NULL, "|");
        uint32_t number = 0;
        uint32_t card_points = 0;

        char *num = strtok(winners, " ");
        while (num) {
            number = atoi(num);
            aoc_uint32_array_append(winning_numbers, number);
            num = strtok(NULL, " ");
        }

        num = strtok(my_numbers, " ");
        while (num) {
            number = atoi(num);
            aoc_uint32_array_append(numbers, number);
            num = strtok(NULL, " ");
        }

        unsigned add_card_index = 1;
        for (unsigned w = 0; w < winning_numbers->length; w++) {
            uint32_t wn = aoc_uint32_array_index(winning_numbers, w);
            for (unsigned n = 0; n < numbers->length; n++) {
                if (wn == aoc_uint32_array_index(numbers, n)) {
                    if (!card_points) {
                        card_points = 1;
                    } else {
                        card_points *= 2;
                    }
                    cards_array[index + add_card_index++] += cards_array[index];
                    break;
                }
            }
        }
        points += card_points;
        number_of_cards += cards_array[index];
        numbers->length = 0;
        winning_numbers->length = 0;
    }
    aoc_uint32_array_free(numbers);
    aoc_uint32_array_free(winning_numbers);

    data->user_data = (unsigned *)malloc(sizeof(unsigned));
    memcpy(data->user_data, &number_of_cards, sizeof number_of_cards);

    return points;
}

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%d", solver(data));
}

void *solve_part_2(AocData_t *data) {
    unsigned number_of_cards = *(unsigned *)data->user_data;
    free(data->user_data);
    data->user_data = NULL;
    return strdup_printf("%d", number_of_cards);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2023;
    const unsigned day = 4;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
