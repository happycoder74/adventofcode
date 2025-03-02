#include "aoc_2020_17.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_key(int x, int y, int z, int w, struct Input *input) {
    int x_min = input->x_min - 7;
    int x_max = input->x_max + 7;
    int y_min = input->y_min - 7;
    int y_max = input->y_max + 7;
    int z_min = input->z_min - 7;
    int z_max = input->z_max + 7;
    int w_min = input->w_min - 7;

    return x - x_min +
           (x_max - x_min + 1) *
               (y - y_min + (y_max - y_min + 1) * (z - z_min + (z_max - z_min + 1) * (w - w_min)));
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

int count_active_neighbors(struct Input *input, int x, int y, int z, int w, uint8_t is_part_2) {
    int active = 0;
    int dw_start = 0;
    int dw_end = 0;
    if (is_part_2) {
        dw_start = -1;
        dw_end = 1;
    }
    for (int dw = dw_start; dw <= dw_end; dw++) {
        for (int dz = -1; dz <= 1; dz++) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) {
                        continue;
                    }
                    unsigned int key = get_key(x + dx, y + dy, z + dz, w + dw, input);
                    if (input->grid[key] == 1) {
                        active++;
                    }
                }
            }
        }
    }
    return active;
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint8_t      *grid = input->grid;
    int           x_max = input->x_max;
    int           y_max = input->y_max;
    int           x_min = input->x_min;
    int           y_min = input->y_min;
    int           z_min = 0;
    int           z_max = 0;

    for (int cycle = 1; cycle <= 6; cycle++) {
        uint32_t activate[100000] = {0};
        uint32_t deactivate[100000] = {0};
        size_t   activate_count = 0;
        size_t   deactivate_count = 0;

        // x_max += 1;
        // y_max += 1;
        // z_max += 1;
        // x_min -= 1;
        // y_min -= 1;
        // z_min -= 1;
        int w = 0;
        for (int z = z_min - cycle; z <= z_max + cycle; z++) {
            for (int y = y_min - cycle; y <= y_max + cycle; y++) {
                for (int x = x_min - cycle; x <= x_max + cycle; x++) {
                    unsigned int key = get_key(x, y, z, 0, input);
                    int          active = count_active_neighbors(input, x, y, z, w, 0);
                    if ((grid[key] == 1) && ((active < 2) || (active > 3))) {
                        deactivate[deactivate_count++] = key;
                    } else if (active == 3) {
                        activate[activate_count++] = key;
                    }
                }
            }
        }

        for (size_t i = 0; i < activate_count; i++) {
            grid[activate[i]] = 1;
        }
        for (size_t i = 0; i < deactivate_count; i++) {
            grid[deactivate[i]] = 0;
        }
    }
    int result = 0;
    for (size_t i = 0; i < 110000; i++) {
        result += grid[i];
    }
    return result;
}

int solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    uint8_t      *grid = input->grid;
    int           x_max = input->x_max;
    int           y_max = input->y_max;
    int           x_min = input->x_min;
    int           y_min = input->y_min;
    int           z_min = 0;
    int           z_max = 0;
    int           w_min = 0;
    int           w_max = 0;

    uint32_t activate[100000] = {0};
    uint32_t deactivate[100000] = {0};
    for (int cycle = 0; cycle < 6; cycle++) {
        size_t activate_count = 0;
        size_t deactivate_count = 0;
        x_max += 1;
        y_max += 1;
        z_max += 1;
        w_max += 1;
        x_min -= 1;
        y_min -= 1;
        z_min -= 1;
        w_min -= 1;
        for (int w = w_min; w <= w_max; w++) {
            for (int z = z_min; z <= z_max; z++) {
                for (int y = y_min; y <= y_max; y++) {
                    for (int x = x_min; x <= x_max; x++) {
                        unsigned int key = get_key(x, y, z, w, input);
                        int          active = count_active_neighbors(input, x, y, z, w, 1);
                        if ((grid[key] == 1) && ((active < 2) || (active > 3))) {
                            deactivate[deactivate_count++] = key;
                        } else if (active == 3) {
                            activate[activate_count++] = key;
                        }
                    }
                }
            }
        }

        for (size_t i = 0; i < activate_count; i++) {
            grid[activate[i]] = 1;
        }
        for (size_t i = 0; i < deactivate_count; i++) {
            grid[deactivate[i]] = 0;
        }
        memset(activate, 0, 100000 * sizeof(uint32_t));
        memset(deactivate, 0, 100000 * sizeof(uint32_t));
    }
    int result = 0;
    for (size_t i = 0; i < 110000; i++) {
        result += grid[i];
    }
    return result;
}
