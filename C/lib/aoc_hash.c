#include "aoc_hash.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
  
typedef struct entry {
    char *key;
    void *object;
    struct entry *next;
} entry;
        

struct _aoc_hash_table {
    uint32_t size;
    hashfunction hash;
    entry **elements;
};


static size_t aoc_hash_table_index(aoc_hash_table *ht, const char *key) {
    size_t result = (ht->hash(key, strlen(key)) % ht->size);
    return result;
}
aoc_hash_table *aoc_hash_table_create(uint32_t size, hashfunction hf) {
    aoc_hash_table *ht = (aoc_hash_table *)malloc(sizeof(*ht));
    ht->size = size;
    ht->hash = hf;

    ht->elements = calloc(sizeof(entry *), ht->size);
    return ht;
}

void aoc_hash_table_destroy(aoc_hash_table *ht) {
    if (ht) {
      if (ht->elements) {
        free(ht->elements);
      }

      free(ht);
    }
}

bool aoc_hash_table_insert(aoc_hash_table *ht, const char *key, void *obj) {
    if (!ht)
        return false;

    if (aoc_hash_table_lookup(ht, key))
        return false;

    if (key == NULL || obj == NULL)
        return false;

    size_t index  = aoc_hash_table_index(ht, key);

    if (aoc_hash_table_lookup(ht, key) != NULL) return false;

    // create a new entry

    entry *e = malloc(sizeof(*e));
    e->object = obj;
    e->key = strdup(key);

    // insert our entry
    e->next = ht->elements[index];
    ht->elements[index] = e;
    return true;
}

void *aoc_hash_table_lookup(aoc_hash_table *ht, const char *key) {
    if (!ht)
        return false;

    if (aoc_hash_table_lookup(ht, key))
        return false;

    if (key == NULL)
        return false;

    size_t index  = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    return tmp->object;
}

void *aoc_hash_table_delete(aoc_hash_table *ht, const char *key) {
    if (!ht)
        return false;

    if (aoc_hash_table_lookup(ht, key))
        return false;

    if (key == NULL)
        return false;

    size_t index  = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;

    if (prev == NULL) {
        // deleting the head of the list
        ht->elements[index] = tmp->next;
    } else {
        // deleting elsewhere
        prev->next = tmp->next;
    }
    void *result = tmp->object;
    free(tmp);
    return result;
}
