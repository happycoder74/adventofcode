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

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct GridPoint {
    Position pos;
    unsigned value;
} GridPoint;

Position spiral_step(Position pos) {
    Position rp = pos;

    if ((rp.x > 0) && (abs(rp.x) > abs(rp.y))) {
        rp.y += 1;
    } else if ((rp.x < 0) && ((abs(rp.x) > abs(rp.y)) || (rp.x == -rp.y))) {
        rp.y -= 1;
    } else if ((rp.y > 0) && ((abs(rp.y) > abs(rp.x)) || (rp.x == rp.y))) {
        rp.x -= 1;
    } else {
        rp.x += 1;
    }
    return rp;
}

unsigned grid_value(GridPoint *grid, GridPoint *gp) {
    unsigned       res = 0;
    const Position deltas[9] = {
        {-1, -1},
        {-1, 0 },
        {-1, 1 },
        {0,  -1},
        {0,  0 },
        {0,  1 },
        {1,  -1},
        {1,  0 },
        {1,  1 }
    };

    for (unsigned i = 0; i < 9; i++) {
        Position   compare_pos = {gp->pos.x + deltas[i].x, gp->pos.y + deltas[i].y};
        GridPoint *gp2;
        for (GridPoint *ptr = grid; ptr < gp; ptr++) {
            gp2 = ptr;
            if ((gp2->pos.x == compare_pos.x) && (gp2->pos.y == compare_pos.y)) {
                res += gp2->value;
                break;
            }
        }
    }
    return res;
}

unsigned manhattan(const Position pos) {
    return abs(pos.x) + abs(pos.y);
}

AocArrayPtr clean_input(AocArrayPtr data) {
    return data;
}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr input = aoc_data_get(data);
    unsigned    target = strtoul(aoc_str_array_index(input, 0), NULL, 10);
    Position    pos = {0, 0};

    for (unsigned i = 1; i < target; i++) {
        pos = spiral_step(pos);
    }

    return strdup_printf("%d", manhattan(pos));
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr input = aoc_data_get(data);
    unsigned    target = strtoul(aoc_str_array_index(input, 0), NULL, 10);
    Position    pos = {0, 0};
    GridPoint  *grid = (GridPoint *)calloc(target, sizeof(GridPoint));
    GridPoint  *grid_pointer = grid;
    GridPoint  *gp = grid_pointer++;
    gp->pos = pos;
    gp->value = 1;
    while (1) {
        pos = spiral_step(pos);
        gp = grid_pointer++;
        gp->pos = pos;
        gp->value = grid_value(grid, gp);
        if (gp->value > target) {
            break;
        }
    }

    unsigned result = gp->value;
    free(grid);

    return strdup_printf("%d", result);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2017;
    const unsigned day = 3;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
