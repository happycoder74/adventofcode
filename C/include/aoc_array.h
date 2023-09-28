#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include <glib.h>

// General array functions
#define aoc_array_new(_s)                    (g_array_new(TRUE, TRUE, _s))
#define aoc_array_sized_new(_s, _size)       (g_array_sized_new(TRUE, TRUE, _s, _size))
#define aoc_array_length(_arr)               ((_arr)->len)
#define aoc_array_free(_arr)                 (g_array_free(_arr, FALSE));
#define aoc_array_index(_arr, _index)        (g_array_index(_arr, void *, _index))
#define aoc_array_append(_arr, _value)       (g_array_append_vals(_arr, &(_value), 1))
#define aoc_array_remove_index(_arr, _index) (g_array_remove_index(_arr, _index))

// Integer (int32_t) array function macros
#define aoc_int_array_new()                  (aoc_array_new(sizeof(int)))
#define aoc_int_array_index(_arr, _index)    (g_array_index(_arr, int, _index))

#define aoc_int_array_append(_arr, _val)     \
  do {                                       \
    int _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_int_array_sort(_arr, func)       (g_array_sort(_arr, func))

// int64_t array function macros
#define aoc_int64_array_new()                 (aoc_array_new(sizeof(int64_t)))
#define aoc_int64_array_index(_arr, _index)   (g_array_index(_arr, int64_t, _index))

#define aoc_int64_array_append(_arr, _val)    \
  do {                                       \
    int64_t _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_int64_array_sort(_arr, func)      (g_array_sort(_arr, func))

// uint64_t array function macros
#define aoc_uint64_array_new()                 (aoc_array_new(sizeof(uint64_t)))
#define aoc_uint64_array_index(_arr, _index)   (g_array_index(_arr, uint64_t, _index))

#define aoc_uint64_array_append(_arr, _val)    \
  do {                                       \
    uint64_t _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_uint64_array_sort(_arr, func)      (g_array_sort(_arr, func))
//
// String (char *) array function macros
#define aoc_str_array_new()                  (aoc_array_new(sizeof(char *)))
#define aoc_str_array_index(_arr, _index)    (g_array_index(_arr, char *, _index))
#define aoc_str_array_append(_arr, _val)     (g_array_append_vals(_arr, &(_val), 1))
#define aoc_str_array_sort(_arr, func)       (g_array_sort(_arr, func))

// Line (struct Line) array function macros
#define aoc_line_array_new()                 (aoc_array_new(sizeof(Line)))
#define aoc_line_array_index(_arr, _index)   (g_array_index(_arr, Line, _index))
#define aoc_line_array_append(_arr, _val)    (g_array_append_vals(_arr, &(_val), 1))
#define aoc_line_array_sort(_arr, func)      (g_array_sort(_arr, func))

// Point (struct Point) array function macros
#define aoc_point_array_new()                (aoc_array_new(sizeof(Point)))
#define aoc_point_array_index(_arr, _index)  (g_array_index(_arr, Point, _index))
#define aoc_point_array_append(_arr, _val)   (g_array_append_vals(_arr, &(_val), 1))
#define aoc_point_array_sort(_arr, func)     (g_array_sort(_arr, func))

#endif // !__AOC_ARRAY_H__
