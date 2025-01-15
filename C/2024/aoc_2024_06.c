#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct position {
    unsigned int row;
    unsigned int column;
};

struct direction {
    int x;
    int y;
};

struct map {
    char             data[150][150];
    struct direction direction[150][150];
    struct position  guard;
    unsigned int     rows;
    unsigned int     cols;
};

struct direction turn(struct direction direction) {
    struct direction new_direction;

    int rotation_matrix[2][2] = {
        {0, -1},
        {1, 0 }
    };

    new_direction.x = direction.x * rotation_matrix[0][0] + direction.y * rotation_matrix[0][1];
    new_direction.y = direction.x * rotation_matrix[1][0] + direction.y * rotation_matrix[1][1];

    return new_direction;
}

struct position find_guard(struct map map) {
    struct position guard = {0, 0};
    char           *ptr = NULL;
    for (unsigned int row = 0; row < map.rows; row++) {
        if ((ptr = strchr(map.data[row], '^')) != NULL) {
            guard.row = row;
            guard.column = (ptr - map.data[row]) / sizeof(char);
        }
    }
    return guard;
}

unsigned short int inside_map(struct position pos, struct map map) {
    return ((0 <= pos.column) && (pos.column < map.cols)) &&
           ((0 <= pos.row) && (pos.row < map.rows));
}

int solve_part_1(struct map *map) {

    unsigned int     count = 0;
    struct direction direction = {0, -1};
    struct position  next_position;
    struct position  guard;

    map->data[map->guard.row][map->guard.column] = 'X';
    guard = map->guard;
    while (1) {
        next_position.row = guard.row + direction.y;
        next_position.column = guard.column + direction.x;
        if (!inside_map(next_position, *map)) {
            break;
        } else if (map->data[next_position.row][next_position.column] == '#') {
            direction = turn(direction);
        } else {
            guard.row = next_position.row;
            guard.column = next_position.column;
            map->data[guard.row][guard.column] = 'X';
        }
    }

    for (unsigned int r = 0; r < map->rows; r++) {
        for (unsigned int c = 0; c < map->cols; c++) {
            if (map->data[r][c] == 'X') {
                count++;
            }
        }
    }

    return count;
}

int solve_part_2(struct map map) {
    unsigned int count = 0;

    struct direction initial_direction = {0, -1};
    struct direction direction;
    struct position  next_position;
    struct map       tracemap;

    for (unsigned int r_obs = 0; r_obs < map.rows; r_obs++) {
        for (unsigned int c_obs = 0; c_obs < map.rows; c_obs++) {
            if ((map.data[r_obs][c_obs] != 'X') ||
                ((map.guard.row == r_obs) && (map.guard.column == c_obs))) {
                continue;
            }

            memmove(&tracemap, &map, sizeof(map));
            struct position guard = map.guard;
            memset(tracemap.direction, 0, sizeof(tracemap.direction));
            direction = initial_direction;
            tracemap.data[guard.row][guard.column] = 'X';
            tracemap.direction[guard.row][guard.column] = direction;
            while (1) {
                next_position.row = guard.row + direction.y;
                next_position.column = guard.column + direction.x;
                if (!inside_map(next_position, tracemap)) {
                    break;
                } else if ((tracemap.data[next_position.row][next_position.column] == '#') ||
                           ((next_position.row == r_obs) && (next_position.column == c_obs))) {
                    direction = turn(direction);
                } else if ((tracemap.data[next_position.row][next_position.column] == 'X') &&
                           (tracemap.direction[next_position.row][next_position.column].x ==
                            direction.x) &&
                           (tracemap.direction[next_position.row][next_position.column].y ==
                            direction.y)) {
                    count += 1;
                    break;
                } else {
                    guard.row = next_position.row;
                    guard.column = next_position.column;
                    tracemap.data[guard.row][guard.column] = 'X';
                    tracemap.direction[guard.row][guard.column] = direction;
                }
            }
        }
    }

    return count;
}

int main(int argc, char **argv) {

    FILE      *fp = NULL;
    char       filepath[255];
    char       filename[40] = "input.txt";
    struct map map = {
        {0},
        {{{0, 0}}},
        {0, 0},
        0, 0
    };

    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if (argc > 1) {
        if (!strcmp("--test", argv[1])) {
            sprintf(filename, "test_input.txt");
        }
    }
    sprintf(filepath, "%s/2024/06/%s", getenv("AOC_DATA_LOCATION"), filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    unsigned int row = 0;
    while (fgets(map.data[row], 150, fp) != NULL) {
        row++;
    }
    map.rows = row;
    map.cols = strlen(map.data[0]) - 1;
    /* for (unsigned int i = 0; i < map.rows; i++) { */
    /*     fputs(map.data[i], stdout); */
    /* } */

    map.guard = find_guard(map);
    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %10d", solve_part_1(&map));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2(map));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
}
