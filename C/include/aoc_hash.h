#ifndef AOC_GENHASH_H
#define AOC_GENHASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "aoc_types.h"

typedef AocType AocKeyType;

typedef struct entry AocHashEntry;

typedef struct _aoc_hash_table AocHashTable;
typedef AocHashTable          *AocHashTablePtr;

struct _hash_iterator {
    AocHashTablePtr hash_table;
    int32_t         position;
    void          **keys;
    void          **values;
};
typedef struct _hash_iterator AocHashIterator;

typedef void (*AocHashTableFunc)(void *key, void *value, void *user_data);
typedef bool (*AocHashTableRFunc)(void *key, void *value, void *user_data);
typedef uint32_t (*hash_function)(const void *key);
typedef bool (*key_equal_func)(const void *key1, const void *key2);
typedef void (*free_func)(void *ptr);

AocHashTablePtr aoc_hash_table_create(AocKeyType type);
AocHashTablePtr aoc_hash_table_create_custom(uint32_t size, hash_function hf,
                                             free_func key_free_function,
                                             free_func value_free_function, AocKeyType type);
AocHashTablePtr aoc_hash_table_new_similar(AocHashTablePtr ht);

AocHashEntry *aoc_hash_table_lookup_entry(AocHashTablePtr ht, const void *key);
void         *aoc_hash_table_lookup(AocHashTablePtr ht, const void *key);
bool          aoc_hash_table_lookup_extended(AocHashTablePtr ht, const void *key, void **orig_key,
                                             void **value);
bool          aoc_hash_table_insert(AocHashTablePtr ht, const void *key, const void *obj);
bool          aoc_hash_table_replace(AocHashTablePtr ht, const void *key, const void *obj);
bool          aoc_hash_table_add(AocHashTablePtr ht, const void *key);
bool          aoc_hash_table_contains(AocHashTablePtr ht, const void *key);

void  aoc_hash_table_foreach_remove(AocHashTablePtr hash_table, AocHashTableRFunc func,
                                    void *user_data);
void  aoc_hash_table_foreach(AocHashTablePtr hash_table, AocHashTableFunc func, void *user_data);
void  aoc_hash_table_destroy(AocHashTablePtr *ht);
void *aoc_hash_table_pop(AocHashTablePtr ht, const void *key);
void  aoc_hash_table_delete(AocHashTablePtr ht, const void *key);

size_t      aoc_hash_table_size(AocHashTablePtr hash_table);
size_t      aoc_hash_table_count(AocHashTablePtr hash_table);
AocArrayPtr aoc_hash_table_get_keys(AocHashTablePtr hash_table);
AocArrayPtr aoc_hash_table_get_values(AocHashTablePtr hash_table);
AocArrayPtr aoc_hash_table_get_values_if(AocHashTablePtr hash_table, bool(cmp_func)(const void *));

void aoc_hash_table_iter_init(AocHashIterator *iter, AocHashTablePtr hash_table);
bool aoc_hash_table_iter_next(AocHashIterator *iter, void **key, void **value);

#endif /* AOC_HASH_H */
