#ifndef NDEBUG

#include "aoc_hash.h"
#include "glib.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _MemRecord {
    char   function[100];
    int    line;
    size_t size;
    void  *ptr;
} MemRecord;

typedef struct entry {
    struct entry *next;
    void         *key;
    void         *object;
} MemEntry;

typedef struct {
    uint32_t   size;
    uint32_t   count;
    MemEntry **elements;
} AocMemTable;

typedef void (*AocMemTableFunc)(void *, void *, void *);
static AocMemTable *aoc_mem_table_create(void);
static AocMemTable *aoc_mem_table_create_size(size_t);
static void        *aoc_mem_table_pop(AocMemTable *, const void *);
static int          aoc_mem_table_insert(AocMemTable *, const void *, const void *);
static unsigned     aoc_mem_table_count(AocMemTable *);
static void         aoc_mem_table_delete(AocMemTable *, const void *);
static void         aoc_mem_table_destroy(AocMemTable **);
static void         aoc_mem_table_foreach(AocMemTable *, AocMemTableFunc func, void *);
static MemEntry    *aoc_mem_table_lookup_entry(AocMemTable *, const void *);
static size_t       aoc_mem_table_index(AocMemTable *, const void *);
static AocMemTable *aoc_mem_table_rehash(AocMemTable *);

AocMemTable *mem_table = NULL;

typedef void *(*malloc_function)(size_t);
typedef void (*free_function)(void *);
typedef void *(*calloc_function)(size_t, size_t);
typedef void *(*realloc_function)(void *, size_t);

static free_function    sys_free = NULL;
static malloc_function  sys_malloc = NULL;
static calloc_function  sys_calloc = NULL;
static realloc_function sys_realloc = NULL;

void init_mem_table(void) {
    if (mem_table) {
        return;
    }
    if (!sys_malloc) {
        sys_malloc = (malloc_function)dlsym(RTLD_NEXT, "malloc");
    }
    if (!sys_calloc) {
        sys_calloc = (calloc_function)dlsym(RTLD_NEXT, "calloc");
    }
    if (!sys_realloc) {
        sys_realloc = (realloc_function)dlsym(RTLD_NEXT, "realloc");
    }
    if (!sys_free) {
        sys_free = (free_function)dlsym(RTLD_NEXT, "free");
    }
    mem_table = aoc_mem_table_create();
}

void *malloc(size_t size) {
    if (!sys_malloc) {
        sys_malloc = (malloc_function)dlsym(RTLD_NEXT, "malloc");
    }
    void *alloc = sys_malloc(size);

    return alloc;
}

void *calloc(size_t count, size_t size) {
    if (!sys_calloc) {
        sys_calloc = (calloc_function)dlsym(RTLD_NEXT, "calloc");
    }
    void *alloc = sys_calloc(count, size);

    return alloc;
}

void *realloc(void *ptr, size_t size) {
    if (!sys_realloc) {
        sys_realloc = (realloc_function)dlsym(RTLD_NEXT, "realloc");
    }
    void *alloc = sys_realloc(ptr, size);

    return alloc;
}

void free(void *ptr) {
    if (!sys_free) {
        sys_free = (free_function)dlsym(RTLD_NEXT, "free");
    }
    if (!ptr) {
        return;
    }
    sys_free(ptr);
}

/**
 * aoc_malloc_internal:
 * @param size: memory size requested
 * @param element_size: size of each element
 * @param function: name of calling function
 * @param file: filename of file where call is made
 * @param line: line number in file where call is made
 *
 * Forwards size to malloc.
 * Add address to memory table unless NULL is returned.
 * If DEBUG_VERBOSE is defined the details is logged to stderr.
 */
#ifdef DEBUG_VERBOSE
void *aoc_malloc_internal(size_t size, const char *function, const char *file, int line) {
#else
void *aoc_malloc_internal(size_t size) {
#endif
    if (!mem_table) {
        init_mem_table();
    }

    void *addr = malloc(size);

#ifdef DEBUG_VERBOSE
    strncpy(record->function, function, 99);
    record->line = line;
#endif
    record->size = size;
    record->ptr = addr;

    if (!addr) {
        return NULL;
    }

    /* Add addr to hash_table here */
    aoc_mem_table_insert(mem_table, addr, record);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "malloc:  %p (size = %u) - %s - %s:%d\n", addr, aoc_mem_table_count(mem_table),
            function, file, line);
    fflush(stderr);
#endif
    return addr;
}

/*
 * aoc_calloc_internal:
 * @n_elements: number of elements to allocate
 * @element_size: size of each element
 * @function: name of calling function
 * @file: filename of file where call is made
 * @line: line number in file where call is made
 *
 * Forwards n_elements and element_size to calloc.
 * Add address to memory table unless NULL is returned.
 * If DEBUG_VERBOSE is defined the details is logged to stderr.
 */
#ifdef DEBUG_VERBOSE
void *aoc_calloc_internal(size_t n_elements, size_t element_size, const char *function, const char *file, int line) {
#else
void *aoc_calloc_internal(size_t n_elements, size_t element_size) {
#endif
    void *addr = calloc(n_elements, element_size);

    if (!addr) {
        return NULL;
    }

    /* Add addr to hash_table here */
    aoc_mem_table_insert(mem_table, addr, record);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "calloc:  %p (size = %u) - %s - %s:%d\n", addr, aoc_mem_table_count(mem_table),
            function, file, line);
    fflush(stderr);
#endif

    return addr;
}

/*
 * aoc_realloc_internal:
 * @ptr: pointer to memory to reallocate. If ptr == NULL then behave like malloc(new_size).
 * @new_size: new size to request
 * @function: name of calling function
 * @file: filename of file where call is made
 * @line: line number in file where call is made
 *
 * Removes the old address from the allocation table
 * and add the new returned from realloc. If NULL is returned
 * (meaning realloc failed) the old ptr is added to the memory table.
 * If DEBUG_VERBOSE is defined the details is logged to stderr.
 */
#ifdef DEBUG_VERBOSE
void *aoc_realloc_internal(void *ptr, size_t new_size, const char *function, const char *file, int line) {
#else
void *aoc_realloc_internal(void *ptr, size_t new_size) {
#endif
    g_hash_table_remove(mem_table, ptr);
    void *addr = realloc(ptr, new_size);

    if (addr) {
        record->size = new_size;
        record->ptr = addr;
        aoc_mem_table_insert(mem_table, addr, record);
#ifdef DEBUG_VERBOSE
        fprintf(stderr, "realloc: %p (size = %u) - %s - %s:%d\n", addr,
                aoc_mem_table_count(mem_table), function, file, line);
        fflush(stderr);
#endif
    } else {
        aoc_mem_table_insert(mem_table, ptr, record);
    }

    return addr;
}

/*
 * aoc_free_internal:
 * @ptr: pointer to memory to free
 * @function: name of calling function
 * @file: filename of file where call is made
 * @line: line number in file where call is made
 *
 * Removes the address from the allocation table and if DEBUG_VERBOSE is
 * defined the details is logged to stderr.
 */
#ifdef DEBUG_VERBOSE
void aoc_free_internal(void *ptr, const char *function, const char *file, int line) {
#else
void aoc_free_internal(void *ptr) {
#endif
    /* Delete ptr from mem_table if present */
    if (mem_table) {
        g_hash_table_remove(mem_table, ptr);
    }
#ifdef DEBUG_VERBOSE
void aoc_free_internal(void *ptr, const char *function, const char *file, int line) {
#else
void aoc_free_internal(void *ptr) {
#endif
    /* Delete ptr from mem_table if present */
    if (mem_table) {
        aoc_mem_table_delete(mem_table, ptr);
#ifdef DEBUG_VERBOSE
        fprintf(stderr, "free:    %p (size = %u) - %s - %s:%d\n", ptr,
                aoc_mem_table_count(mem_table), function, file, line);
        fflush(stderr);
#endif
    }

    // Free the memory
    free(ptr);

    // If table is empty, free up table and set global pointer to NULL.
    if (mem_table) {
        if (g_hash_table_size(mem_table) == 0) {
            g_hash_table_destroy(mem_table);
            mem_table = NULL;
        }
    }
}

static void report(void *key, void *value, void *data) {
    MemRecord *record = (MemRecord *)value;
    uint32_t  *counter = (uint32_t *)data;
    fprintf(stderr, "[%3d]: Address: %p (size: %u)", *counter, key, (unsigned)record->size);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, " from %s:%d", record->function, record->line);
#endif
    fprintf(stderr, "\n");

    *counter += 1;
}
/*
 * aoc_mem_gc:
 *
 * Free up all remaining allocated but yet not free'd memory.
 * Will also destroy hash table when done.
 */
static uint32_t counter = 0;
uint64_t        aoc_mem_gc(void) {

    if (!(mem_table) || (aoc_mem_table_count(mem_table) == 0)) {
        return 0;
    }

    uint64_t size = aoc_mem_table_count(mem_table);
    if (size) {
        fprintf(stderr, "%" PRIu64 " elements remaining\n", size);
    }

    aoc_mem_table_foreach(mem_table, report, &counter);
    fflush(stderr);
    /* g_hash_table_foreach_remove(mem_table, gc_free, NULL); */
    aoc_mem_table_destroy(&mem_table);
    mem_table = NULL;
    return EXIT_FAILURE;
}

#endif
