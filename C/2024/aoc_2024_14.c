#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Position {
    unsigned int x;
    unsigned int y;
};

struct Robot {
    unsigned int id;
    int          pos_x;
    int          pos_y;
    int          vx;
    int          vy;
    int          max_x;
    int          max_y;
};

struct Bathroom {
    unsigned int room[101 * 103];
    int          max_x;
    int          max_y;
    struct Robot robots[500];
    unsigned int nrobots;
};

void print_room(struct Bathroom *room) {
    for (int r = 0; r < room->max_y; r++) {
        for (int c = 0; c < room->max_x; c++) {
            if ((c == room->max_x / 2) || (r == room->max_y / 2)) {
                printf(" ");
            } else if (room->room[c + r * room->max_x] == 0) {
                printf(".");
            } else {
                printf("%d", room->room[c + r * room->max_x]);
            }
        }
        printf("\n");
    }
}

void print_robot(struct Robot *r) {
    printf("Robot %d: pos_x=%d, pos_y=%d, vx=%d, vy=%d\n", r->id, r->pos_x, r->pos_y, r->vx, r->vy);
}
void move_robot(struct Robot *r, unsigned int steps) {
    int pos_x, pos_y;
    pos_x = (r->pos_x + r->vx * (int)steps) % r->max_x;
    pos_y = (r->pos_y + r->vy * (int)steps) % r->max_y;
    pos_x = pos_x < 0 ? pos_x + r->max_x : pos_x;
    pos_y = pos_y < 0 ? pos_y + r->max_y : pos_y;
    r->pos_x = pos_x;
    r->pos_y = pos_y;
}

void move_robots(struct Bathroom *room, unsigned int steps) {

    for (unsigned int ir = 0; ir < room->nrobots; ir++) {
        struct Robot *r = room->robots + ir;
        room->room[r->pos_x + r->pos_y * r->max_x] -= 1;
        move_robot(r, steps);
        room->room[r->pos_x + r->pos_y * r->max_x] += 1;
    }
}

int solve_part_1(struct Bathroom *room) {
    unsigned int result = 0;

    move_robots(room, 100);
    unsigned int quadrant = 0;
    // First quadrant - Top Left
    for (int row = 0; row < room->max_y / 2; row++) {
        for (int column = 0; column < room->max_x / 2; column++) {
            quadrant += room->room[column + row * room->max_x];
        }
    }
    result = quadrant;

    // Second quadrant - Top Right
    quadrant = 0;
    for (int row = 0; row < room->max_y / 2; row++) {
        for (int column = room->max_x / 2 + 1; column < room->max_x; column++) {
            quadrant += room->room[column + row * room->max_x];
        }
    }
    result *= quadrant;

    // Third quadrant - Bottom Left
    quadrant = 0;
    for (int row = room->max_y / 2 + 1; row < room->max_y; row++) {
        for (int column = 0; column < room->max_x / 2; column++) {
            quadrant += room->room[column + row * room->max_x];
        }
    }
    result *= quadrant;

    // Fourth quadrant - Bottom Right
    quadrant = 0;
    for (int row = room->max_y / 2 + 1; row < room->max_y; row++) {
        for (int column = room->max_x / 2 + 1; column < room->max_x; column++) {
            quadrant += room->room[column + row * room->max_x];
        }
    }

    return result * quadrant;
}

short int no_dups(struct Bathroom *room) {
    for (int r = 0; r < room->max_y; r++) {
        for (int c = 0; c < room->max_x; c++) {
            if (room->room[c + r * room->max_x] > 1) {
                return 0;
            }
        }
    }

    return 1;
}

int solve_part_2(struct Bathroom *room) {
    unsigned int result = 0;
    while (!no_dups(room)) {
        result += 1;
        move_robots(room, 1);
    }

    return result;
}

int main(int argc, char **argv) {
    FILE           *fp = NULL;
    char            filepath[255];
    char            filename[40] = "input.txt";
    struct Bathroom room = {0};

    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    if (argc > 1) {
        if (!strcmp("--test", argv[1])) {
            sprintf(filename, "test_input.txt");
        }
    }
    sprintf(filepath, "%s/2024/14/%s", getenv("AOC_DATA_LOCATION"), filename);
    fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    unsigned int index = 0;
    char         line[255];
    while (fgets(line, 255, fp) != NULL) {
        struct Robot *r = room.robots + index;
        sscanf(line, "p=%d,%d v=%d,%d", &(r->pos_x), &(r->pos_y), &(r->vx), &(r->vy));
        if ((argc > 1) && (!strcmp(argv[1], "--test"))) {
            r->max_x = 11;
            r->max_y = 7;
        } else {
            r->max_x = 101;
            r->max_y = 103;
        }
        r->id = index;
        room.room[r->pos_x + r->pos_y * r->max_x] += 1;
        index++;
    }
    fclose(fp);

    room.nrobots = index;
    room.max_x = room.robots[0].max_x;
    room.max_y = room.robots[0].max_y;
    struct Bathroom room2 = room;

    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %10d", solve_part_1(&room));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2(&room2));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");
}
