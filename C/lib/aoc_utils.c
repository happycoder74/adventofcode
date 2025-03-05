#include "aoc_utils.h"
#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_types.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

AocData_t *aoc_data_set_data(AocData_t *aoc, AocArrayPtr data) {
    if (aoc) {
        aoc->data = data;
        return aoc;
    }
    return NULL;
}

AocData_t *aoc_data_new_clean(char *filename, int year, int day,
                              AocArrayPtr (*parse_function)(AocArray *)) {
    AocData_t *data = (AocData_t *)malloc(sizeof(AocData_t));

    data->filename = strdup(filename);
    data->year = year;
    data->day = day;
    data->data = NULL;
    data->free_segments = 1;
    data->user_data = NULL;

    AocArrayPtr input_data = get_input(filename, year, day);
    if (!input_data) {
        aoc_data_free(data);
        exit(EXIT_FAILURE);
    }

    if (parse_function) {
        data->data = parse_function(input_data);
    } else {
        data->data = input_data;
    }
    return data;
}

AocData_t *get_data(int argc, char **argv, unsigned year, unsigned day,
                    AocArrayPtr (*parse_func)(AocArrayPtr)) {
    AocData_t *data;
    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new_clean("test_input.txt", year, day, parse_func);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, parse_func);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, parse_func);
    }
    return data;
}

void aoc_data_free(AocData_t *data) {
    if (data->filename) {
        free(data->filename);
    }

    if (data->data) {
        aoc_array_free(data->data, data->data->free_segments);
    }
    if (data->user_data) {
        free(data->user_data);
    }

    free(data);
}

int max(int *arr, int length) {
    int max = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int min(int *arr, int length) {
    int min = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int int_array_max(int *arr, int length) {
    int max = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int int_array_min(int *arr, int length) {
    int min = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int min_non_zero(int *arr, int length) {
    int min = length;
    int i;

    for (i = 0; i < length; i++) {
        if ((arr[i] < min) && (arr[i] != 0)) {
            min = arr[i];
        }
    }
    return min;
}

void print_line(Line line) {
    Point diff;
    Point point;

    diff = point_difference(line.p0, line.p1);

    printf("Line from (%d, %d) to (%d, %d) - distance (%d, %d) - step (%d, %d)\n", line.p0.x,
           line.p0.y, line.p1.x, line.p1.y, diff.x, diff.y, line.stepx, line.stepy);
    for (point = line.p0;
         (point.x != (line.p1.x + line.stepx)) || (point.y != (line.p1.y + line.stepy));
         point.x += line.stepx, point.y += line.stepy) {
        printf("\t(%d, %d)\n", point.x, point.y);
    }

    return;
}

Point point_difference(Point p0, Point p1) {
    Point diff;

    diff.x = p1.x - p0.x;
    diff.y = p1.y - p0.y;

    return diff;
}

Point points_on_line(Line line) {
    Point diff;

    diff = point_difference(line.p0, line.p1);

    return diff;
}

void point_move(Point *p, Point delta) {
    if (p) {
        p->x += delta.x;
        p->y += delta.y;
    }
}

int point_manhattan_distance(Point p0, Point p1) {
    return abs(p0.x - p1.x) + abs(p0.y - p1.y);
}

int point_distance(Point p0, Point p1) {
    return (int)sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
}

void point_print(Point p) {
    printf("Point (%d, %d)\n", p.x, p.y);
    return;
}

char *point_to_string(Point p, char *buf, unsigned bufsize) {
    snprintf(buf, bufsize, "(%d, %d)", p.x, p.y);
    return buf;
}

unsigned int64_hash(uint64_t value) {
    // Implementation from glib-v2.X
    const uint64_t bits = value;

    return (unsigned)((bits >> 32) ^ (bits & 0xffffffffU));
}

unsigned int point_hash(const void *p) {
    Point   *point = (Point *)p;
    uint64_t int_hash = point->x;
    int_hash <<= sizeof(UINT_MAX) * 4;
    int_hash ^= point->y;

    unsigned int return_value = int64_hash(int_hash);

    return return_value;
}

int point_equal(const void *pp1, const void *pp2) {
    Point *p1, *p2;
    p1 = (Point *)pp1;
    p2 = (Point *)pp2;
    return (p1->x == p2->x) && (p1->y == p2->y);
}

// Legacy function to be removed later
/* char *basename(const char *path) { */
/* #if (defined(__WIN32__) && !(defined __MINGW32__)) */
/*     char pathsep = '\\'; */
/* #else */
/*     char pathsep = '/'; */
/* #endif */
/*     char *ptr = (char *)strrchr(path, pathsep); */
/*     if (!ptr) */
/*         return strdup(path); */
/*     return strdup(ptr + 1); */
/* } */

char *basename_new(const char *path) {
#if (defined(__WIN32__) && !(defined __MINGW32__))
    char pathsep = '\\';
#else
    char pathsep = '/';
#endif
    char *ptr = (char *)strrchr(path, pathsep);
    if (!ptr)
        return (char *)path;
    return (ptr + 1);
}

char *_aoc_basename(const char *path, const char pathsep) {
    char *s = (char *)strrchr(path, pathsep);
    if (!s) {
        return strdup(path);
    } else {
        return strdup(s + 1);
    }
}

bool is_horisontal(Line line) {
    return line.p0.y == line.p1.y;
}

bool is_vertical(Line line) {
    return line.p0.x == line.p1.x;
}

bool is_parallel(Line line1, Line line2) {
    if (((line1.p0.x - line1.p1.x) == 0) && ((line2.p0.x - line2.p1.x) == 0))
        return true;
    if (((line1.p0.y - line1.p1.y) == 0) && ((line2.p0.y - line2.p1.y) == 0))
        return true;
    return false;
}

bool is_diagonal(Line line) {
    if (is_vertical(line))
        return false;
    return (abs((line.p1.y - line.p0.y) / (line.p1.x - line.p0.x)) == 1);
}

void line_print(Line line) {
    printf("(%d, %d) to (%d, %d)\n", line.p0.x, line.p0.y, line.p1.x, line.p1.y);
}

Line line_new(Point p0, Point p1) {
    Line line;
    line.p0 = p0;
    line.p1 = p1;
    line.stepx = p1.x - p0.x;
    line.stepy = p1.y - p0.y;
    return line;
}

Point point_new(int x, int y) {
    Point point;

    point.x = x;
    point.y = y;

    return point;
}

Point *point_new_m(int x, int y) {
    Point *p = (Point *)malloc(sizeof(Point));
    p->x = x;
    p->y = y;

    return p;
}

Point *line_intersection(Line line1, Line line2, Point *intersection_point) {
    float u, t;
    int   x1, x2, x3, x4;
    int   y1, y2, y3, y4;

    if (is_parallel(line1, line2)) {
        return NULL;
    }

    x1 = line1.p0.x;
    y1 = line1.p0.y;
    x2 = line1.p1.x;
    y2 = line1.p1.y;
    x3 = line2.p0.x;
    y3 = line2.p0.y;
    x4 = line2.p1.x;
    y4 = line2.p1.y;

    t = (float)((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) /
        (float)((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    u = (float)((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) /
        (float)((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    if (!((0 <= t) && (t <= 1.0)) || !((0 <= u) && (u <= 1.0))) {
        return NULL;
    }

    intersection_point->x = x1 + t * (x2 - x1);
    intersection_point->y = y1 + t * (y2 - y1);

    return intersection_point;
}

void line_array_print(AocArrayPtr lines) {
    for (size_t i = 0; i < aoc_array_length(lines); i++) {
        line_print(aoc_line_array_index(lines, i));
    }
}

bool point_on_line(Point p, Line line) {
    if (is_vertical(line)) {
        return ((MIN(line.p0.y, line.p1.y) <= p.y) && (p.y <= MAX(line.p0.y, line.p1.y)) &&
                (line.p0.x == p.x));
    } else if (is_horisontal(line)) {
        return ((MIN(line.p0.x, line.p1.x) <= p.x) && (p.x <= MAX(line.p0.x, line.p1.x)) &&
                (line.p0.y == p.y));
    } else {
        int y = (line.p1.y - line.p0.y) / (line.p1.x - line.p0.x) * (p.x - line.p0.x) + line.p0.y;
        return p.y == y;
    }
}

int line_length(Line line) {
    return point_distance(line.p0, line.p1);
}
