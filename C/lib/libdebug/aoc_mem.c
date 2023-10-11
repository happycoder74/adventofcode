#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>

#include "aoc_types.h"
#include "aoc_array.h"

GHashTable *mem_alloc_table = NULL;
FILE *fp = NULL;

typedef struct {
    char message[301];
    char allocator[100];
    char function[50];
    char file[200];
    int line;
} LogMessage_t;

void aoc_mem_dbg_init(int year, int day) {
    mem_alloc_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    char filename[100];

    sprintf(filename, "aoc_%4d_%02d_allocation.log", year, day);
    fp = fopen(filename, "w");
    fprintf(fp, "Allocation log for %4d/%02d:\n", year, day);
    fflush(fp);
}

void aoc_mem_dbg_destroy(void) {
    if (mem_alloc_table)
        g_hash_table_destroy(mem_alloc_table);

}

static LogMessage_t *create_log_message(const char *allocator, const char *function, const char *file, int line) {
    LogMessage_t *msg = (LogMessage_t *)malloc(sizeof(LogMessage_t));
    snprintf(msg->allocator, 100, allocator);
    snprintf(msg->function, 50, function);
    snprintf(msg->file, 200, "%s", (char *)(strrchr(file, '/')) + 1);
    msg->line = line;
    snprintf(msg->message, 300, "[%s in {%s}:'%s':%d]", msg->allocator, msg->function, msg->file, msg->line);

    return msg;
}

static void aoc_allocator_debug(LogMessage_t *msg, void *address) {
    if(!address) {
        fprintf(fp, "(%s) Could not allocate memory %s\n", msg->allocator, msg->message);
        fflush(fp);
        return;
    }

    if(g_hash_table_contains(mem_alloc_table, address)) {
        LogMessage_t *value = (LogMessage_t *)g_hash_table_lookup(mem_alloc_table, address);
        if (strcmp("realloc", msg->allocator)) {
            fprintf(fp, "(%s) %#08llx already allocated from %s\n\t%s\n", msg->allocator, (uint64_t)address, value->message, msg->message);
            fflush(fp);
        }
    } else {
        g_hash_table_insert(mem_alloc_table, address, msg);
        fprintf(fp, "(%s) %#08llx %s\n", msg->allocator, (uint64_t)address, msg->message);
        fflush(fp);
    }
}

void *aoc_malloc_debug(size_t size, const char *function, const char *file, const int line) {

    void *address = malloc(size);
    LogMessage_t *msg = create_log_message("malloc", function, file, line);
    aoc_allocator_debug(msg, address);
    return address;
}

void *aoc_calloc_debug(size_t count, size_t size, const char *function, const char *file, const int line) {
    void *address = calloc(count, size);
    LogMessage_t *msg = create_log_message("malloc", function, file, line);
    aoc_allocator_debug(msg, address);
    return address;
}

void *aoc_realloc_debug(void *ptr, size_t size, const char *function, const char *file, const int line) {
    uint64_t old_ptr = (uint64_t)ptr;
    LogMessage_t *msg = create_log_message("realloc", function, file, line);

    void *address = realloc(ptr, size);
    if (old_ptr != (uint64_t)address) {
        if(g_hash_table_contains(mem_alloc_table, address)) {
            LogMessage_t *value = g_hash_table_lookup(mem_alloc_table, address);
            fprintf(fp, "(%s) %#08llx already allocated from %s:'%s':%d\n", "realloc", (uint64_t)address, value->allocator, value->file, value->line);
        } else {
            g_hash_table_remove(mem_alloc_table, (void *)old_ptr);
            fprintf(fp, "(%s) Releasing %#08llx\n", msg->allocator, (uint64_t)old_ptr);
        }
    }

    aoc_allocator_debug(msg, address);
    return address;
}


void aoc_free_debug(void *address, const char *function, const char *file, const int line) {
    if ((!address) || (!mem_alloc_table))
        return;

    LogMessage_t *msg = create_log_message("free", function, file, line);

    if(g_hash_table_contains(mem_alloc_table, address)) {
        LogMessage_t *value = g_hash_table_lookup(mem_alloc_table, address);
        fprintf(fp, "(%s) %#08llx from (%s):'%s':%d | %s\n", msg->allocator, (uint64_t)address, value->allocator, value->file, value->line, msg->message);
        fflush(fp);
        g_hash_table_remove(mem_alloc_table, address);
        free(value);
        free(address);
    } else {
        fprintf(fp, "(%-16s) Memory at %p is already free'd or allocated outside of memdebug scope%s\n", msg->allocator, address, msg->message);
        fflush(fp);
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

    g_hash_table_destroy(mem_alloc_table);

    mem_alloc_table = NULL;
}

void *aoc_array_append_debug(AocArrayPtr array, void *value, const char *function, const char *file, const int line) {
    fprintf(fp, "(aoc_array_append) called from {%s}:'%s' line: %d]", function, file, line);

    return aoc_array_append(array, value);
}
extern void *aoc_array_new_mangle(AocArrayType, size_t);

void *aoc_array_new_debug(AocArrayType type, size_t size, const char *function, const char *file, const int line) {
    fprintf(fp, "(aoc_array_new) called from {%s}:'%s' line: %d]", function, file, line);

    return aoc_array_new(type, size);
}


void *g_hash_table_new_mem_debug(unsigned int (*hash_func)(const void *), int (*eq_func)(const void *, const void *), const char *function, const char *file, const int line) {
    char *message = NULL;
    message = (char *)malloc(sizeof(char)*200);
    sprintf(message, "[g_hash_table_new in {%s}:'%s' line: %d]", function, file, line);

    void *address = g_hash_table_new(hash_func, eq_func);

    if(!address) {
        fprintf(fp, "(g_hash_table_new) Could not allocate memory %s\n", message);
        return address;
    }

    if(g_hash_table_contains(mem_alloc_table, address)) {

        fprintf(fp, "(g_hash_table_new) Obtained address already allocated from %s\n\t%s\n",(char *)g_hash_table_lookup(mem_alloc_table, address), message);
    } else {
        g_hash_table_insert(mem_alloc_table, address, message);
        fprintf(fp, "(g_hash_table_new) Getting %p %s\n", address, message);
    }

    return address;

}

void g_hash_table_destroy_mem_debug(void *address, const char *function, const char *file, const int line) {
    if (!address)
        return;

    char message[200];
    sprintf(message, "[g_hash_table_destroy in {%s}:'%s' line: %d]", function, file, line);

    if (mem_alloc_table) {
        if(g_hash_table_contains(mem_alloc_table, address)) {
            void *value = g_hash_table_lookup(mem_alloc_table, address);
            free(value);
            g_hash_table_remove(mem_alloc_table, address);
            fprintf(fp, "(g_hash_table_destroy) Freeing up %p %s\n", address, message);
            g_hash_table_destroy(address);
        } else {
            fprintf(fp, "(g_hash_table_destroy) Memory at %p is already free'd %s\n", address, message);
        }
    }

}
