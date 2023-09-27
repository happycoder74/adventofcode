#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include <glib.h>

typedef GArray AocArray;
typedef GArray* AocArrayPtr;

// General array functions
#define aoc_array_new(s)                (g_array_new(TRUE, TRUE, s))
#define aoc_array_sized_new(s, _size)   (g_array_sized_new(TRUE, TRUE, s, _size))
#define aoc_array_length(arr)           ((arr)->len)
#define aoc_array_free(arr)             (g_array_free(arr, FALSE));

// Integer (int32_t) array function macros
#define aoc_int_array_new()             (aoc_array_new(sizeof(int)))
#define aoc_int_array_index(arr, index) (g_array_index(arr, int, index))

#define aoc_int_array_append(arr, val)     \
  do {                                     \
    int value = val;                       \
    g_array_append_vals(arr, &(value), 1); \
  } while (0)

#define aoc_int_array_sort(arr, func)   (g_array_sort(arr, func))

// String (char *) array function macros
#define aoc_str_array_new()             (aoc_array_new(sizeof(char *)))
#define aoc_str_array_index(arr, index) (g_array_index(arr, char *, index))
#define aoc_str_array_append(arr, val)  (g_array_append_vals(arr, &(val), 1))
#define aoc_str_array_sort(arr, func)   (g_array_sort(arr, func))

#endif // !__AOC_ARRAY_H__
