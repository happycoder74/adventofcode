#include "aoc_hash.h"
#include <corecrt.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Functions to implement:
 * aoc_hash_table_foreach
 * aoc_hash_table_contains
 * */

inline static uint32_t uint64_hash(const void *key);
inline static bool     uint64_equal(const void *key1, const void *key2);
inline static uint32_t uint32_hash(const void *key);
inline static bool     uint32_equal(const void *key1, const void *key2);
inline static uint32_t int64_hash(const void *key);
inline static bool     int64_equal(const void *key1, const void *key2);
inline static uint32_t int32_hash(const void *key);
inline static bool     int32_equal(const void *key1, const void *key2);
inline static uint32_t str_hash(const void *key);
inline static bool     str_equal(const void *key1, const void *key2);
inline static uint32_t ptr_hash(const void *key);
inline static bool     ptr_equal(const void *key1, const void *key2);
inline static uint32_t point_hash(const void *key);
inline static bool     point_equal(const void *key1, const void *key2);
inline static uint32_t char_hash(const void *key);
inline static bool     char_equal(const void *key1, const void *key2);

typedef struct entry {
    struct entry *next;
    void         *key;
    void         *object;
} entry;

struct _aoc_hash_table {
    AocKeyType     type;
    uint32_t       size;
    uint32_t       count;
    hash_function  hash;
    free_func      key_free_func;
    free_func      value_free_func;
    key_equal_func key_equal;
    entry        **elements;
    void         **keys;
    void         **values;
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

static size_t aoc_hash_table_index(AocHashTable *hashtable, const void *key) {
    return (hashtable->hash(key) % hashtable->size);
}

static AocHashTablePtr aoc_hash_table_rehash(AocHashTablePtr hashtable) {
    size_t          new_size = next_prime(hashtable->size * 2 - 1);
    AocHashTablePtr ht = aoc_hash_table_create_custom(new_size, hashtable->hash, hashtable->key_free_func, hashtable->value_free_func, hashtable->type);

    void **keys = hashtable->keys;
    void **values = hashtable->values;

    for (size_t i = 0; i < hashtable->count; i++) {
        aoc_hash_table_insert(ht, keys[i], values[i]);
    }
    free(hashtable->keys);
    free(hashtable->values);
    free(hashtable->elements);

    hashtable->type = ht->type;
    hashtable->size = ht->size;
    hashtable->count = ht->count;
    hashtable->keys = ht->keys;
    hashtable->values = ht->values;
    hashtable->elements = ht->elements;

    free(ht);

    return hashtable;
}

AocHashTablePtr aoc_hash_table_create_custom(uint32_t size, hash_function hf, free_func kff, free_func vff, AocKeyType type) {
    AocHashTablePtr ht = (AocHashTablePtr)calloc(1, sizeof(AocHashTable));
    ht->size = size <= 17 ? 17 : next_prime(size);
    ht->count = 0;
    if (hf) {
        ht->hash = hf;
    } else {
        switch (type) {
            case AOC_KEY_INT32:
                ht->hash = int32_hash;
                break;
            case AOC_KEY_UINT32:
                ht->hash = uint32_hash;
                break;
            case AOC_KEY_INT64:
                ht->hash = int64_hash;
                break;
            case AOC_KEY_UINT64:
                ht->hash = uint64_hash;
                break;
            case AOC_KEY_STR:
                ht->hash = str_hash;
                break;
            case AOC_KEY_PTR:
                ht->hash = ptr_hash;
                break;
            case AOC_KEY_POINT:
                ht->hash = point_hash;
                break;
            case AOC_KEY_CHAR:
                ht->hash = char_hash;
                break;
            default:
                ht->hash = NULL;
                break;
        }
    }
    ht->type = type;
    ht->keys = (void **)calloc(ht->size, sizeof(void *));
    ht->values = (void **)calloc(ht->size, sizeof(void *));
    ht->elements = (entry **)calloc(ht->size, sizeof(entry *));

    ht->key_free_func = kff;
    ht->value_free_func = vff;

    switch (ht->type) {
        case AOC_KEY_INT32:
            ht->key_equal = int32_equal;
            break;
        case AOC_KEY_UINT32:
            ht->key_equal = uint32_equal;
            break;
        case AOC_KEY_INT64:
            ht->key_equal = int64_equal;
            break;
        case AOC_KEY_UINT64:
            ht->key_equal = uint64_equal;
            break;
        case AOC_KEY_STR:
            ht->key_equal = str_equal;
            break;
        case AOC_KEY_PTR:
            ht->key_equal = ptr_equal;
            break;
        case AOC_KEY_POINT:
            ht->key_equal = point_equal;
            break;
        case AOC_KEY_CHAR:
            ht->key_equal = char_equal;
            break;
        default:
            ht->key_equal = NULL;
            break;
    }
    return ht;
}

AocHashTablePtr aoc_hash_table_create(AocKeyType type) {
    return aoc_hash_table_create_custom(0, NULL, NULL, NULL, type);
}

void aoc_hash_table_destroy(AocHashTablePtr *hashtable) {
    AocHashTablePtr ht = *hashtable;
    if (ht) {
        if (ht->elements) {
            free(ht->elements);
        }
        if (ht->keys) {
            for (unsigned key = 0; key < ht->count; key++) {
                if (ht->key_free_func) {
                    ht->key_free_func(ht->keys[key]);
                }
            }
            free(ht->keys);
        }
        if (ht->values) {
            for (unsigned val = 0; val < ht->count; val++) {
                if (ht->value_free_func) {
                    ht->value_free_func(ht->values[val]);
                }
            }
            free(ht->values);
        }

        free(ht);
    }
    *hashtable = NULL;
}

static bool aoc_hash_table_insert_replace(AocHashTablePtr ht, const void *key, const void *obj, bool replace) {
    bool value_exists = false;
    if (!ht) {
        return 0;
    }
    if (aoc_hash_table_lookup(ht, key)) {
        if (!replace) {
            return 0;
        } else {
            value_exists = true;
        }
    }
    if (!obj) {
        return 0;
    }

    if (ht->count >= 0.75 * ht->size) {
        ht = aoc_hash_table_rehash(ht);
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *e = malloc(sizeof(entry));
    e->object = (void *)obj;
    e->key = (void *)key;
    e->next = ht->elements[index];
    ht->elements[index] = e;
    ht->keys[ht->count] = (void *)key;
    ht->values[ht->count] = (void *)obj;
    ht->count += 1;
    return !value_exists;
}

bool aoc_hash_table_insert(AocHashTablePtr ht, const void *key, const void *obj) {
    return aoc_hash_table_insert_replace(ht, key, obj, false);
}

bool aoc_hash_table_replace(AocHashTablePtr ht, const void *key, const void *obj) {
    return aoc_hash_table_insert_replace(ht, key, obj, true);
}

inline static bool int32_equal(const void *key1, const void *key2) {
    return ((*(int32_t *)key1) == (*(int32_t *)key2));
}

inline static bool uint32_equal(const void *key1, const void *key2) {
    return ((*(uint32_t *)key1) == (*(uint32_t *)key2));
}

inline static bool int64_equal(const void *key1, const void *key2) {
    return ((*(int64_t *)key1) == (*(int64_t *)key2));
}

inline static bool uint64_equal(const void *key1, const void *key2) {
    return ((*(uint64_t *)key1) == (*(uint64_t *)key2));
}

inline static bool str_equal(const void *key1, const void *key2) {
    return !strcmp((char *)key1, (char *)key2);
}

inline static bool ptr_equal(const void *key1, const void *key2) {
    return key1 == key2;
}

inline static bool point_equal(const void *key1, const void *key2) {
    Point *p1 = (Point *)key1;
    Point *p2 = (Point *)key2;

    return ((p1->x == p2->x) && (p1->y == p2->y));
}

inline static bool char_equal(const void *key1, const void *key2) {
    return ((*(char *)key1) == (*(char *)key2));
}

AocHashEntry *aoc_hash_table_lookup_entry(AocHashTablePtr ht, const void *key) {
    if (!ht) {
        return NULL;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];

    while (tmp != NULL && !ht->key_equal(tmp->key, key)) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }
    return tmp;
}

void *aoc_hash_table_lookup(AocHashTablePtr ht, const void *key) {
    entry *e = aoc_hash_table_lookup_entry(ht, key);

    return (e ? e->object : NULL);
}

/*
 * aoc_hash_table_delete
 *
 *
 * Deletes and entry from the hash table.
 * It returns the value and the ownership of the value from the entry struct.
 * The (internal) entry struct pointer and the key is deleted.
 *
 */
void *aoc_hash_table_delete(AocHashTablePtr ht, const void *key) {
    if (!ht) {
        return NULL;
    }

    if (!aoc_hash_table_lookup(ht, key)) {
        return NULL;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while (tmp != NULL && !ht->key_equal(tmp->key, key)) {
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
        if (ht->key_equal(table->keys[i], key)) {
            if (i < ht->count - 1) {
                if (ht->key_free_func) {
                    ht->key_free_func(table->keys[i]);
                }
                memmove(table->keys + i, table->keys + i + 1, sizeof(void *) * (table->count - i - 1));
                break;
            }
        }
    }
    ht->count -= 1;

    return result;
}

/*
 * aoc_hash_table_pop
 *
 * Deletes an entry from the hash table and return the entry struct.
 * It returns ownership of the entry to the caller.
 */
AocHashEntry *aoc_hash_table_pop(AocHashTablePtr ht, const void *key) {
    if (!ht) {
        return NULL;
    }

    if (!aoc_hash_table_lookup(ht, key)) {
        return NULL;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while (tmp != NULL && !ht->key_equal(tmp->key, key)) {
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
    entry *result = tmp;

    // need also to remove the key from the 'keys' array
    AocHashTable *table = ht;
    for (size_t i = 0; i < table->count; i++) {
        if (ht->key_equal(table->keys[i], key)) {
            if (i < ht->count - 1) {
                memcpy(table->keys + i, table->keys + i + 1, sizeof(void *) * (table->count - i - 1));
                break;
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

bool aoc_hash_table_add(AocHashTablePtr ht, const void *key) {
    return aoc_hash_table_insert(ht, key, &key);
}

inline static uint32_t aoc_hash(AocKeyType type, const void *key) {
    if ((type == AOC_KEY_INT32) || (type == AOC_KEY_UINT32)) {
        return *(uint32_t *)key;
    } else if ((type == AOC_KEY_INT64) || (type == AOC_KEY_UINT64)) {
        const uint64_t *bits = (uint64_t *)key;
        return (uint32_t)((*bits >> 32) ^ (*bits & 0xffffffffU));
    } else if (type == AOC_KEY_STR) {
        const void        *v = key;
        const signed char *p;
        uint64_t           h = 5381;

        for (p = v; *p != '\0'; p++) {
            h = (h << 5) + h + *p;
        }
        return h;
    } else if (type == AOC_KEY_POINT) {
        Point   *point = (Point *)key;
        uint64_t int_hash = point->x;
        int_hash <<= sizeof(UINT_MAX) * 4;
        int_hash ^= point->y;

        return (unsigned)((int_hash >> 32) ^ (int_hash & 0xffffffffU));
    } else if (type == AOC_KEY_PTR) {
        return (uint32_t)(uint64_t)key;
    } else if (type == AOC_KEY_CHAR) {
        return (uint32_t) * (uint8_t *)key;
    } else {
        return 0;
    }
}

inline static uint32_t int32_hash(const void *key) {
    return aoc_hash(AOC_KEY_INT32, key);
}

inline static uint32_t uint32_hash(const void *key) {
    return aoc_hash(AOC_KEY_UINT32, key);
}

inline static uint32_t int64_hash(const void *key) {
    return aoc_hash(AOC_KEY_INT64, key);
}

inline static uint32_t uint64_hash(const void *key) {
    return aoc_hash(AOC_KEY_UINT64, key);
}

inline static uint32_t str_hash(const void *key) {
    return aoc_hash(AOC_KEY_STR, key);
}

inline static uint32_t ptr_hash(const void *key) {
    return aoc_hash(AOC_KEY_PTR, key);
}

inline static uint32_t point_hash(const void *key) {
    return aoc_hash(AOC_KEY_POINT, key);
}

inline static uint32_t char_hash(const void *key) {
    return aoc_hash(AOC_KEY_CHAR, key);
}

void aoc_hash_table_iter_init(AocHashIterator *iter, AocHashTablePtr hash_table) {
    if (!iter) {
        return;
    }
    if (!hash_table) {
        return;
    }

    iter->position = -1;
    iter->hash_table = hash_table;
}

bool aoc_hash_table_iter_next(AocHashIterator *iter, void **key, void **value) {
    if (!iter) {
        return false;
    }
    if (!(iter->position < (ssize_t)iter->hash_table->count)) {
        return false;
    }

    int32_t position = iter->position;
    do {
        position++;
        if (position >= (ssize_t)iter->hash_table->count) {
            iter->position = position;
            return false;
        }
    } while (!iter->hash_table->keys[position]);

    if (key != NULL) {
        *key = iter->hash_table->keys[position];
    }
    if (value != NULL) {
        *value = iter->hash_table->values[position];
    }

    iter->position = position;
    return true;
}

bool aoc_hash_table_contains(AocHashTablePtr ht, const void *key) {
    return (aoc_hash_table_lookup(ht, key) != NULL);
}
