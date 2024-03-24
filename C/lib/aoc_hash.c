#include "aoc_hash.h"
#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_types.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/*
 * Functions to implement:
 * aoc_hash_table_foreach
 *
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
        number += (int64_t)(void *)1;
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
    AocHashTablePtr ht =
        aoc_hash_table_create_custom(new_size, hashtable->hash, hashtable->key_free_func,
                                     hashtable->value_free_func, hashtable->type);

    for (size_t i = 0; i < hashtable->size; i++) {
        entry *e = hashtable->elements[i];
        if (e != NULL) {
            do {
                void *key = e->key;
                void *value = e->object;
                aoc_hash_table_insert(ht, key, value);
                e = e->next;
            } while (e != NULL);
        }
    }
    free(hashtable->elements);

    hashtable->type = ht->type;
    hashtable->size = ht->size;
    hashtable->count = ht->count;
    hashtable->elements = ht->elements;

    free(ht);

    return hashtable;
}

AocHashTablePtr aoc_hash_table_create_custom(uint32_t size, hash_function hf, free_func kff,
                                             free_func vff, AocKeyType type) {
    AocHashTablePtr ht = (AocHashTablePtr)calloc(1, sizeof(AocHashTable));
    ht->size = size <= 17 ? 17 : next_prime(size);
    ht->count = 0;
    if (hf) {
        ht->hash = hf;
    } else {
        switch (type) {
            case AOC_INT32:
                ht->hash = int32_hash;
                break;
            case AOC_UINT32:
                ht->hash = uint32_hash;
                break;
            case AOC_INT64:
                ht->hash = int64_hash;
                break;
            case AOC_UINT64:
                ht->hash = uint64_hash;
                break;
            case AOC_STR:
                ht->hash = str_hash;
                break;
            case AOC_PTR:
                ht->hash = ptr_hash;
                break;
            case AOC_POINT:
                ht->hash = point_hash;
                break;
            case AOC_CHAR:
                ht->hash = char_hash;
                break;
            default:
                ht->hash = NULL;
                break;
        }
    }
    ht->type = type;
    ht->elements = (entry **)calloc(ht->size, sizeof(entry *));

    ht->key_free_func = kff;
    ht->value_free_func = vff;

    switch (ht->type) {
        case AOC_INT32:
            ht->key_equal = int32_equal;
            break;
        case AOC_UINT32:
            ht->key_equal = uint32_equal;
            break;
        case AOC_INT64:
            ht->key_equal = int64_equal;
            break;
        case AOC_UINT64:
            ht->key_equal = uint64_equal;
            break;
        case AOC_STR:
            ht->key_equal = str_equal;
            break;
        case AOC_PTR:
            ht->key_equal = ptr_equal;
            break;
        case AOC_POINT:
            ht->key_equal = point_equal;
            break;
        case AOC_CHAR:
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
            for (unsigned i = 0; i < ht->size; i++) {
                entry *e = ht->elements[i];
                if (e) {
                    do {
                        if (ht->key_free_func) {
                            ht->key_free_func(e->key);
                        }
                        if (ht->value_free_func) {
                            ht->value_free_func(e->object);
                        }
                        e = e->next;
                    } while (e != NULL);
                }
            }
            free(ht->elements);
        }
        free(ht);
    }
    *hashtable = NULL;
}

static bool aoc_hash_table_insert_replace(AocHashTablePtr ht, const void *key, const void *obj,
                                          bool replace) {
    if (!ht) {
        return false;
    }

    entry *e = NULL;
    bool   key_exists = false;

    e = aoc_hash_table_lookup_entry(ht, key);
    if (e) {
        if (!replace) {
            return false;
        } else {
            key_exists = true;
        }
    } else {
        e = (AocHashEntry *)malloc(sizeof(AocHashEntry));
    }

    size_t index = aoc_hash_table_index(ht, key);

    e->object = (void *)obj;
    e->key = (void *)key;
    if (!key_exists) {
        e->next = ht->elements[index];
        ht->elements[index] = e;
        ht->count += 1;
    }
    if (ht->count >= 0.75 * ht->size) {
        ht = aoc_hash_table_rehash(ht);
    }
    return !key_exists;
}

/****
 *
 * aoc_hash_table_insert:
 *
 * @ht: pointer to a AocHashTable
 * @key: address to key to insert
 * @value: The value to associate with the key
 *
 * Returns: 'true' if the key did not exist
 *          'false' otherwise
 *
 * Inserts value in table using key. If the key already exists in table, no change is made and the
 * function returns false. Otherwise the key/value pair is added and function returns true.
 *
 ****/
bool aoc_hash_table_insert(AocHashTablePtr ht, const void *key, const void *obj) {
    return aoc_hash_table_insert_replace(ht, key, obj, false);
}

/****
 *
 * aoc_hash_table_replace:
 *
 * @ht: pointer to a AocHashTable
 * @key: address to key to insert
 * @value: The value to associate with the key
 *
 * Returns: 'true' if the key did not exist
 *          'false' otherwise
 *
 *
 * Inserts value in table using key. If the key already exists in table, its associated value is
 * updated with 'value'
 *
 ****/
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
void aoc_hash_table_delete(AocHashTablePtr ht, const void *key) {
    if (!ht) {
        return;
    }

    if (!aoc_hash_table_lookup(ht, key)) {
        return;
    }

    size_t index = aoc_hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while (tmp != NULL && !ht->key_equal(tmp->key, key)) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return;
    }

    if (prev == NULL) {
        // deleting the head of the list
        ht->elements[index] = tmp->next;
    } else {
        // deleting elsewhere
        prev->next = tmp->next;
    }
    if (ht->key_free_func) {
        ht->key_free_func(tmp->key);
    }
    if (ht->value_free_func) {
        ht->value_free_func(tmp->object);
    }
    free(tmp);

    ht->count -= 1;

    return;
}

/*
 * aoc_hash_table_pop
 *
 * Deletes an entry from the hash table and return the entry struct.
 * It returns ownership of the entry to the caller.
 */
void *aoc_hash_table_pop(AocHashTablePtr ht, const void *key) {
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
    if (ht->key_free_func) {
        ht->key_free_func(tmp->key);
    }

    ht->count -= 1;
    void *result = tmp->object;
    free(tmp);

    return result;
}

size_t aoc_hash_table_size(AocHashTablePtr hash_table) {
    return hash_table->size;
}

size_t aoc_hash_table_count(AocHashTablePtr hash_table) {
    return hash_table ? hash_table->count : 0;
}

bool aoc_hash_table_add(AocHashTablePtr ht, const void *key) {
    return aoc_hash_table_insert(ht, key, &key);
}

inline static uint32_t aoc_hash(AocKeyType type, const void *key) {
    if ((type == AOC_INT32) || (type == AOC_UINT32)) {
        return *(uint32_t *)key;
    } else if ((type == AOC_INT64) || (type == AOC_UINT64)) {
        const uint64_t *bits = (uint64_t *)key;
        return (uint32_t)((*bits >> 32) ^ (*bits & 0xffffffffU));
    } else if (type == AOC_STR) {
        const void  *v = key;
        signed char *p;
        uint64_t     h = 5381;

        for (p = (signed char *)v; *p != '\0'; p++) {
            h = (h << 5) + h + *p;
        }
        return h;
    } else if (type == AOC_POINT) {
        Point   *point = (Point *)key;
        uint64_t int_hash = point->x;
        int_hash <<= sizeof(UINT_MAX) * 4;
        int_hash ^= point->y;

        return (unsigned)((int_hash >> 32) ^ (int_hash & 0xffffffffU));
    } else if (type == AOC_PTR) {
        return (uint32_t)(uint64_t)key;
    } else if (type == AOC_CHAR) {
        return (uint32_t) * (uint8_t *)key;
    } else {
        return 0;
    }
}

inline static uint32_t int32_hash(const void *key) {
    return aoc_hash(AOC_INT32, key);
}

inline static uint32_t uint32_hash(const void *key) {
    return aoc_hash(AOC_UINT32, key);
}

inline static uint32_t int64_hash(const void *key) {
    return aoc_hash(AOC_INT64, key);
}

inline static uint32_t uint64_hash(const void *key) {
    return aoc_hash(AOC_UINT64, key);
}

inline static uint32_t str_hash(const void *key) {
    return aoc_hash(AOC_STR, key);
}

inline static uint32_t ptr_hash(const void *key) {
    return aoc_hash(AOC_PTR, key);
}

inline static uint32_t point_hash(const void *key) {
    return aoc_hash(AOC_POINT, key);
}

inline static uint32_t char_hash(const void *key) {
    return aoc_hash(AOC_CHAR, key);
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
    iter->keys = (void **)calloc(hash_table->count, sizeof(void *));
    iter->values = (void **)calloc(hash_table->count, sizeof(void *));
    unsigned key_idx = 0;
    for (unsigned idx = 0; idx < hash_table->size; idx++) {
        entry *e = hash_table->elements[idx];
        if (e != NULL) {
            do {
                iter->keys[key_idx] = e->key;
                iter->values[key_idx] = e->object;
                key_idx++;
                e = e->next;
            } while (e != NULL);
        }
    }
}

bool aoc_hash_table_iter_next(AocHashIterator *iter, void **key, void **value) {
    if (!iter) {
        return false;
    }
    if (!(iter->position < (ssize_t)iter->hash_table->size)) {
        return false;
    }

    int32_t position = iter->position;
    do {
        position++;
        if (position >= (ssize_t)iter->hash_table->count) {
            iter->position = position;
            return false;
        }
    } while (!iter->keys[position]);

    if (key != NULL) {
        *key = iter->keys[position];
    }
    if (value != NULL) {
        *value = iter->values[position];
    }

    iter->position = position;
    return true;
}

bool aoc_hash_table_contains(AocHashTablePtr ht, const void *key) {
    return (aoc_hash_table_lookup(ht, key) != NULL);
}

bool aoc_hash_table_lookup_extended(AocHashTablePtr ht, const void *key, void **orig_key,
                                    void **value) {
    entry *e = aoc_hash_table_lookup_entry(ht, key);

    if (e == NULL) {
        if (orig_key != NULL) {
            *orig_key = NULL;
        }
        if (value != NULL) {
            *value = NULL;
        }
        return false;
    }

    if (orig_key != NULL) {
        *orig_key = e->key;
    }
    if (value != NULL) {
        *value = e->object;
    }
    return true;
}

AocArrayPtr aoc_hash_table_get_keys(AocHashTablePtr ht) {
    AocArrayPtr key_array = aoc_ptr_array_new();
    for (unsigned ind = 0; ind < ht->size; ind++) {
        entry *e = ht->elements[ind];
        if (e != NULL) {
            do {
                aoc_ptr_array_append(key_array, e->key);
                e = e->next;
            } while (e != NULL);
        }
    }
    return key_array;
}

AocArrayPtr aoc_hash_table_get_values(AocHashTablePtr ht) {
    AocArrayPtr value_array = aoc_ptr_array_new();
    for (unsigned ind = 0; ind < ht->size; ind++) {
        entry *e = ht->elements[ind];
        if (e != NULL) {
            do {
                aoc_ptr_array_append(value_array, e->object);
                e = e->next;
            } while (e != NULL);
        }
    }
    return value_array;
}
AocArrayPtr aoc_hash_table_get_values_if(AocHashTablePtr ht, bool(cmp_func)(const void *val)) {
    AocArrayPtr value_array = aoc_ptr_array_new();
    for (unsigned ind = 0; ind < ht->size; ind++) {
        entry *e = ht->elements[ind];
        if (e != NULL) {
            do {
                if (cmp_func(e->object)) {
                    aoc_ptr_array_append(value_array, e->object);
                }
                e = e->next;
            } while (e != NULL);
        }
    }
    return value_array;
}

void aoc_hash_table_foreach(AocHashTablePtr hash_table, AocHashTableFunc func, void *user_data) {
    for (unsigned idx = 0; idx < hash_table->size; idx++) {
        entry *e = hash_table->elements[idx];
        if (e != NULL) {
            do {
                func(e->key, e->object, user_data);
                e = e->next;
            } while (e != NULL);
        }
    }
}

void aoc_hash_table_foreach_remove(AocHashTablePtr hash_table, AocHashTableRFunc func,
                                   void *user_data) {

    for (unsigned idx = 0; idx < hash_table->size; idx++) {
        entry *e = hash_table->elements[idx];
        if (e != NULL) {
            do {
                entry *next = e->next;
                if (func(e->key, e->object, user_data)) {
                    aoc_hash_table_delete(hash_table, e->key);
                }
                e = next;
            } while (e != NULL);
        }
    }
}
AocHashTablePtr aoc_hash_table_new_similar(AocHashTablePtr hash_table) {
    AocHashTablePtr table =
        aoc_hash_table_create_custom(hash_table->size, hash_table->hash, hash_table->key_free_func,
                                     hash_table->value_free_func, hash_table->type);
    return table;
}
