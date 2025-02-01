#ifndef AOC_2020_16_H_OYBIAANE
#define AOC_2020_16_H_OYBIAANE

#include <stdint.h>

struct Range {
    uint32_t start;
    uint32_t end;
};

struct Ticket {
    uint32_t tickets[20];
    uint32_t ticket_count;
};

struct Mask {
    uint32_t masks[250];
    uint32_t count;
};

struct Result {
    uint32_t value;
};

struct Class {
    char         name[40];
    struct Range range1;
    struct Range range2;
    struct Mask  mask;
    uint32_t     result;
    uint32_t     position;
};

struct Input {
    struct Class  classes[20];
    uint32_t      class_count;
    struct Ticket nearbys[250];
    uint32_t      nearby_count;
    struct Ticket myticket;
    struct Ticket valid_tickets[250];
    uint32_t      valid_count;
};

struct Position {
    char     name[40];
    uint32_t value;
};

int     count_bits(int n);
int     find_bit(int n);
char   *trim_end(char *str);
int     read_ticket(struct Ticket *ticket, char *line);
uint8_t in_range(uint32_t n, struct Class *class);
int     compare(const void *a, const void *b);
void    check_range(struct Ticket *valid_tickets, uint32_t ticket_count, struct Class *class);
void    compute_masks(struct Input *input);

void print_range(struct Class *class);
void print_mask(struct Class *class);
void print_result(struct Class *class);

int      solve_part_1(void *inp);
uint64_t solve_part_2(void *inp);

#endif /* end of include guard: AOC_2020_16_H_OYBIAANE */
