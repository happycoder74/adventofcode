#include "aoc_hash.h"
#include "glib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

GHashTable *mem_table = NULL;

static void init_mem_table(void) {
    mem_table = g_hash_table_new(g_direct_hash, g_direct_equal);
}

static void gc_free(void *key, void *value, void *user_data) {
    fprintf(stderr, "gc:      %p (size = %u)\n", value, g_hash_table_size(mem_table));

    // free(value);
    return;
}

void *aoc_malloc(size_t size) {
    if (!mem_table)
        init_mem_table();

    void *addr = malloc(size);
    if (!addr)
        return NULL;

    /* Add addr to hash_table here */
    g_hash_table_add(mem_table, addr);
    fprintf(stderr, "malloc:  %p (size = %u)\n", addr, g_hash_table_size(mem_table));

    return addr;
}

void *aoc_calloc(size_t n_elements, size_t element_size) {
    void *addr = calloc(n_elements, element_size);

    if (!addr)
        return NULL;

    /* Add addr to hash_table here */
    g_hash_table_add(mem_table, addr);
    fprintf(stderr, "calloc:  %p (size = %u)\n", addr, g_hash_table_size(mem_table));

    return addr;
}

void *aoc_realloc(void *orig, size_t new_size) {

    g_hash_table_remove(mem_table, orig);
    void *addr = realloc(orig, new_size);

    if (addr) {
        /* Add addr to hash_table here */
        g_hash_table_add(mem_table, addr);
        fprintf(stderr, "realloc: %p (size = %u)\n", addr, g_hash_table_size(mem_table));
    }

    return addr;
}

void aoc_free(void *ptr) {
    /* Delete ptr from mem_table if present */
    g_hash_table_remove(mem_table, ptr);
    fprintf(stderr, "free:    %p (size = %u)\n", ptr, g_hash_table_size(mem_table));

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
    g_hash_table_foreach(mem_table, gc_free, NULL);
    g_hash_table_destroy(mem_table);
    mem_table = NULL;
    return size;
}
