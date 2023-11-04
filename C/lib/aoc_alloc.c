#include "aoc_hash.h"
#include "glib.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

GHashTable *mem_table = NULL;

static void gc_free(void *key) {
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "gc:      %p (size = %u)\n", key, *(int *)((char *)mem_table + sizeof(gsize) + 2 * sizeof(int)));
    fflush(stderr);
#endif
    free(key);
    return;
}

static void init_mem_table(void) {
    mem_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, gc_free, NULL);
}

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

void *aoc_realloc_internal(void *orig, size_t new_size, const char *function, const char *file, int line) {
    g_hash_table_remove(mem_table, orig);
    void *addr = realloc(orig, new_size);

    if (addr) {
        /* Add addr to hash_table here */
        g_hash_table_add(mem_table, addr);
#ifdef DEBUG_VERBOSE
        fprintf(stderr, "realloc: %p (size = %u) - %s - %s:%d\n", addr, g_hash_table_size(mem_table), function, file, line);
        fflush(stderr);
#endif
    }

    return addr;
}

void aoc_free_internal(void *ptr, const char *function, const char *file, int line) { /* Delete ptr from mem_table if present */
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

uint64_t aoc_mem_gc(void) {

    if (!(mem_table) || (g_hash_table_size(mem_table) == 0)) {
        return 0;
    }

    uint64_t size = g_hash_table_size(mem_table);
    if (size) {
        fprintf(stderr, "%" PRIu64 " elements remaining\n", size);
        fflush(stderr);
    }
    g_hash_table_destroy(mem_table);
    mem_table = NULL;
    return size;
}
