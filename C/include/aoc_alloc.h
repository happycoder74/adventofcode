#ifndef __AOC_ALLOC_H_
#define __AOC_ALLOC_H_

#include <stdlib.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __FUNCTION__ __func__
#ifndef NDEBUG
#define aoc_malloc(size_)          aoc_malloc_internal(size_, __FUNCTION__, __FILENAME__, __LINE__)
#define aoc_calloc(n_elem_, size_) aoc_calloc_internal(n_elem_, size_, __FUNCTION__, __FILENAME__, __LINE__)
#define aoc_realloc(ptr_, size_)   aoc_realloc_internal(ptr_, size_, __FUNCTION__, __FILENAME__, __LINE__)
#define aoc_free(ptr_)             aoc_free_internal(ptr_, __FUNCTION__, __FILENAME__, __LINE__)

void    *aoc_malloc_internal(size_t size, const char *function, const char *file, const int line);
void    *aoc_calloc_internal(size_t n_elements, size_t element_size, const char *function, const char *file, const int line);
void    *aoc_realloc_internal(void *mem_ptr, size_t new_size, const char *function, const char *file, const int line);
void     aoc_free_internal(void *mem_ptr, const char *function, const char *file, const int line);
uint64_t aoc_mem_gc(void);

#else

#define aoc_malloc(size_)          malloc(size_)
#define aoc_calloc(n_elem_, size_) calloc(n_elem_, size_)
#define aoc_realloc(ptr_, size_)   realloc(ptr_, size_)
#define aoc_free(ptr_)             free(ptr_)
#define aoc_mem_gc()               0

#endif
#endif // !__AOC_ALLOC_H_
