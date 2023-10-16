#ifndef __AOC_ARRAY_H__
#define __AOC_ARRAY_H__

#include <glib.h>
#include <stdint.h>

// General array functions
<<<<<<< Updated upstream
#define aoc_array_new(_s)                    (g_array_new(TRUE, TRUE, _s))
#define aoc_array_sized_new(_s, _size)       (g_array_sized_new(TRUE, TRUE, _s, _size))
#define aoc_array_length(_arr)               ((_arr)->len)
#define aoc_array_free(_arr)                 (g_array_free(_arr, FALSE));
#define aoc_array_index(_arr, _index)        (g_array_index(_arr, void *, _index))
#define aoc_array_append(_arr, _value)       (g_array_append_vals(_arr, &(_value), 1))
#define aoc_array_remove_index(_arr, _index) (g_array_remove_index(_arr, _index))
=======
#define aoc_array_length(_arr)                  ((_arr)->length)
#define aoc_array_sized_new(_s, _size)          (aoc_array_new(_s, _size))

// int32_t array function macros
#define aoc_int32_array_new()                   (aoc_array_new(AOC_ARRAY_INT32, 0))
#define aoc_int32_array_index(arr_, index_)     (*(int32_t *)(aoc_array_index(arr_, index_)))
#define aoc_int32_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_int32_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_int32_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int32_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT32) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_int32_array_prepend(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT32) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))


// uint32_t array function macros
#define aoc_uint32_array_new()                  (aoc_array_new(AOC_ARRAY_UINT32, 0))
#define aoc_uint32_array_index(arr_, index_)    (*(uint32_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint32_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint32_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint32_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint32_array_append(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT32) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_uint32_array_prepend(_arr_, _val_)   (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT32) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))


// int64_t array function macros
#define aoc_int64_array_new()                   (aoc_array_new(AOC_ARRAY_INT64, 0))
#define aoc_int64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int64_array_index(arr_, index_)     (*(int64_t *)(aoc_array_index(arr_, index_)))
#define aoc_int64_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_int64_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_int64_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_int64_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT64) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_int64_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_INT64) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))


// uint64_t array function macros
#define aoc_uint64_array_new()                  (aoc_array_new(AOC_ARRAY_UINT64, 0))
#define aoc_uint64_array_index(arr_, index_)    (*(uint64_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint64_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint64_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint64_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint64_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
#define aoc_uint64_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT64) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_uint64_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UINT64) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))


// String (char *) array function macros
#define aoc_str_array_new()                     (aoc_array_new(AOC_ARRAY_STR, 0))
#define aoc_str_array_index(arr_, index_)       (*(char **)(aoc_array_index(arr_, index_)))
#define aoc_str_array_free(arr_)                (aoc_array_free(arr_, true))
#define aoc_str_array_free_all(arr_)            (aoc_array_free(arr_, true))
#define aoc_str_array_sort(_arr, func)          (aoc_array_sort(_arr, func))


// Char array function macros
#define aoc_char_array_new()                    (aoc_array_new(AOC_ARRAY_CHAR, 0))
#define aoc_char_array_index(arr_, index_)      (*(char *)(aoc_array_index(arr_, index_)))
#define aoc_char_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_char_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_char_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_char_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_CHAR) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_char_array_prepend(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_CHAR) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

// Unsigned Char array function macros
#define aoc_uchar_array_new()                    (aoc_array_new(AOC_ARRAY_UCHAR, 0))
#define aoc_uchar_array_index(arr_, index_)      (*(unsigned char *)(aoc_array_index(arr_, index_)))
#define aoc_uchar_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_uchar_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_uchar_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_uchar_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UCHAR) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_uchar_array_prepend(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_UCHAR) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))


// Point array function macros
#define aoc_point_array_new(size_)              (aoc_array_new(AOC_ARRAY_POINT, 0))
#define aoc_point_array_index(arr_, index_)     (*(Point *)(aoc_array_index(arr_, index_)))
#define aoc_point_array_free(arr_)              (aoc_array_free(arr_, false))
#define aoc_point_array_free_all(arr_)          (aoc_array_free(arr_, true))
#define aoc_point_array_sort(_arr, func)        (aoc_array_sort(_arr, func))
#define aoc_point_array_append(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_POINT) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_point_array_prepend(_arr_, _val_)    (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_POINT) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))


// Line (struct Line) array function macros
#define aoc_line_array_new()                    (aoc_array_new(AOC_ARRAY_LINE, 0))
#define aoc_line_array_index(_arr, _index)      (*(Line *)(aoc_array_index(_arr, _index)))
#define aoc_line_array_free(arr_)               (aoc_array_free(arr_, false))
#define aoc_line_array_free_all(arr_)           (aoc_array_free(arr_, true))
#define aoc_line_array_sort(_arr, func)         (aoc_array_sort(_arr, func))
#define aoc_line_array_append(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_LINE) ? (aoc_array_append(_arr_, &(_val_))) : NULL))
#define aoc_line_array_prepend(_arr_, _val_)     (ISNULL(_arr_) ? NULL : (ISTYPE(_arr_, AOC_ARRAY_LINE) ? (aoc_array_prepend(_arr_, &(_val_))) : NULL))

>>>>>>> Stashed changes

// Integer (int32_t) array function macros
#define aoc_int_array_new()                  (aoc_array_new(sizeof(int)))
#define aoc_int_array_index(_arr, _index)    (g_array_index(_arr, int, _index))

#define aoc_int_array_append(_arr, _val)     \
  do {                                       \
    int _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_int_array_sort(_arr, func)       (g_array_sort(_arr, func))

// Char array function macros
#define aoc_char_array_new()                  (aoc_array_new(sizeof(char)))
#define aoc_char_array_index(_arr, _index)    (g_array_index(_arr, char, _index))

#define aoc_char_array_append(_arr, _val)     \
  do {                                       \
    char _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_char_array_sort(_arr, func)       (g_array_sort(_arr, func))

// int32_t array function macros
#define aoc_int32_array_new()                 (aoc_array_new(sizeof(int32_t)))
#define aoc_int32_array_index(_arr, _index)   (g_array_index(_arr, int32_t, _index))

#define aoc_int32_array_append(_arr, _val)    \
  do {                                       \
    int32_t _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_int32_array_sort(_arr, func)      (g_array_sort(_arr, func))

// uint32_t array function macros
#define aoc_uint32_array_new()                 (aoc_array_new(sizeof(uint32_t)))
#define aoc_uint32_array_index(_arr, _index)   (g_array_index(_arr, uint32_t, _index))

#define aoc_uint32_array_append(_arr, _val)    \
  do {                                       \
    uint32_t _value = _val;                       \
    g_array_append_vals(_arr, &(_value), 1); \
  } while (0)

#define aoc_uint32_array_sort(_arr, func)      (g_array_sort(_arr, func))

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
