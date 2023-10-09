#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include "aoc_types.h"
#include "aoc_array.h"

GHashTable *mem_alloc_table = NULL;
FILE *fp = NULL;

static void aoc_mem_dbg_init(void) {
    mem_alloc_table = g_hash_table_new(g_direct_hash, g_direct_equal);
    fp = fopen("allocation.log", "w");
}

void aoc_mem_dbg_destroy(void) {
    if (mem_alloc_table)
        g_hash_table_destroy(mem_alloc_table);

}

void *aoc_malloc_debug(size_t size, char *file, int line) {
    if(!mem_alloc_table)
        aoc_mem_dbg_init();
    char *message = NULL;
    message = (char *)malloc(sizeof(char)*200);
    sprintf(message, "[malloc in '%s' line: %d]", file, line);

    void *address = malloc(size);

    if(!address) {
        fprintf(fp, "(malloc) Could not allocate memory %s\n", message);
        return address;
    }

    if(g_hash_table_contains(mem_alloc_table, address)) {

        fprintf(fp, "(malloc) Obtained address already allocated from %s\n\t%s\n",(char *)g_hash_table_lookup(mem_alloc_table, address), message);
    } else {
        g_hash_table_insert(mem_alloc_table, address, message);
        fprintf(fp, "(malloc) Getting %p %s\n", address, message);
    }

    return address;
}

void *aoc_calloc_debug(size_t count, size_t size, char *file, int line) {
    if(!mem_alloc_table)
        aoc_mem_dbg_init();
    char *message = NULL;
    message = (char *)malloc(sizeof(char)*200);
    sprintf(message, "[calloc in '%s' line: %d]", file, line);

    void *address = calloc(count, size);

    if(!address) {
        fprintf(fp, "(calloc) Could not allocate memory %s\n", message);
        return address;
    }

    if(g_hash_table_contains(mem_alloc_table, address)) {
        fprintf(fp, "(calloc) Obtained address already allocated from %s\n\t%s\n", (char *)g_hash_table_lookup(mem_alloc_table, address), message);
    } else {
        g_hash_table_insert(mem_alloc_table, address, message);
        fprintf(fp, "(calloc) Getting %p %s\n", address, message);
    }

    return address;
}

void *aoc_realloc_debug(void *ptr, size_t size, char *file, int line) {
    if(!mem_alloc_table)
        aoc_mem_dbg_init();

    char *message = NULL;
    message = (char *)malloc(sizeof(char)*200);
    sprintf(message, "[realloc in '%s' line: %d]", file, line);

    uint64_t old_ptr = (uint64_t)ptr;
    void *address = realloc(ptr, size);

    if(!address) {
        fprintf(fp, "(realloc) Could not allocate memory %s\n", message);
        return address;
    }

    if ((void *)old_ptr != address) {
        if(g_hash_table_contains(mem_alloc_table, address)) {
            fprintf(fp, "(realloc) Obtained address already allocated from %s\n\t%s\n", (char *)g_hash_table_lookup(mem_alloc_table, address), message);
        } else {
            g_hash_table_remove(mem_alloc_table, (void *)old_ptr);
            fprintf(fp, "(realloc) Freeing up %p %s\n", address, message);
            g_hash_table_insert(mem_alloc_table, address, message);
            fprintf(fp, "(realloc) Getting %p %s\n", address, message);
        }
    }
    return address;
}

void aoc_free_debug(void *address, char *file, int line) {
    if (!address)
        return;

    char message[200];
    sprintf(message, "[free in '%s' line: %d]", file, line);

    if (mem_alloc_table) {
        if(g_hash_table_contains(mem_alloc_table, address)) {
            void *value = g_hash_table_lookup(mem_alloc_table, address);
            free(value);
            g_hash_table_remove(mem_alloc_table, address);
            fprintf(fp, "(free) Freeing up %p %s\n", address, message);
                    free(address);
        } else {
            fprintf(fp, "(free) Memory at %p is already free'd %s\n", address, message);
        }
    }
}

int free_key(void *key, void *value, void *data) {
    free(key);
    free(value);

    return TRUE;
}

void aoc_mem_report_debug(void) {
    if (!mem_alloc_table) {
        printf("No alloc table defined\n");
        return;
    }

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init (&iter, mem_alloc_table);
    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        fprintf(fp, "%p allocated by %s\n", key, (char *)value);
    }
}

void aoc_mem_wrap_up(void) {
    if(!mem_alloc_table)
        return;

    if (g_hash_table_size(mem_alloc_table) != 0) {
        fprintf(stderr, "%d allocations are not released at end of program\n", g_hash_table_size(mem_alloc_table));
        fprintf(fp, "Remaining allocated memory:\n");
        aoc_mem_report_debug();
    }
    g_hash_table_foreach_remove(mem_alloc_table, free_key, NULL);
    g_hash_table_destroy(mem_alloc_table);

    mem_alloc_table = NULL;
}

void *aoc_array_append_debug(AocArrayPtr array, void *value, char *file, int line) {
    fprintf(fp, "(aoc_array_append) called from %s line %d\n", file, line);

    return aoc_array_append(array, value);
}
extern void *aoc_array_new_mangle(AocArrayType, size_t);

void *aoc_array_new_debug(AocArrayType type, size_t size, char *file, int line) {
    fprintf(fp, "(aoc_array_new) called from %s line %d\n", file, line);

    return aoc_array_new_mangle(type, size);
}
