#ifndef NDEBUG

#include "aoc_hash.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocHashTable *mem_table = NULL;

static int gc_free(void *key, void *value, void *user_data) {
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "gc:      %p (size = %u)\n", key, *(int *)((char *)mem_table + sizeof(size_t) + 2 * sizeof(int)));
    fflush(stderr);
#endif
    free(key);
    return 1;
}

static void init_mem_table(void) {
    mem_table = aoc_hash_table_create(0, NULL, AOC_KEY_PTR);
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
    if (!addr) {
        return NULL;
    }

    /* Add addr to hash_table here */
    aoc_hash_table_insert(mem_table, ptr_key(addr), addr);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "malloc:  %p (size = %u) - %s - %s:%d\n", addr, aoc_hash_table_count(mem_table), function, file, line);
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
    aoc_hash_table_insert(mem_table, ptr_key(addr), addr);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "calloc:  %p (size = %u) - %s - %s:%d\n", addr, aoc_hash_table_count(mem_table), function, file, line);
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
#ifdef DEBUG_VERBOSE
void *aoc_realloc_internal(void *ptr, size_t new_size, const char *function, const char *file, int line) {
#else
void *aoc_realloc_internal(void *ptr, size_t new_size) {
#endif
    aoc_hash_table_delete(mem_table, ptr_key(ptr));
    void *addr = realloc(ptr, new_size);

    if (addr) {
        /* Add addr to hash_table here */
        aoc_hash_table_insert(mem_table, ptr_key(addr), addr);
#ifdef DEBUG_VERBOSE
        fprintf(stderr, "realloc: %p (size = %u) - %s - %s:%d\n", addr, aoc_hash_table_count(mem_table), function, file, line);
        fflush(stderr);
#endif
    } else {
        aoc_hash_table_insert(mem_table, ptr_key(ptr), ptr);
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
        aoc_hash_table_delete(mem_table, ptr_key(ptr));
#ifdef DEBUG_VERBOSE
        fprintf(stderr, "free:    %p (size = %u) - %s - %s:%d\n", ptr, aoc_hash_table_count(mem_table), function, file, line);
        fflush(stderr);
#endif
    }

    // Free the memory
    free(ptr);

    // If table is empty, free up table and set global pointer to NULL.
    if (mem_table) {
        if (aoc_hash_table_count(mem_table) == 0) {
            aoc_hash_table_destroy(mem_table);
            mem_table = NULL;
        }
    }
}

/*
 * aoc_mem_gc:
 *
 * Free up all remaining allocated but yet not free'd memory.
 * Will also destroy hash table when done.
 */
uint64_t aoc_mem_gc(void) {

    if (!(mem_table) || (aoc_hash_table_count(mem_table) == 0)) {
        return 0;
    }

    uint64_t size = aoc_hash_table_count(mem_table);
    if (size) {
        fprintf(stderr, "%" PRIu64 " elements remaining\n", size);
        fflush(stderr);
    }

    /* g_hash_table_foreach_remove(mem_table, gc_free, NULL); */
    aoc_hash_table_destroy(mem_table);
    mem_table = NULL;
    return size;
}

#endif
