#include "aoc_2020_16.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_bits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int find_bit(int n) {
    for (uint32_t i = 0; i < 20; i++) {
        if (((n >> i) & 1) == 1) {
            return i;
        }
    }
    return -1;
}

char *trim_end(char *str) {
    if (str == NULL) {
        return NULL;
    }

    char *end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';
    return str;
}

int read_ticket(struct Ticket *ticket, char *line) {
    int   number_of_tokens = 0;
    char *token = strtok(line, ",");
    while (token != NULL) {
        ticket->tickets[ticket->ticket_count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    return number_of_tokens;
}

uint8_t in_range(uint32_t n, struct Class *class) {
    uint8_t v1 = ((class->range1.start <= n) && (n <= class->range1.end));
    uint8_t v2 = ((class->range2.start <= n) && (n <= class->range2.end));
    return v1 || v2;
}

uint8_t check_number_in_range(struct Input *input, uint32_t ticket) {
    struct Class *class = NULL;

    for (size_t r = 0; r < input->class_count; r++) {
        class = input->classes + r;
        if (in_range(ticket, class))
            return 1;
    }
    return 0;
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint32_t      invalid = 0;

    struct Ticket *nearby = NULL;
    for (size_t i = 0; i < input->nearby_count; i++) {
        nearby = input->nearbys + i;
        uint8_t ticket_is_valid = 1;
        for (size_t n = 0; n < nearby->ticket_count; n++) {
            if (!check_number_in_range(input, nearby->tickets[n])) {
                invalid += nearby->tickets[n];

                ticket_is_valid = 0;
                break;
            }
        }
        if (ticket_is_valid) {
            struct Ticket *valid = input->valid_tickets + input->valid_count;
            memmove(valid, nearby, 1 * sizeof(struct Ticket));
            input->valid_count++;
        }
    }
    return invalid;
}

void check_range(struct Ticket *valid_tickets, uint32_t ticket_count, struct Class *class) {
    for (size_t i = 0; i < ticket_count; i++) {
        uint32_t val = 0;
        for (size_t j = 0; j < valid_tickets[i].ticket_count; j++) {
            if (in_range(valid_tickets[i].tickets[j], class)) {
                uint32_t pos = valid_tickets[i].ticket_count - 1 - j;
                val = val | (1 << pos);
            }
        }
        class->mask.masks[i] = val;
        class->mask.count += 1;
    }

    return;
}

void compute_masks(struct Input *input) {
    struct Class *class = input->classes;

    for (size_t i = 0; i < input->class_count; i++) {
        check_range(input->valid_tickets, input->valid_count, class + i);
    }

    return;
}

int compare(const void *a, const void *b) {
    struct Class *ra = (struct Class *)a;
    struct Class *rb = (struct Class *)b;

    return ra->result - rb->result;
}

uint64_t solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;

    compute_masks(input);

    for (uint32_t imask = 0; imask < input->class_count; imask++) {
        struct Class *class = input->classes + imask;
        uint32_t value = class->mask.masks[0];
        for (uint32_t j = 1; j < class->mask.count; j++) {
            value &= class->mask.masks[j];
        }
        class->result = value;
    }

    qsort(input->classes, input->class_count, sizeof(struct Class), compare);

    for (uint32_t iresult = 0; iresult < input->class_count; iresult++) {
        uint32_t res = input->classes[iresult].result;
        if (count_bits(res) == 1) {
            uint8_t bit_index = find_bit(res);
            input->classes[iresult].position = input->class_count - 1 - bit_index;
            for (size_t i = iresult + 1; i < input->class_count; i++) {
                input->classes[i].result &= ~(res);
            }
        }
    }

    uint64_t product = 1;

    for (uint32_t ipos = 0; ipos < input->class_count; ipos++) {
        if (!strncmp(input->classes[ipos].name, "departure", 9)) {
            product *= input->myticket.tickets[input->classes[ipos].position];
        }
    }

    return product;
}
