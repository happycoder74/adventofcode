#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char   **grid;
    unsigned max_x;
    unsigned max_y;
    unsigned num_parts;
    unsigned next_col;
} Schematic_t;

static void neighbours(Schematic_t *schema, unsigned y, unsigned x, char *nbs, unsigned *length) {
    unsigned nb_index = 0;
    for (short j = -1; j <= 1; j++) {
        for (short i = -1; i <= 1; i++) {
            if ((((int)y + j) >= 0) && ((y + j) < schema->max_y) && (0 <= ((int)x + i)) && ((x + i) < schema->max_x)) {
                if (!((i == 0) && (j == 0))) {
                    nbs[nb_index++] = schema->grid[y + j][x + i];
                }
            }
        }
    }
    *length = nb_index;

    return;
}

static bool near_symbol(Schematic_t *schema, unsigned y, unsigned x) {
    char     nbs[9] = {0};
    unsigned length;
    neighbours(schema, y, x, nbs, &length);
    for (unsigned index = 0; index < length; index++) {
        if (!isdigit(nbs[index]) && (nbs[index] != '.')) {
            return true;
        }
    }
    return false;
}

static unsigned find_parts(Schematic_t *schema) {
    unsigned num_parts = 0;
    for (unsigned j = 0; j < schema->max_y; j++) {
        int  num_start = -1;
        bool keep = false;
        for (unsigned i = 0; i <= schema->max_x; i++) {
            char point = schema->grid[j][i];
            if (isdigit(point)) {
                if (num_start == -1) {
                    num_start = (int)i;
                }
                if (keep || near_symbol(schema, j, i)) {
                    keep = true;
                }
            } else {
                if ((num_start != -1) && keep) {
                    char     buf[100];
                    unsigned k;
                    for (k = 0; k <= (i - num_start); k++) {
                        buf[k] = schema->grid[j][k + num_start];
                    }
                    buf[k] = '\0';
                    num_parts += atoi(buf);
                }
                num_start = -1;
                keep = false;
            }
        }
    }
    return num_parts;
}

static Schematic_t *init_schematic(AocArrayPtr data) {
    Schematic_t *schema = (Schematic_t *)malloc(sizeof(Schematic_t));
    schema->max_y = data->length;
    schema->grid = (char **)calloc(schema->max_y, sizeof(char *));
    for (unsigned ind = 0; ind < schema->max_y; ind++) {
        schema->grid[ind] = strdup(aoc_str_array_index(data, ind));
    }
    schema->max_x = strlen(schema->grid[0]);
    schema->next_col = UINT_MAX;

    return schema;
}

static unsigned find_number(Schematic_t *schema, unsigned row, unsigned col) {
    int start = (int)col;
    int end = (int)col;
    if (!isdigit(schema->grid[row][col])) {
        return 0;
    }
    // Look left
    while (start >= 0) {
        if (isdigit(schema->grid[row][start])) {
            start--;
        } else {
            break;
        }
    }

    // Look right
    while (isdigit(schema->grid[row][end])) {
        end++;
    }

    char buf[10] = {0};
    int  k;
    for (k = start + 1; k <= end - 1; k++) {
        buf[k - (start + 1)] = schema->grid[row][k];
    }
    buf[k - (start + 1)] = '\0';

    schema->next_col = end;
    return atoi(buf);
}

static unsigned find_gears(Schematic_t *schema) {
    unsigned    gear_ratio = 0;
    AocArrayPtr gears = aoc_ptr_array_new();

    for (unsigned j = 0; j < schema->max_y; j++) {
        for (unsigned i = 0; i < schema->max_x; i++) {
            if (schema->grid[j][i] == '*') {
                Point *p = point_new_m((int)i, (int)j);
                aoc_ptr_array_append(gears, p);
            }
        }
    }

    for (unsigned index = 0; index < gears->length; index++) {
        Point   *p = (Point *)aoc_ptr_array_index(gears, index);
        unsigned i = (unsigned)p->x;
        unsigned j = (unsigned)p->y;

        unsigned       numbers[9] = {0};
        unsigned short n_numbers = 0;

        for (unsigned row = j - 1; row <= j + 1; row++) {
            for (unsigned col = i - 1; col <= i + 1; col++) {
                if ((0 <= (int)row) && (row < schema->max_y) && (0 <= (int)col) && (col < schema->max_x)) {
                    if (isdigit(schema->grid[row][col])) {
                        numbers[n_numbers++] = find_number(schema, row, col);
                        if (schema->next_col != UINT_MAX) {
                            col = schema->next_col;
                            schema->next_col = UINT_MAX;
                        }
                    }
                }
            }
        }
        if (n_numbers > 1) {
            gear_ratio += numbers[0] * numbers[1];
        }
    }

    aoc_ptr_array_free(gears);

    return gear_ratio;
}

static void cleanup(Schematic_t *schema) {
    for (unsigned row = 0; row < schema->max_y; row++) {
        free(schema->grid[row]);
    }
    free(schema->grid);
}

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr  input = aoc_ptr_array_new();
    Schematic_t *schema = init_schematic(data);
    aoc_ptr_array_append(input, schema);
    aoc_str_array_free(data);
    return input;
}

void *solve_part_1(AocData_t *data) {
    Schematic_t *schema = aoc_ptr_array_index(aoc_data_get(data), 0);
    return strdup_printf("%d", find_parts(schema));
}

void *solve_part_2(AocData_t *data) {
    Schematic_t *schema = aoc_ptr_array_index(aoc_data_get(data), 0);
    unsigned     n_gears = find_gears(schema);
    cleanup(schema);
    return strdup_printf("%d", n_gears);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int  year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new_clean("test_input.txt", year, day, clean_input);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, clean_input);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
