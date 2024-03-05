#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include "aoc_types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Helper macros
#define ISNULL(_arr_)                            ((_arr_) == NULL)
#define ISTYPE(_arr_, _type_)                    ((_arr_)->type == _type_)

// General array functions
#define aoc_array_length(_arr)                   ((_arr)->length)
#define aoc_array_sized_new(_s, _size)           (aoc_array_new(_s, _size))

// int32_t array function macros
#define aoc_int32_array_new()                    (aoc_array_new(AOC_ARRAY_INT32, 0))
#define aoc_int32_array_index(arr_, index_)      (*(int32_t *)(aoc_array_index(arr_, index_)))
#define aoc_int32_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_int32_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_int32_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_int32_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT32) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_int32_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT32) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))
#define aoc_int32_array_contains(_arr_, _value_) aoc_array_contains(_arr_, &(_value_))
#define aoc_int32_array_last(_array_)            (*(int32_t *)aoc_array_last(_array_))

// uint32_t array function macros
#define aoc_uint32_array_new()                   (aoc_array_new(AOC_ARRAY_UINT32, 0))
#define aoc_uint32_array_index(arr_, index_)     (*(uint32_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint32_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_uint32_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_uint32_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_uint32_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT32) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_uint32_array_prepend(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT32) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// int64_t array function macros
#define aoc_int64_array_new()                    (aoc_array_new(AOC_ARRAY_INT64, 0))
#define aoc_int64_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_int64_array_index(arr_, index_)      (*(int64_t *)(aoc_array_index(arr_, index_)))
#define aoc_int64_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_int64_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_int64_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_int64_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT64) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_int64_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT64) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// uint64_t array function macros
#define aoc_uint64_array_new()                   (aoc_array_new(AOC_ARRAY_UINT64, 0))
#define aoc_uint64_array_index(arr_, index_)     (*(uint64_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint64_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_uint64_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_uint64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_uint64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_uint64_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT64) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_uint64_array_prepend(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT64) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// String (char *) array function macros
#define aoc_str_array_new()                      (aoc_array_new(AOC_ARRAY_STR, 0))
#define aoc_str_array_index(arr_, index_)        (*(char **)(aoc_array_index(arr_, index_)))
#define aoc_str_array_free(arr_)                 (aoc_array_free(arr_, true))
#define aoc_str_array_free_all(arr_)             (aoc_array_free(arr_, true))
#define aoc_str_array_sort(_arr, func)           (aoc_array_sort(_arr, func))

// Char array function macros
#define aoc_char_array_new()                     (aoc_array_new(AOC_ARRAY_CHAR, 0))
#define aoc_char_array_index(arr_, index_)       (*(char *)(aoc_array_index(arr_, index_)))
#define aoc_char_array_free(arr_)                (aoc_array_free(arr_, false))
#define aoc_char_array_free_all(arr_)            (aoc_array_free(arr_, true))
#define aoc_char_array_sort(_arr, func)          (aoc_array_sort(_arr, func))
#define aoc_char_array_append(_arr_, _val_)      (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_CHAR) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_char_array_prepend(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_CHAR) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))
#define aoc_char_array_contains(_arr_, _value_)  aoc_array_contains(_arr_, &(_value_))
#define aoc_char_array_find(_arr_, _value_)      aoc_array_find(_arr_, &(_value_))

// Unsigned Char array function macros
#define aoc_uchar_array_new()                    (aoc_array_new(AOC_ARRAY_UCHAR, 0))
#define aoc_uchar_array_index(arr_, index_)      (*(unsigned char *)(aoc_array_index(arr_, index_)))
#define aoc_uchar_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_uchar_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_uchar_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_uchar_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UCHAR) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_uchar_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UCHAR) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// Point array function macros
#define aoc_point_array_new(size_)               (aoc_array_new(AOC_ARRAY_POINT, 0))
#define aoc_point_array_index(arr_, index_)      (*(Point *)(aoc_array_index(arr_, index_)))
#define aoc_point_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_point_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_point_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_point_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_POINT) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_point_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_POINT) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// Line (struct Line) array function macros
#define aoc_line_array_new()                     (aoc_array_new(AOC_ARRAY_LINE, 0))
#define aoc_line_array_index(_arr, _index)       (*(Line *)(aoc_array_index(_arr, _index)))
#define aoc_line_array_free(arr_)                (aoc_array_free(arr_, false))
#define aoc_line_array_free_all(arr_)            (aoc_array_free(arr_, true))
#define aoc_line_array_sort(_arr, func)          (aoc_array_sort(_arr, func))
#define aoc_line_array_append(_arr_, _val_)      (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_LINE) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_line_array_prepend(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_LINE) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// Integer (int32_t) array function macros
#define aoc_int_array_new()                      (aoc_int32_array_new())
#define aoc_int_array_index(_arr, _index)        (aoc_int32_array_index(_arr, _index))
#define aoc_int_array_append(_arr, _val)         aoc_int32_array_append(_arr, _val)
#define aoc_int_array_sort(_arr, func)           (aoc_array_sort(_arr, func))

// Point array function macros
#define aoc_ptr_array_new()                      (aoc_array_new(AOC_ARRAY_PTR, 0))
#define aoc_ptr_array_index(arr_, index_)        (aoc_array_index(arr_, index_))
#define aoc_ptr_array_append(arr_, value_)       (aoc_array_append(arr_, value_));
#define aoc_ptr_array_prepend(arr_, value_)      (aoc_array_prepend(arr_, value_));
#define aoc_ptr_array_free(arr_)                 (aoc_array_free(arr_, false))
#define aoc_ptr_array_free_all(arr_)             (aoc_array_free(arr_, true))
#define aoc_ptr_array_sort(_arr, func)           (aoc_array_sort(_arr, func))

// double array function macros
#define aoc_double_array_new()                   (aoc_array_new(AOC_ARRAY_DOUBLE, 0))
#define aoc_double_array_index(arr_, index_)     (*(double *)(aoc_array_index(arr_, index_)))
#define aoc_double_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_double_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_double_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_double_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_double_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_DOUBLE) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_double_array_prepend(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_DOUBLE) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// Point (struct Point) array function macros

// Function declarations

AocArrayPtr aoc_int32_array_set_index(AocArrayPtr array, size_t index, int32_t value);
AocArrayPtr aoc_int64_array_set_index(AocArrayPtr array, size_t index, int64_t value);
AocArrayPtr aoc_uint32_array_set_index(AocArrayPtr array, size_t index, uint32_t value);
AocArrayPtr aoc_uint64_array_set_index(AocArrayPtr array, size_t index, uint64_t value);

void *aoc_str_array_append(AocArrayPtr array, char *str);
void *aoc_str_array_prepend(AocArrayPtr array, char *str);

void        aoc_array_sort(AocArrayPtr arr, AocCompareFunc func);
AocArray   *aoc_array_new(AocArrayType array_type, size_t length);
void        aoc_array_print(AocArray *array);
void       *aoc_array_append(AocArray *array, void *value);
void       *aoc_array_prepend(AocArray *array, void *value);
void       *aoc_array_index(AocArray *array, size_t index);
void        aoc_array_free(AocArray *array, int free_segments);
AocArrayPtr aoc_array_remove_index(AocArrayPtr array, size_t index);
void       *aoc_array_get_data(AocArrayPtr array);
AocArrayPtr aoc_array_copy(AocArrayPtr array);
size_t      aoc_array_get_element_size(AocArrayPtr array);
size_t      aoc_array_get_capacity(AocArrayPtr array);
int         aoc_array_contains(AocArrayPtr array, void *value);
int         aoc_array_find(AocArrayPtr array, void *value);
AocArrayPtr aoc_array_new_from_data(AocArrayType array_type, void *data, size_t length);
void       *aoc_array_last(AocArrayPtr array);

int int32_compare(const void *a, const void *b);
int int64_compare(const void *a, const void *b);
int double_compare(const void *a, const void *b);

double aoc_double_array_mean(AocArrayPtr array);
double aoc_double_array_stddev(AocArrayPtr array);
#endif // !__AOC_ARRAY_H__
