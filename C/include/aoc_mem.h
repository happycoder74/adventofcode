#ifndef __AOC_MEM_H__
#define __AOC_MEM_H__

#ifndef NDEBUG

#define free(_addr_)    aoc_free_debug(_addr_, __FILE__, __LINE__)
#define malloc(_size_)  aoc_malloc_debug(_size_, __FILE__, __LINE__)
#define calloc(_count_, _size_)  aoc_calloc_debug(_count_, _size_, __FILE__, __LINE__)
#define realloc(_ptr_, _size_)  aoc_realloc_debug(_ptr_, _size_, __FILE__, __LINE__)

void aoc_free_debug(void *, char *, int);
void *aoc_malloc_debug(size_t, char *, int);
void *aoc_calloc_debug(size_t, size_t, char *, int);
void *aoc_realloc_debug(void *, size_t, char *, int);
void aoc_mem_report_debug(void);
void aoc_mem_wrap_up(void);

#endif

#endif // !__AOC_MEM_H__
