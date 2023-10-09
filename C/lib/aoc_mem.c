#include <glib.h>
#include <stdio.h>

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

    void *address = malloc(size);

    if(!address) {
        fprintf(fp, "(malloc) Could not allocate memory [in '%s' line: %d]\n", file, line);
        return address;
    }

    if(g_hash_table_contains(mem_alloc_table, address)) {
        fprintf(fp, "(malloc) Obtained address already allocated from somewhere\n\t[in '%s' line: %d]\n", file, line);
    } else {
        g_hash_table_add(mem_alloc_table, address);
        fprintf(fp, "(malloc) Getting %p [in '%s' line: %d]\n", address, file, line);
    }

    return address;
}

void *aoc_calloc_debug(size_t count, size_t size, char *file, int line) {
    if(!mem_alloc_table)
        aoc_mem_dbg_init();

    void *address = calloc(count, size);

    if(!address) {
        fprintf(fp, "(calloc) Could not allocate memory [in '%s' line: %d]\n", file, line);
        return address;
    }

    if(g_hash_table_contains(mem_alloc_table, address)) {
        fprintf(fp, "(calloc) Obtained address already allocated from somewhere\n\t[in '%s' line: %d]\n", file, line);
    } else {
        g_hash_table_add(mem_alloc_table, address);
        fprintf(fp, "(calloc) Getting %p [in '%s' line: %d]\n", address, file, line);
    }

    return address;
}

void *aoc_realloc_debug(void *ptr, size_t size, char *file, int line) {
    if(!mem_alloc_table)
        aoc_mem_dbg_init();

    void *old_ptr = ptr;
    void *address = realloc(ptr, size);

    if(!address) {
        fprintf(fp, "(realloc) Could not allocate memory [in '%s' line: %d]\n", file, line);
        return address;
    }

    if (old_ptr != address) {
        if(g_hash_table_contains(mem_alloc_table, address)) {
            fprintf(fp, "(realloc) Obtained address already allocated from somewhere\n\t[in '%s' line: %d]\n", file, line);
        } else {
            g_hash_table_remove(mem_alloc_table, old_ptr);
            fprintf(fp, "(realloc) Freeing up %p [in '%s' line: %d]\n", address, file, line);
            g_hash_table_add(mem_alloc_table, address);
            fprintf(fp, "(realloc) Getting %p [in '%s' line: %d]\n", address, file, line);
        }
    }
    return address;
}

void aoc_free_debug(void *address, char *file, int line) {
    if (!address)
        return;

    if (mem_alloc_table) {
        if(g_hash_table_contains(mem_alloc_table, address)) {
            g_hash_table_remove(mem_alloc_table, address);
            fprintf(fp, "(free) Freeing up %p [in '%s' line: %d]\n", address, file, line);
                    free(address);
        } else {
            fprintf(fp, "(free) Memory at %p is already free'd\n", address);
        }
    }
}

int free_key(void *key, void *value, void *data) {
    free(key);
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
        fprintf(fp, "%p\n", key);
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

