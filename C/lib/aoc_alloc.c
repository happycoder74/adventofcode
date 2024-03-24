#ifdef MEMDEBUG
#define _GNU_SOURCE

#include <dlfcn.h>
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
    MemRecord *record = sys_malloc(sizeof(MemRecord));

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
void *aoc_calloc_internal(size_t n_elements, size_t element_size, const char *function,
                          const char *file, int line) {
#else
void *aoc_calloc_internal(size_t n_elements, size_t element_size) {
#endif
    MemRecord *record = sys_malloc(sizeof(MemRecord));
    void      *addr = calloc(n_elements, element_size);

#ifdef DEBUG_VERBOSE
    strncpy(record->function, function, 99);
    record->line = line;
#endif
    record->size = n_elements * element_size;
    record->ptr = addr;

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
void *aoc_realloc_internal(void *ptr, size_t new_size, const char *function, const char *file,
                           int line) {
#else
void *aoc_realloc_internal(void *ptr, size_t new_size) {
#endif
    MemRecord *record = aoc_mem_table_pop(mem_table, ptr);
#ifdef DEBUG_VERBOSE
    strncpy(record->function, function, 99);
    record->line = line;
#endif
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
        if (aoc_mem_table_count(mem_table) == 0) {
            aoc_mem_table_destroy(&mem_table);
        }
    }
}

static void report(void *key, void *value, void *data) {
    MemRecord *record = (MemRecord *)value;
    fprintf(stderr, "Address: %p (size: %u)", key, (unsigned)record->size);
#ifdef DEBUG_VERBOSE
    fprintf(stderr, " from %s:%d", record->function, record->line);
#endif
    fprintf(stderr, "\n");
}
/*
 * aoc_mem_gc:
 *
 * Free up all remaining allocated but yet not free'd memory.
 * Will also destroy hash table when done.
 */
uint64_t aoc_mem_gc(void) {

    if (!(mem_table) || (aoc_mem_table_count(mem_table) == 0)) {
        return 0;
    }

    uint64_t size = aoc_mem_table_count(mem_table);
    if (size) {
        fprintf(stderr, "%" PRIu64 " elements remaining\n", size);
    }

    aoc_mem_table_foreach(mem_table, report, NULL);
    fflush(stderr);
    /* g_hash_table_foreach_remove(mem_table, gc_free, NULL); */
    aoc_mem_table_destroy(&mem_table);
    mem_table = NULL;
    return size;
}

static AocMemTable *aoc_mem_table_create_size(size_t new_size) {
    AocMemTable *table = (AocMemTable *)sys_calloc(1, sizeof(AocMemTable));
    table->size = new_size;
    table->count = 0;
    table->elements = (MemEntry **)sys_calloc(table->size, sizeof(MemEntry *));

    return table;
}

static AocMemTable *aoc_mem_table_create(void) {
    AocMemTable *table = (AocMemTable *)sys_calloc(1, sizeof(AocMemTable));
    table->size = 17;
    table->count = 0;
    table->elements = (MemEntry **)sys_calloc(table->size, sizeof(MemEntry *));

    return table;
}

void aoc_mem_table_destroy(AocMemTable **table) {
    AocMemTable *mt = *table;

    if (!mt) {
        return;
    }

    if (mt->elements) {
        for (unsigned i = 0; i < mt->size; i++) {
            MemEntry *e = mt->elements[i];
            if (e) {
                do {
                    sys_free(e->key);
                    sys_free(e->object);
                    e = e->next;
                } while (e != NULL);
            }
        }
        sys_free(mt->elements);
    }
    sys_free(mt);
    *table = NULL;
}

static int aoc_mem_table_insert(AocMemTable *ht, const void *key, const void *obj) {
    if (!ht) {
        return 0;
    }

    MemEntry *e = NULL;
    int       key_exists = 0;

    e = aoc_mem_table_lookup_entry(ht, key);
    if (e) {
        key_exists = 1;
    } else {
        e = (MemEntry *)sys_malloc(sizeof(MemEntry));
    }

    size_t index = aoc_mem_table_index(ht, key);

    e->object = (void *)obj;
    e->key = (void *)key;
    if (!key_exists) {
        e->next = ht->elements[index];
        ht->elements[index] = e;
        ht->count += 1;
    }
    if (ht->count >= 0.75 * ht->size) {
        ht = aoc_mem_table_rehash(ht);
    }
    return !key_exists;
}

static int ptr_equal(const void *key1, const void *key2) {
    return key1 == key2;
}

static MemEntry *aoc_mem_table_lookup_entry(AocMemTable *table, const void *key) {
    if (!table) {
        return NULL;
    }

    size_t index = aoc_mem_table_index(table, key);

    MemEntry *tmp = table->elements[index];

    while (tmp != NULL && !ptr_equal(tmp->key, key)) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }
    return tmp;
}

static size_t aoc_mem_table_index(AocMemTable *table, const void *key) {
    return (uint32_t)(uint64_t)key % table->size;
}

static int is_prime(size_t number) {
    if ((number < 3) || !(number % 2)) {
        return 0;
    }

    for (size_t n = 3; n < number / 2; n += 2) {
        if (!(number % n)) {
            return 0;
        }
    }
    return 1;
}

static size_t next_prime(size_t number) {
    if (number % 2 == 0) {
        number += (int64_t)(void *)1;
    }
    size_t n = number;
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

static AocMemTable *aoc_mem_table_rehash(AocMemTable *table) {
    size_t       new_size = next_prime(table->size * 2 - 1);
    AocMemTable *ht = aoc_mem_table_create_size(new_size);

    for (size_t i = 0; i < table->size; i++) {
        MemEntry *e = table->elements[i];
        if (e != NULL) {
            do {
                void *key = e->key;
                void *value = e->object;
                aoc_mem_table_insert(ht, key, value);
                e = e->next;
            } while (e != NULL);
        }
    }
    sys_free(table->elements);

    table->size = ht->size;
    table->count = ht->count;
    table->elements = ht->elements;

    sys_free(ht);

    return table;
}

static void *aoc_mem_table_pop(AocMemTable *table, const void *key) {
    if (!table) {
        return NULL;
    }

    if (!aoc_mem_table_lookup_entry(table, key)) {
        return NULL;
    }

    size_t index = aoc_mem_table_index(table, key);

    MemEntry *tmp = table->elements[index];
    MemEntry *prev = NULL;

    while (tmp != NULL && !ptr_equal(tmp->key, key)) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }

    if (prev == NULL) {
        // deleting the head of the list
        table->elements[index] = tmp->next;
    } else {
        // deleting elsewhere
        prev->next = tmp->next;
    }

    table->count -= 1;
    void *result = tmp->object;
    sys_free(tmp);

    return result;
}

static unsigned aoc_mem_table_count(AocMemTable *table) {
    if (!table) {
        return 0;
    }
    return table->count;
}

static void aoc_mem_table_delete(AocMemTable *table, const void *key) {
    if (!table) {
        return;
    }

    if (!aoc_mem_table_lookup_entry(table, key)) {
        return;
    }
    size_t index = aoc_mem_table_index(table, key);

    MemEntry *tmp = table->elements[index];
    MemEntry *prev = NULL;

    while (tmp != NULL && !ptr_equal(tmp->key, key)) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return;
    }

    if (prev == NULL) {
        // deleting the head of the list
        table->elements[index] = tmp->next;
    } else {
        // deleting elsewhere
        prev->next = tmp->next;
    }
    sys_free(tmp);

    table->count -= 1;

    return;
}

static void aoc_mem_table_foreach(AocMemTable *table, AocMemTableFunc func, void *user_data) {
    for (unsigned idx = 0; idx < table->size; idx++) {
        MemEntry *e = table->elements[idx];
        if (e != NULL) {
            do {
                func(e->key, e->object, user_data);
                e = e->next;
            } while (e != NULL);
        }
    }
}
#endif
