#ifndef _AOC_TYPES_H_
#define _AOC_TYPES_H_

#include <glib.h>

typedef GArray AocArray;
typedef GArray* AocArrayPtr;

typedef struct {
    char *filename;
    int year;
    int day;
    AocArrayPtr data;
} AocData_t;

typedef struct point {
    int x;
    int y;
} Point;

typedef struct line {
    Point p0;
    Point p1;
    int stepx;
    int stepy;
} Line;

#endif
