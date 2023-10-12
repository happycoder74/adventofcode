#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include <stdbool.h>
#include <stddef.h>
#include "aoc_types.h"
#include <stdint.h>

// Helper macros
#define ISNULL(_arr_)                           ((_arr_) == NULL)
#define ISTYPE(_arr_, _type_)                   ((_arr_)->type == _type_)

// General array functions
#define aoc_array_length(_arr)                  ((_arr)->length)
#define aoc_array_sized_new(_s, _size)          (aoc_array_new(_s, _size))

// int32_t array function macros
#define aoc_int32_array_new()                   (aoc_array_new(AOC_ARRAY_INT32, 1))
#define aoc_int32_array_index(arr_, index_)     (*(int32_t *)(aoc_array_index(arr_, index_)))
#define aoc_int32_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_int32_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_int32_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int32_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT32) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// uint32_t array function macros
#define aoc_uint32_array_new()                  (aoc_array_new(AOC_ARRAY_UINT32, 1))
#define aoc_uint32_array_index(arr_, index_)    (*(uint32_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint32_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint32_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint32_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint32_array_append(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT32) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// int64_t array function macros
#define aoc_int64_array_new()                   (aoc_array_new(AOC_ARRAY_INT64, 1))
#define aoc_int64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int64_array_index(arr_, index_)     (*(int64_t *)(aoc_array_index(arr_, index_)))
#define aoc_int64_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_int64_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_int64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int64_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT64) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// uint64_t array function macros
#define aoc_uint64_array_new()                  (aoc_array_new(AOC_ARRAY_UINT64, 1))
#define aoc_uint64_array_index(arr_, index_)    (*(uint64_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint64_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint64_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint64_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint64_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint64_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT64) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// String (char *) array function macros
#define aoc_str_array_new()                     (aoc_array_new(AOC_ARRAY_STR, 1))
#define aoc_str_array_index(arr_, index_)       (*(char **)(aoc_array_index(arr_, index_)))
#define aoc_str_array_free(arr_)                (aoc_array_free(arr_, true))
#define aoc_str_array_free_all(arr_)            (aoc_array_free(arr_, true))
#define aoc_str_array_sort(_arr, func)          (aoc_array_sort(_arr, func))


// Char array function macros
#define aoc_char_array_new() i                  (aoc_array_new(AOC_ARRAY_CHAR, 1))
#define aoc_char_array_index(arr_, index_)      (*(char *)(aoc_array_index(arr_, index_)))
#define aoc_char_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_char_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_char_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_char_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_CHAR) ? (aoc_array_append(_arr_, &(_val_))) : NULL))

// Unsigned Char array function macros
#define aoc_uchar_array_new() i                  (aoc_array_new(AOC_ARRAY_UCHAR, 1))
#define aoc_uchar_array_index(arr_, index_)      (*(unsigned char *)(aoc_array_index(arr_, index_)))
#define aoc_uchar_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_uchar_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_uchar_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_uchar_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UCHAR) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// Point array function macros
#define aoc_point_array_new(size_)              (aoc_array_new(AOC_ARRAY_POINT, 1))
#define aoc_point_array_index(arr_, index_)     (*(Point *)(aoc_array_index(arr_, index_)))
#define aoc_point_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_point_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_point_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_point_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_POINT) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// Line (struct Line) array function macros
#define aoc_line_array_new()                    (aoc_array_new(AOC_ARRAY_LINE, 1))
#define aoc_line_array_index(_arr, _index)      (*(Line *)(aoc_array_index(_arr, _index)))
#define aoc_line_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_line_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_line_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_line_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_LINE) ? (aoc_array_append(_arr_, &(_val_))) : NULL))


// Integer (int32_t) array function macros
#define aoc_int_array_new()                     (aoc_int32_array_new())
#define aoc_int_array_index(_arr, _index)       (aoc_int32_array_index(_arr, _index))
#define aoc_int_array_append(_arr, _val)        aoc_int32_array_append(_arr, _val)
#define aoc_int_array_sort(_arr, func)          (aoc_array_sort(_arr, func))

// Point array function macros
#define aoc_ptr_array_new()                     (aoc_array_new(AOC_ARRAY_PTR, 1))
#define aoc_ptr_array_index(arr_, index_)       ((void *)(*(uint64_t *)(aoc_array_index(arr_, index_))))
#define aoc_ptr_array_append(arr_, value_)      (aoc_array_append(arr_, &(value_)));
#define aoc_ptr_array_free(arr_)                (aoc_array_free(arr_, false))
#define aoc_ptr_array_free_all(arr_)            (aoc_array_free(arr_, true))
#define aoc_ptr_array_sort(_arr, func)          (aoc_array_sort(_arr, func))



// Point (struct Point) array function macros


// Function declarations
void *aoc_str_array_append(AocArrayPtr, char *);

AocArrayPtr aoc_int32_array_set_index(AocArrayPtr, size_t index, int32_t);
AocArrayPtr aoc_int64_array_set_index(AocArrayPtr, size_t index, int64_t);
AocArrayPtr aoc_uint32_array_set_index(AocArrayPtr, size_t index, uint32_t);
AocArrayPtr aoc_uint64_array_set_index(AocArrayPtr, size_t index, uint64_t);

AocArrayPtr aoc_int32_array_prepend(AocArrayPtr, int32_t);


void aoc_array_sort(AocArrayPtr arr, int (*compare_function)(const void *, const void *));
AocArray *aoc_array_new(AocArrayType, size_t);
void aoc_array_print(AocArray *);
void *aoc_array_append(AocArray *, void *);
void *aoc_array_index(AocArray *, size_t);
void aoc_array_free(AocArray *, int);
AocArrayPtr aoc_array_remove_index(AocArrayPtr, size_t);
void *aoc_array_get_data(AocArrayPtr);
AocArrayPtr aoc_array_copy(AocArrayPtr);

#endif // !__AOC_ARRAY_H__
