#include "aoc_hash.h"
#include "glib.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

GHashTable *mem_table = NULL;

static int gc_free(void *key, void *value, void *user_data) {
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "gc:      %p (size = %u)\n", key, *(int *)((char *)mem_table + sizeof(gsize) + 2 * sizeof(int)));
    fflush(stderr);
#endif
    free(key);
    return 1;
}

static void init_mem_table(void) {
    mem_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
}

/*
 * aoc_malloc_internal:
 * @size: memory size requested
 * @element_size: size of each element
 * @function: name of calling function
 * @file: filename of file where call is made
 * @line: line number in file where call is made
 *
 * Forwards size to malloc.
 * Add address to memory table unless NULL is returned.
 * If DEBUG_VERBOSE is defined the details is logged to stderr.
 */
void *aoc_malloc_internal(size_t size, const char *function, const char *file, int line) {
    if (!mem_table)
        init_mem_table();

    void *addr = malloc(size);
    if (!addr)
        return NULL;

    /* Add addr to hash_table here */
    g_hash_table_add(mem_table, addr);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "malloc:  %p (size = %u) - %s - %s:%d\n", addr, g_hash_table_size(mem_table), function, file, line);
    fflush(stderr);
#endif
    return addr;
}

/*
 * aoc_calloc_internal:
 * @n_elements: pointer to memory reallocate
 * @new_size: new size to request
 * @element_size: size of each element
 * @function: name of calling function
 * @file: filename of file where call is made
 * @line: line number in file where call is made
 *
 * Forwards n_elements and element_size to calloc.
 * Add address to memory table unless NULL is returned.
 * If DEBUG_VERBOSE is defined the details is logged to stderr.
 */
void *aoc_calloc_internal(size_t n_elements, size_t element_size, const char *function, const char *file, int line) {
    void *addr = calloc(n_elements, element_size);

    if (!addr)
        return NULL;

    /* Add addr to hash_table here */
    g_hash_table_add(mem_table, addr);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "calloc:  %p (size = %u) - %s - %s:%d\n", addr, g_hash_table_size(mem_table), function, file, line);
    fflush(stderr);
#endif

    return addr;
}

/*
 * aoc_realloc_internal:
 * @ptr: pointer to memory reallocate
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
void *aoc_realloc_internal(void *ptr, size_t new_size, const char *function, const char *file, int line) {
    g_hash_table_remove(mem_table, ptr);
    void *addr = realloc(ptr, new_size);

    if (addr) {
        /* Add addr to hash_table here */
        g_hash_table_add(mem_table, addr);
#ifdef DEBUG_VERBOSE
        fprintf(stderr, "realloc: %p (size = %u) - %s - %s:%d\n", addr, g_hash_table_size(mem_table), function, file, line);
        fflush(stderr);
#endif
    } else {
        g_hash_table_add(mem_table, orig);
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
void aoc_free_internal(void *ptr, const char *function, const char *file, int line) {
    /* Delete ptr from mem_table if present */
    g_hash_table_remove(mem_table, ptr);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "free:    %p (size = %u) - %s - %s:%d\n", ptr, g_hash_table_size(mem_table), function, file, line);
    fflush(stderr);
#endif

    // Free the memory
    free(ptr);

    // If table is empty, free up table and set global pointer to NULL.
    if (g_hash_table_size(mem_table) == 0) {
        g_hash_table_destroy(mem_table);
        mem_table = NULL;
    }
}

/*
 * aoc_mem_gc:
 *
 * Free up all remaining allocated but yet not free'd memory.
 * Will also destroy hash table when done.
 */
uint64_t aoc_mem_gc(void) {

    if (!(mem_table) || (g_hash_table_size(mem_table) == 0)) {
        return 0;
    }

    uint64_t size = g_hash_table_size(mem_table);
    if (size) {
        fprintf(stderr, "%" PRIu64 " elements remaining\n", size);
        fflush(stderr);
    }

    g_hash_table_foreach_remove(mem_table, gc_free, NULL);
    g_hash_table_destroy(mem_table);
    mem_table = NULL;
    return size;
}
