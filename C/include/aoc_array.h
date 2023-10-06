#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include <stdbool.h>
#include <stddef.h>
#include "aoc_types.h"
#include <stdint.h>

// General array functions
#define aoc_array_length(_arr)                  ((_arr)->length)
#define aoc_array_sized_new(_s, _size)          (aoc_array_new(_s, _size))


// int32_t array function macros
#define aoc_int32_array_new()                   (aoc_array_new(AOC_ARRAY_INT32, 1))
#define aoc_int32_array_index(arr_, index_)     (*(int32_t *)(aoc_array_index(arr_, index_)))
#define aoc_int32_array_append(arr_, value_)    do { \
                                                    int val_ = value_; \
                                                    aoc_array_append(arr_, &val_); \
                                                } while (0)
#define aoc_int32_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_int32_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_int32_array_sort(_arr, func)        (aoc_array_sort(_arr, func))


// uint32_t array function macros
#define aoc_uint32_array_new()                  (aoc_array_new(AOC_ARRAY_UINT32, 1))
#define aoc_uint32_array_index(arr_, index_)    (*(uint32_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint32_array_append(arr_, value_)   do { \
                                                    int val_ = value_; \
                                                    aoc_array_append(arr_, &val_); \
                                                } while (0)
#define aoc_uint32_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint32_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint32_array_sort(_arr, func)       (aoc_array_sort(_arr, func))


// int64_t array function macros
#define aoc_int64_array_new()                   (aoc_array_new(AOC_ARRAY_INT64, 1))
#define aoc_int64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int64_array_index(arr_, index_)     (*(int64_t *)(aoc_array_index(arr_, index_)))
#define aoc_int64_array_append(arr_, value_)    do { \
                                                     int val_ = value_; \
                                                     aoc_array_append(arr_, &val_); \
                                                 } while (0)
#define aoc_int64_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_int64_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_int64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))


// uint64_t array function macros
#define aoc_uint64_array_new()                  (aoc_array_new(AOC_ARRAY_UINT64, 1))
#define aoc_uint64_array_index(arr_, index_)    (*(uint64_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint64_array_append(arr_, value_)   do { \
                                                    int val_ = value_; \
                                                    aoc_array_append(arr_, &val_); \
                                                } while (0)
#define aoc_uint64_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint64_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint64_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint64_array_sort(_arr, func)       (aoc_array_sort(_arr, func))


// String (char *) array function macros
#define aoc_str_array_new()                     (aoc_array_new(AOC_ARRAY_STR, 1))
#define aoc_str_array_index(arr_, index_)       (*(char **)(aoc_array_index(arr_, index_)))
#define aoc_str_array_append(arr_, value_)      do { \
                                                    char *val_ = strdup(value_); \
                                                    aoc_array_append(arr_, &val_); \
                                                } while (0)
#define aoc_str_array_free(arr_)                (aoc_array_free(arr_, true))
#define aoc_str_array_free_all(arr_)            (aoc_array_free(arr_, true))
#define aoc_str_array_sort(_arr, func)          (aoc_array_sort(_arr, func))


// Char array function macros
#define aoc_char_array_new() i                  (aoc_array_new(AOC_ARRAY_CHAR, 1))
#define aoc_char_array_index(arr_, index_)      (*(char *)(aoc_array_index(arr_, index_)))
#define aoc_char_array_append(arr_, value_)     do {                               \
                                                    char val_ = value_;            \
                                                    aoc_array_append(arr_, &val_); \
                                                } while (0)

#define aoc_char_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_char_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_char_array_sort(_arr, func)         (aoc_array_sort(_arr, func))


// Point array function macros
#define aoc_point_array_new(size_)              (aoc_array_new(AOC_ARRAY_POINT, 1))
#define aoc_point_array_index(arr_, index_)     (*(Point *)(aoc_array_index(arr_, index_)))
#define aoc_point_array_append(arr_, value_)    (aoc_array_append(arr_, &value_));
#define aoc_point_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_point_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_point_array_sort(_arr, func)        (aoc_array_sort(_arr, func))


// Line (struct Line) array function macros
#define aoc_line_array_new()                    (aoc_array_new(AOC_ARRAY_LINE, 1))
#define aoc_line_array_index(_arr, _index)      (*(Line *)(aoc_array_index(_arr, _index)))
#define aoc_line_array_append(_arr, _val)       (aoc_array_append(_arr, &(_val)))
#define aoc_line_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_line_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_line_array_sort(_arr, func)         (aoc_array_sort(_arr, func))


// Integer (int32_t) array function macros
#define aoc_int_array_new()                     (aoc_int32_array_new())
#define aoc_int_array_index(_arr, _index)       (aoc_int32_array_index(_arr, _index))
#define aoc_int_array_append(_arr, _val)        aoc_int32_array_append(_arr, _val)
#define aoc_int_array_sort(_arr, func)          (aoc_array_sort(_arr, func))

// Point array function macros
#define aoc_ptr_array_new(size_)              (aoc_array_new(AOC_ARRAY_PTR, 1))
#define aoc_ptr_array_index(arr_, index_)     ((void *)(*(uint64_t *)(aoc_array_index(arr_, index_))))
#define aoc_ptr_array_append(arr_, value_)    (aoc_array_append(arr_, &(value_)));
#define aoc_ptr_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_ptr_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_ptr_array_sort(_arr, func)        (aoc_array_sort(_arr, func))



// Point (struct Point) array function macros


// Function declarations

void aoc_array_sort(AocArrayPtr arr, int (*compare_function)(const void *, const void *));
AocArray *aoc_array_new(AocArrayType, size_t);
void aoc_array_print(AocArray *);
void aoc_array_append(AocArray *, void *);
void *aoc_array_index(AocArray *, size_t);
void aoc_array_free(AocArray *, int);
AocArrayPtr aoc_array_remove_index(AocArrayPtr, size_t);

#endif // !__AOC_ARRAY_H__
