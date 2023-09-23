#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include <glib.h>

typedef GArray AocArray;
typedef GArray* AocArrayPtr;

// General array functions
AocArray *aoc_array_new(size_t);
size_t aoc_array_length(AocArrayPtr);
void *aoc_array_index(AocArrayPtr, size_t);
void aoc_array_append(AocArrayPtr, void *);
void aoc_array_free(AocArrayPtr);

// Integer (int32_t) array function macros
#define aoc_int_array_new()             (aoc_array_new(sizeof(int)))
#define aoc_int_array_index(arr, index) (g_array_index(arr, int, index))
#define aoc_int_array_append(arr, val)  \
  do { \
    int value = val; \
    g_array_append_vals(arr, &(value), 1); \
  } while (0)

// String (char *) array function macros
#define aoc_str_array_new()             (aoc_array_new(sizeof(char *)))
#define aoc_str_array_index(arr, index) (g_array_index(arr, char *, index))
#define aoc_str_array_append(arr, val)  (g_array_append_vals(arr, &(val), 1))

#endif // !__AOC_ARRAY_H__
