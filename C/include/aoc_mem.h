#ifndef __AOC_MEM_H__
#define __AOC_MEM_H__

#include "aoc_types.h"
#ifndef NDEBUG

#define free(_addr_)                                aoc_free_debug(_addr_, __FILE__, __LINE__)
#define malloc(_size_)                              aoc_malloc_debug(_size_, __FILE__, __LINE__)
#define calloc(_count_, _size_)                     aoc_calloc_debug(_count_, _size_, __FILE__, __LINE__)
#define realloc(_ptr_, _size_)                      aoc_realloc_debug(_ptr_, _size_, __FILE__, __LINE__)

#undef aoc_ptr_array_append
#define aoc_ptr_array_append(_arr_, _value_)        aoc_array_append_debug(_arr_, &(_value_), __FILE__, __LINE__)

#undef aoc_ptr_array_new
#define aoc_ptr_array_new()                         aoc_array_new_debug(AOC_ARRAY_PTR, 1, __FILE__, __LINE__)

#define g_hash_table_new(_hash_func_, _equal_func_) g_hash_table_new_mem_debug(_hash_func_, _equal_func_, __FILE__, __LINE__)
#define g_hash_table_destroy(_hash_table_)          g_hash_table_destroy_mem_debug(_hash_table_, __FILE__, __LINE__);

void aoc_free_debug(void *, char *, int);
void *aoc_malloc_debug(size_t, char *, int);
void *aoc_calloc_debug(size_t, size_t, char *, int);
void *aoc_realloc_debug(void *, size_t, char *, int);
void aoc_mem_report_debug(void);
void aoc_mem_wrap_up(void);
void *aoc_array_append_debug(AocArrayPtr, void *, char *, int);
void *aoc_array_new_debug(AocArrayType, size_t, char *, int);
void *g_hash_table_new_mem_debug(unsigned int (*hash_func)(const void *), int (*eq_func)(const void *, const void *), char *, int);
void *g_hash_table_destroy_mem_debug(void *, char *, int);
#endif

#endif // !__AOC_MEM_H__
