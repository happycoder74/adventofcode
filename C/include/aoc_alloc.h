#ifndef __AOC_ALLOC_H_
#define __AOC_ALLOC_H_

#include <stdint.h>
#include <stdlib.h>

void    *aoc_malloc(size_t size);
void    *aoc_calloc(size_t n_elements, size_t element_size);
void    *aoc_realloc(void *mem_ptr, size_t new_size);
void     aoc_free(void *mem_ptr);
uint64_t aoc_mem_gc(void);

#endif // !__AOC_ALLOC_H_
