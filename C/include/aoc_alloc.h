#ifndef __AOC_ALLOC_H_
#define __AOC_ALLOC_H_

#ifdef MEMDEBUG
#include <stdint.h>
#include <stdlib.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __FUNCTION__ __func__
#ifndef NDEBUG
#ifdef DEBUG_VERBOSE
#define aoc_malloc(size_)          aoc_malloc_internal(size_, __FUNCTION__, __FILENAME__, __LINE__)
#define aoc_calloc(n_elem_, size_) aoc_calloc_internal(n_elem_, size_, __FUNCTION__, __FILENAME__, __LINE__)
#define aoc_realloc(ptr_, size_)   aoc_realloc_internal(ptr_, size_, __FUNCTION__, __FILENAME__, __LINE__)
#define aoc_free(ptr_)             aoc_free_internal(ptr_, __FUNCTION__, __FILENAME__, __LINE__)

void *aoc_malloc_internal(size_t size, const char *function, const char *file, const int line);
void *aoc_calloc_internal(size_t n_elements, size_t element_size, const char *function, const char *file, const int line);
void *aoc_realloc_internal(void *mem_ptr, size_t new_size, const char *function, const char *file, const int line);
void  aoc_free_internal(void *mem_ptr, const char *function, const char *file, const int line);
#else
#define aoc_malloc(size_)          aoc_malloc_internal(size_)
#define aoc_calloc(n_elem_, size_) aoc_calloc_internal(n_elem_, size_)
#define aoc_realloc(ptr_, size_)   aoc_realloc_internal(ptr_, size_)
#define aoc_free(ptr_)             aoc_free_internal(ptr_)

void *aoc_malloc_internal(size_t size);
void *aoc_calloc_internal(size_t n_elements, size_t element_size);
void *aoc_realloc_internal(void *mem_ptr, size_t new_size);
void  aoc_free_internal(void *mem_ptr);
#endif
uint64_t aoc_mem_gc(void);
void     init_mem_table(void);

#else

#include <stdlib.h>
#define aoc_mem_gc() 0
void init_mem_table(void);

#endif
#endif // !__AOC_ALLOC_H_
