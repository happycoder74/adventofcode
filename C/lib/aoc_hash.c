#include "aoc_hash.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct entry {
    struct entry *next;
    void *object;
} entry;

typedef struct {
    struct entry head;
    int32_t key;
} int32_entry;

typedef struct {
    struct entry head;
    int64_t key;
} int64_entry;

typedef struct {
    struct entry head;
    uint32_t key;
} uint32_entry;

typedef struct {
    struct entry head;
    uint64_t key;
} uint64_entry;

typedef enum {
    AOC_HASH_INT32,
    AOC_HASH_UINT32,
    AOC_HASH_INT64,
    AOC_HASH_UINT64,
    AOC_HASH_COUNT
} AocHashType;

struct _aoc_hash_table {
    AocHashType type;
    uint32_t size;
    entry **elements;
};

typedef struct {
    struct _aoc_hash_table head;
    int32_hashfunction hash;
} AocInt32HashTable;

static size_t aoc_int32_hash_table_index(AocHashTable *hashtable, const int32_t key) {
    AocInt32HashTable *ht = (AocInt32HashTable *)hashtable;
    size_t result = (ht->hash(key) % ht->head.size);
    return result;
}

AocHashTablePtr aoc_int32_hash_table_create(uint32_t size, int32_hashfunction hf) {
    AocInt32HashTable *ht = (AocInt32HashTable *)malloc(sizeof(*ht));
    ht->head.size = size;
    ht->hash = hf;

    ht->head.elements = calloc(sizeof(entry *), ht->head.size);
    return (AocHashTablePtr) ht;
}

void aoc_int32_hash_table_destroy(AocHashTable *hashtable) {
    AocInt32HashTable *ht = (AocInt32HashTable *)hashtable;

    if (ht) {
      if (ht->head.elements) {
        free(ht->head.elements);
      }

      free(ht);
    }
}

bool aoc_int32_hash_table_insert(AocHashTable *ht, const int32_t key, const void *obj) {
    if (!ht)
        return false;

    if (aoc_int32_hash_table_lookup(ht, key))
        return false;

    if (!obj) {
        return false;
    }

    size_t index  = aoc_int32_hash_table_index(ht, key);

    if (aoc_int32_hash_table_lookup(ht, key) != NULL) return false;

    // create a new entry

    int32_entry *e = malloc(sizeof(*e));
    e->head.object = (void *)obj;
    e->key = key;

    // insert our entry
    e->head.next = ht->elements[index];
    ht->elements[index] = (entry *)e;
    return true;
}

void *aoc_int32_hash_table_lookup(AocHashTablePtr ht, const int32_t key) {
    if (!ht)
        return false;

    size_t index  = aoc_int32_hash_table_index(ht, key);

    int32_entry *tmp = (int32_entry *)ht->elements[index];
    while (tmp != NULL && (tmp->key != key)) {
        tmp = (int32_entry *)tmp->head.next;
    }
    if (tmp == NULL) return NULL;
    return tmp->head.object;
}

void *aoc_int32_hash_table_delete(AocHashTablePtr ht, const int32_t key) {
    if (!ht)
        return false;

    if (aoc_int32_hash_table_lookup(ht, key))
        return false;

    size_t index  = aoc_int32_hash_table_index(ht, key);

    int32_entry *tmp = (int32_entry *)ht->elements[index];
    int32_entry *prev = NULL;

    while (tmp != NULL && (tmp->key != key)) {
        prev = tmp;
        tmp = (int32_entry *)tmp->head.next;
    }
    if (tmp == NULL) return NULL;

    if (prev == NULL) {
        // deleting the head of the list
        ht->elements[index] = tmp->head.next;
    } else {
        // deleting elsewhere
        prev->head.next = tmp->head.next;
    }
    void *result = tmp->head.object;
    free(tmp);
    return result;
}
