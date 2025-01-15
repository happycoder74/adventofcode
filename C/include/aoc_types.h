#ifndef _AOC_TYPES_H_
#define _AOC_TYPES_H_

#include <stddef.h>
#include <stdint.h>

typedef enum {
    AOC_INT32,
    AOC_INT64,
    AOC_UINT32,
    AOC_UINT64,
    AOC_CHAR,
    AOC_STR,
    AOC_PTR,
    AOC_UCHAR,
    AOC_LINE,
    AOC_POINT,
    AOC_DOUBLE,
    AOC_COUNT
} AocType;

typedef AocType AocArrayType;

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
    void       *user_data;
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

#undef MAX
#define MAX(_a_, _b_) (((_a_) > (_b_)) ? (_a_) : (_b_))
#endif
