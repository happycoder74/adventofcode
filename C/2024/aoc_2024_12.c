#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include "aoc_header.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Position {
    unsigned int x;
    unsigned int y;
};

struct Region {
    char            plant;
    unsigned int    npositions;
    struct Position positions[140 * 140];
};

struct Garden {
    unsigned int    rows;
    unsigned int    columns;
    unsigned int    nregions;
    char            map[140 * 140];
    struct Position map_positions[140 * 140];
    struct Position positions[140 * 140];
    struct Region   regions[140 * 140];
};

void initialize_garden(struct Garden **garden, const char map[140 * 140], unsigned int rows,
                       unsigned int columns) {
    if (*garden == NULL) {
        *garden = (struct Garden *)malloc(sizeof(struct Garden));
    }

    struct Garden *g = *garden;
    g->rows = rows;
    g->columns = columns;
    g->nregions = 0;
    memcpy(g->map, map, rows * columns * sizeof(char));
    unsigned int position_counter = 0;
    for (unsigned int row = 0; row < g->rows; row++) {
        for (unsigned int column = 0; column < g->columns; column++) {
            struct Position position = {row, column};
            g->positions[position_counter++] = position;
            g->map_positions[position.x + position.y * g->columns] = position;
        }
    }
}

unsigned short int in_positions(struct Position **position, struct Position *element) {
    struct Position **p = position;
    while (*p != NULL) {
        if ((element->x == (*p)->x) && (element->y == (*p)->y)) {
            return 1;
        }
        p++;
    }
    return 0;
}

unsigned int region_area(struct Region *region) {
    return region->npositions;
}

unsigned int region_perimeter(struct Region *region) {
    unsigned int result = 0;
    int          dx[4] = {0, 0, -1, 1};
    int          dy[4] = {-1, 1, 0, 0};
    for (unsigned index = 0; index < region->npositions; index++) {
        struct Position *p = &region->positions[index];
        for (unsigned int id = 0; id < 4; id++) {
            short int inside = 0;
            for (unsigned int ipos = 0; ipos < region->npositions; ipos++) {
                struct Position *pp = &region->positions[ipos];
                inside = inside ||
                         (((int)p->x + dx[id] == (int)pp->x) && ((int)p->y + dy[id] == (int)pp->y));
            }
            if (!inside) {
                result++;
            }
        }
    }
    return result;
}

void remove_visited2(struct Position **garden_pos, unsigned int *garden_pos_length,
                     struct Position **visited, unsigned int nvisited) {
    for (unsigned int visited_index = 0; visited_index < nvisited; visited_index++) {
        struct Position *p = visited[visited_index];
        unsigned int     index = 0;
        while (!((garden_pos[index]->x == p->x) && (garden_pos[index]->y == p->y))) {
            index++;
        }
        memmove(garden_pos + (index - 1), garden_pos + index,
                (*garden_pos_length - 1 - index) * sizeof(struct Position *));
        garden_pos[*garden_pos_length] = NULL;
        *garden_pos_length -= 1;
    }
}

void remove_visited(struct Garden *garden, struct Position **garden_pos,
                    unsigned int *garden_pos_length, struct Position **visited) {
    for (unsigned int row = 0; row < garden->rows; row++) {
        for (unsigned int column = 0; column < garden->columns; column++) {
            unsigned int index = column + row * garden->columns;
            if (visited[index] != NULL) {
                garden_pos[index] = NULL;
                *garden_pos_length -= 1;
            }
        }
    }
}

void garden_regions(struct Garden *garden) {
    struct Position *garden_pos[140 * 140] = {0};
    unsigned int     garden_pos_length = garden->rows * garden->columns;
    for (unsigned int i = 0; i < garden_pos_length; i++) {
        garden_pos[i] = &garden->map_positions[i];
    }

    while (garden_pos_length != 0) {
        struct Position *visited[140 * 140] = {0};
        struct Position *pos = NULL;
        unsigned int     index = 0;
        while (pos == NULL) {
            pos = garden_pos[index++];
        }
        char             plant = garden->map[pos->x + pos->y * garden->columns];
        unsigned int     nsearch = 0;
        struct Position *search[140 * 140] = {0};
        search[0] = pos;
        nsearch++;
        while (nsearch > 0) {
            struct Position *p = search[nsearch - 1];
            nsearch--;
            if ((visited[p->x + p->y * garden->columns] != NULL) ||
                garden->map[p->x + p->y * garden->columns] != plant) {
                continue;
            }
            visited[p->x + p->y * garden->columns] = p;

            if (((p->x + 1) < garden->columns)) {
                struct Position *nb = &garden->map_positions[p->x + 1 + p->y * garden->columns];
                if (!in_positions(search, nb)) {
                    search[nsearch++] = nb;
                }
            }
            if ((((int)p->x - 1) >= 0)) {
                struct Position *nb = &garden->map_positions[p->x - 1 + p->y * garden->columns];
                if (!in_positions(search, nb)) {
                    search[nsearch++] = nb;
                }
            }
            if (((p->y + 1) < garden->rows)) {
                struct Position *nb = &garden->map_positions[p->x + (p->y + 1) * garden->columns];
                if (!in_positions(search, nb)) {
                    search[nsearch++] = nb;
                }
            }
            if ((((int)p->y - 1) >= 0)) {
                struct Position *nb = &garden->map_positions[p->x + (p->y - 1) * garden->columns];
                if (!in_positions(search, nb)) {
                    search[nsearch++] = nb;
                }
            }
        }
        struct Region *region = &garden->regions[garden->nregions];
        region->plant = plant;
        region->npositions = 0;
        index = 0;
        for (unsigned int row = 0; row < garden->rows; row++) {
            for (unsigned int column = 0; column < garden->columns; column++) {
                if (visited[column + row * garden->columns] != NULL) {
                    region->positions[index].x = visited[column + row * garden->columns]->x;
                    region->positions[index].y = visited[column + row * garden->columns]->y;
                    region->npositions += 1;
                    index++;
                }
            }
        }
        garden->nregions++;

        remove_visited(garden, garden_pos, &garden_pos_length, visited);
    }
}

int solve_part_1(void *input) {
    struct Garden *garden = (struct Garden *)input;
    unsigned int   result = 0;
    garden_regions(garden);
    for (unsigned int iregion = 0; iregion < garden->nregions; iregion++) {
        result += region_area(&(garden->regions[iregion])) *
                  region_perimeter(&(garden->regions[iregion]));
    }

    return result;
}

int main(int argc, char **argv) {
    FILE     *fp = NULL;
    char      filepath[255];
    char      filename[40] = "input.txt";
    char      map[140 * 140];
    const int year = 2024;
    const int day = 12;

    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if (argc > 1) {
        if (!strcmp("--test", argv[1])) {
            snprintf(filename, 39, "test_input.txt");
        }
    }
    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file (%s)\n", filepath);
        exit(EXIT_FAILURE);
    }

    unsigned int row = 0;
    unsigned int column = 0;
    char         line[255];
    while (fgets(line, 255, fp) != NULL) {
        if (row == 0)
            column = strlen(line) - 1;
        strncpy(map + row * column, line, column);
        row++;
    }
    struct Garden *garden = NULL;

    initialize_garden(&garden, map, row, column);

    clock_gettime(CLOCK_REALTIME, &stop);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", &start, &stop, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, garden, 1);
    clock_gettime(CLOCK_REALTIME, &stop);
    aoc_timer_gen("Total time:", &start, &stop, BORDER_TOP | BORDER_BOTTOM);

    free(garden);
    return EXIT_SUCCESS;
}
