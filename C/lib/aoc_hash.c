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
    uint32_t count;
    entry **elements;
};

typedef struct {
    struct _aoc_hash_table head;
    int32_hashfunction hash;
    int32_t *keys;
} AocInt32HashTable;

static int is_prime(size_t number) {
    if ((number < 3))
        return 0;

    if (!(number % 2))
        return 0;

    for (size_t n = 3; n < number / 2; n += 2) {
        if (!(number % n))
            return 0;
    }
    return 1;
}

static size_t next_prime(size_t number) {
    if (number % 2 == 0)
        number += 1;
    size_t n = number;
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

static size_t aoc_int32_hash_table_index(AocHashTable *hashtable, const int32_t key) {
    AocInt32HashTable *ht = (AocInt32HashTable *)hashtable;
    size_t result = (ht->hash(key) % ht->head.size);
    return result;
}

static AocHashTablePtr aoc_int32_hash_table_rehash(AocHashTablePtr hashtable) {
    size_t new_size = next_prime(hashtable->size + 1);
    AocHashTablePtr ht = aoc_int32_hash_table_create(new_size, ((AocInt32HashTable *)hashtable)->hash);

    int32_t *keys = ((AocInt32HashTable *)hashtable)->keys;
    for(size_t i = 0; i < hashtable->count; i++) {
        void *value = aoc_int32_hash_table_lookup(hashtable, keys[i]);
        aoc_int32_hash_table_insert(ht, keys[i], value);
    }

    free(keys);
    hashtable->type = ht->type;
    hashtable->elements = ht->elements;
    hashtable->size = ht->size;
    hashtable->count = ht->count;
    ((AocInt32HashTable *)hashtable)->keys = ((AocInt32HashTable *)ht)->keys;
    ((AocInt32HashTable *)hashtable)->hash = ((AocInt32HashTable *)ht)->hash;

    free(ht);

    return hashtable;
}

AocHashTablePtr aoc_int32_hash_table_create(uint32_t size, int32_hashfunction hf) {
    AocInt32HashTable *ht = (AocInt32HashTable *)malloc(sizeof(*ht));
    ht->head.size = size <= 17 ? 17 : next_prime(size);
    ht->head.count = 0;
    ht->hash = hf;
    ht->keys = (int32_t *)malloc(sizeof(int32_t) * ht->head.size);

    ht->head.elements = calloc(sizeof(entry *), ht->head.size);
    return (AocHashTablePtr) ht;
}

void aoc_int32_hash_table_destroy(AocHashTable *hashtable) {
    AocInt32HashTable *ht = (AocInt32HashTable *)hashtable;

    if (ht) {
        if (ht->head.elements) {
            free(ht->head.elements);
        }
        if(ht->keys)
            free(ht->keys);

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

    // Check size of table - need to resize / rehash?
    if (ht->count >= 0.75 * ht->size)
        ht = aoc_int32_hash_table_rehash(ht);

    size_t index  = aoc_int32_hash_table_index(ht, key);

    if (aoc_int32_hash_table_lookup(ht, key) != NULL) return false;

    // create a new entry

    int32_entry *e = malloc(sizeof(*e));
    e->head.object = (void *)obj;
    e->key = key;

    // insert our entry
    e->head.next = ht->elements[index];
    ht->elements[index] = (entry *)e;

    ((AocInt32HashTable *)ht)->keys[ht->count] = key;
    ht->count += 1;
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
        return NULL;

    if (!aoc_int32_hash_table_lookup(ht, key))
        return NULL;

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

    // need also to remove the key from the 'keys' array
    AocInt32HashTable *table = (AocInt32HashTable *)ht;
    for (size_t i = 0; i < table->head.count; i++) {
        if (table->keys[i] == key) {
            if (i < ht->count - 1)
                memcpy(table->keys + i, table->keys + i + 1, sizeof(int32_t) * (table->head.count - i - 1));
        }
    }
    ht->count -= 1;

    return result;
}

size_t aoc_hash_table_size(AocHashTablePtr hash_table) {
    return hash_table->size;
}

size_t aoc_hash_table_count(AocHashTablePtr hash_table) {
    return hash_table->count;
}
