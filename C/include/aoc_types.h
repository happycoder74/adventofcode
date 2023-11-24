#ifndef _AOC_TYPES_H_
#define _AOC_TYPES_H_

#include <stddef.h>
#include <stdint.h>

typedef enum AocArrayType {
    AOC_ARRAY_CHAR,
    AOC_ARRAY_UCHAR,
    AOC_ARRAY_INT32,
    AOC_ARRAY_UINT32,
    AOC_ARRAY_INT64,
    AOC_ARRAY_UINT64,
    AOC_ARRAY_STR,
    AOC_ARRAY_LINE,
    AOC_ARRAY_POINT,
    AOC_ARRAY_PTR,
    AOC_ARRAY_COUNT
} AocArrayType;

typedef struct AocArray {
    AocArrayType type;
    size_t       length;
    uint8_t      free_segments;
} AocArray;

typedef AocArray *AocArrayPtr;

typedef struct {
    char       *filename;
    int         year;
    int         day;
    int         free_segments;
    AocArrayPtr data;
} AocData_t;

typedef struct point {
    int x;
    int y;
} Point;

typedef struct line {
    Point p0;
    Point p1;
    int   stepx;
    int   stepy;
} Line;

typedef struct AocSList {
    struct AocSList *next;
    void            *data;
} AocSList;

#endif
