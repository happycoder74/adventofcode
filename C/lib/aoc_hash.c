#include "aoc_hash.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Functions to implement:
 * aoc_hash_table_foreach
 * aoc_hash_table_contains
 * */

typedef struct entry {
    struct entry *next;
    AocKey        key;
    void         *object;
} entry;

struct _aoc_hash_table {
    AocKeyType    type;
    uint32_t      size;
    uint32_t      count;
    hash_function hash;
    entry       **elements;
    AocKey       *keys;
};

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
        number += 1;
    }
    size_t n = number;
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

static size_t aoc_hash_table_index(AocHashTable *hashtable, AocKey key) {
    return (hashtable->hash(key) % hashtable->size);
}

static AocHashTablePtr aoc_hash_table_rehash(AocHashTablePtr hashtable) {
    size_t          new_size = next_prime(hashtable->size + 1);
    AocHashTablePtr ht = aoc_hash_table_create(new_size, hashtable->hash, hashtable->type);

    AocKey *keys = hashtable->keys;
    for (size_t i = 0; i < hashtable->count; i++) {
        void *value = aoc_hash_table_lookup(hashtable, keys[i]);
        aoc_hash_table_insert(ht, keys[i], value);
    }
    free(keys);
    hashtable->type = ht->type;
    hashtable->elements = ht->elements;
    hashtable->size = ht->size;
    hashtable->count = ht->count;
    hashtable->keys = ht->keys;
    hashtable->hash = ht->hash;

    free(ht);

    return hashtable;
}

AocHashTablePtr aoc_hash_table_create(uint32_t size, hash_function hf, AocKeyType type) {
    AocHashTablePtr ht = (AocHashTablePtr)calloc(1, sizeof(AocHashTable));
    ht->size = size <= 17 ? 17 : next_prime(size);
    ht->count = 0;
    if (hf) {
        ht->hash = hf;
    } else {
        ht->hash = aoc_hash;
    }
    ht->type = type;
    ht->keys = (AocKey *)calloc(ht->size, sizeof(AocKey));
    ht->elements = (entry **)calloc(ht->size, sizeof(entry *));

    return ht;
}

void aoc_hash_table_destroy(AocHashTablePtr ht) {
    if (ht) {
        if (ht->elements) {
            free(ht->elements);
        }
        if (ht->keys) {
            free(ht->keys);
        }

        free(ht);
    }
}

bool aoc_hash_table_insert(AocHashTablePtr ht, const AocKey key, const void *obj) {
    if (!ht) {
        return 0;
    }
    if (aoc_hash_table_lookup(ht, key)) {
        return 0;
    }
    if (!obj) {
        return 0;
    }

    if (ht->count >= 0.75 * ht->size) {
        ht = aoc_hash_table_rehash(ht);
    }

    size_t index = aoc_hash_table_index(ht, key);

    if (aoc_hash_table_lookup(ht, key) != NULL) {
        return 0;
    }

    entry *e = malloc(sizeof(entry));
    e->object = (void *)obj;
    e->key = key;
    e->next = ht->elements[index];
    ht->elements[index] = e;
    ht->keys[ht->count] = key;
    ht->count += 1;
    return 1;
}

inline static bool key_equal(AocKey key1, AocKey key2) {
    if (key1.type != key2.type) {
        return false;
    }

    switch (key1.type) {
        case AOC_KEY_INT32:
            return ((*(int32_t *)key1.key) == (*(int32_t *)key2.key));
            break;
        case AOC_KEY_UINT32:
            return ((*(uint32_t *)key1.key) == (*(uint32_t *)key2.key));
            break;
        case AOC_KEY_INT64:
            return ((*(int64_t *)key1.key) == (*(int64_t *)key2.key));
            break;
        case AOC_KEY_UINT64:
            return ((*(uint64_t *)key1.key) == (*(uint64_t *)key2.key));
            break;
        case AOC_KEY_STR:
            return !strcmp((char *)key1.key, (char *)key2.key);
            break;
        case AOC_KEY_PTR:
            return key1.key == key2.key;
            break;
        case AOC_KEY_POINT:
            {
                Point *p1 = (Point *)key1.key;
                Point *p2 = (Point *)key2.key;

                return ((p1->x == p2->x) && (p1->y == p2->y));
            }
            break;
        default:
            return false;
            break;
    }
}

AocHashEntry *aoc_hash_table_lookup_new(AocHashTablePtr ht, AocKey key) {
    if (!ht) {
        return false;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];

    while (tmp != NULL && !key_equal(tmp->key, key)) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }
    return tmp;
}

void *aoc_hash_table_lookup(AocHashTablePtr ht, AocKey key) {
    if (!ht) {
        return false;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];

    while (tmp != NULL && !key_equal(tmp->key, key)) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }
    return tmp->object;
}

void *aoc_hash_table_delete(AocHashTablePtr ht, AocKey key) {
    if (!ht) {
        return NULL;
    }

    if (!aoc_hash_table_lookup(ht, key)) {
        return NULL;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while (tmp != NULL && !key_equal(tmp->key, key)) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }

    if (prev == NULL) {
        // deleting the head of the list
        ht->elements[index] = tmp->next;
    } else {
        // deleting elsewhere
        prev->next = tmp->next;
    }
    void *result = tmp->object;
    free(tmp);

    // need also to remove the key from the 'keys' array
    AocHashTable *table = ht;
    for (size_t i = 0; i < table->count; i++) {
        if (key_equal(table->keys[i], key)) {
            if (i < ht->count - 1) {
                memcpy(table->keys + i, table->keys + i + 1, sizeof(AocKey) * (table->count - i - 1));
            }
        }
    }
    ht->count -= 1;

    return result;
}

/*
 * aoc_hash_table_pop
 */
AocHashEntry *aoc_hash_table_pop(AocHashTablePtr ht, AocKey key) {
    if (!ht) {
        return NULL;
    }

    if (!aoc_hash_table_lookup(ht, key)) {
        return NULL;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while (tmp != NULL && !key_equal(tmp->key, key)) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }

    if (prev == NULL) {
        // deleting the head of the list
        ht->elements[index] = tmp->next;
    } else {
        // deleting elsewhere
        prev->next = tmp->next;
    }
    entry *result = tmp->object;
    free(tmp);

    // need also to remove the key from the 'keys' array
    AocHashTable *table = ht;
    for (size_t i = 0; i < table->count; i++) {
        if (key_equal(table->keys[i], key)) {
            if (i < ht->count - 1) {
                memcpy(table->keys + i, table->keys + i + 1, sizeof(AocKey) * (table->count - i - 1));
            }
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

inline int32_t int32_value(entry *value) {
    if (value->object != NULL) {
        return *(int32_t *)value->object;
    } else {
        return INT32_MAX;
    }
}

inline int64_t int64_value(entry *value) {
    if (value->object != NULL) {
        return *(int64_t *)value->object;
    } else {
        return INT64_MAX;
    }
}
inline uint32_t uint32_value(entry *value) {
    if (value->object != NULL) {
        return *(uint32_t *)value->object;
    } else {
        return INT32_MAX;
    }
}

inline uint64_t uint64_value(entry *value) {
    if (value->object != NULL) {
        return *(uint64_t *)value->object;
    } else {
        return INT64_MAX;
    }
}

inline char *str_value(entry *value) {
    return (char *)value->object;
}

inline Point point_value(entry *value) {
    return *(Point *)value->object;
}

inline AocKey int32_key(int32_t key) {
    AocKey k;

    int32_t *keyval = (int32_t *)k.key;
    *keyval = key;
    k.type = AOC_KEY_INT32;

    return k;
}

inline AocKey uint32_key(uint32_t key) {
    AocKey k;

    uint32_t *keyval = (uint32_t *)k.key;
    *keyval = key;
    k.type = AOC_KEY_UINT32;

    return k;
}

inline AocKey int64_key(int64_t key) {
    AocKey k;

    int32_t *keyval = (int32_t *)k.key;
    *keyval = key;
    k.type = AOC_KEY_INT64;

    return k;
}

inline AocKey uint64_key(uint64_t key) {
    AocKey k;

    uint64_t *keyval = (uint64_t *)k.key;
    *keyval = key;
    k.type = AOC_KEY_UINT64;

    return k;
}

inline AocKey str_key(const char *key) {
    AocKey k;

    memcpy(k.key, key, strlen(key) + 1);
    k.type = AOC_KEY_STR;

    return k;
}

inline AocKey point_key(const Point key) {
    AocKey k;

    memcpy(k.key, &key, sizeof(Point));
    k.type = AOC_KEY_POINT;

    return k;
}

inline AocKey ptr_key(const void *key) {
    AocKey k;

    for (unsigned i = 0; i < 8; i++) {
        k.key[i] = ((uint8_t *)key)[i];
    }
    k.type = AOC_KEY_PTR;

    return k;
}

inline uint32_t aoc_hash(AocKey key) {
    AocKeyType type = key.type;

    if ((type == AOC_KEY_INT32) || (type == AOC_KEY_UINT32)) {
        return *(uint32_t *)key.key;
    } else if ((type == AOC_KEY_INT64) || (type == AOC_KEY_UINT64)) {
        const uint64_t *bits = (uint64_t *)key.key;
        return (uint32_t)((*bits >> 32) ^ (*bits & 0xffffffffU));
    } else if (type == AOC_KEY_STR) {
        const void        *v = (const void *)key.key;
        const signed char *p;
        uint64_t           h = 5381;

        for (p = v; *p != '\0'; p++) {
            h = (h << 5) + h + *p;
        }
        return h;
    } else if (type == AOC_KEY_POINT) {
        Point   *point = (Point *)key.key;
        uint64_t int_hash = point->x;
        int_hash <<= sizeof(UINT_MAX) * 4;
        int_hash ^= point->y;

        return (unsigned)((int_hash >> 32) ^ (int_hash & 0xffffffffU));
    } else if (type == AOC_KEY_PTR) {
        uint64_t value = *(uint64_t *)key.key;
        return (uint32_t)value;
    } else {
        return 0;
    }
}
