#ifndef AOC_GENHASH_H
#define AOC_GENHASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "aoc_types.h"

typedef enum {
    AOC_KEY_INT32,
    AOC_KEY_UINT32,
    AOC_KEY_INT64,
    AOC_KEY_UINT64,
    AOC_KEY_STR,
    AOC_KEY_POINT,
    AOC_KEY_PTR,
    AOC_KEY_COUNT
} AocKeyType;

typedef enum {
    AOC_HASH_INT32,
    AOC_HASH_UINT32,
    AOC_HASH_INT64,
    AOC_HASH_UINT64,
    AOC_HASH_STR,
    AOC_HASH_PTR,
    AOC_HASH_COUNT
} AocHashType;

typedef struct Key {
    AocKeyType type;
    uint8_t    key[80];
} AocKey;

typedef struct entry AocHashEntry;

int32_t  int32_value(AocHashEntry *value);
int64_t  int64_value(AocHashEntry *value);
uint32_t uint32_value(AocHashEntry *value);
uint64_t uint64_value(AocHashEntry *value);
char    *str_value(AocHashEntry *value);
Point    point_value(AocHashEntry *value);

typedef struct _aoc_hash_table AocHashTable;
typedef AocHashTable          *AocHashTablePtr;

typedef uint32_t (*str_hashfunction)(const char *key, size_t);
typedef uint32_t (*ptr_hashfunction)(const void *key, size_t);
typedef uint32_t (*int32_hashfunction)(const int32_t key);
typedef uint32_t (*int64_hashfunction)(const int64_t key, size_t);
typedef uint32_t (*uint32_hashfunction)(const uint32_t key, size_t);
typedef uint32_t (*uint64_hashfunction)(const uint64_t key, size_t);
typedef uint32_t (*point_hashfunction)(const Point key, size_t);
typedef uint32_t (*line_hashfunction)(const Line key, size_t);

typedef uint32_t (*hash_function)(const void *key);
typedef bool (*key_equal_func)(const void *key1, const void *key2);
typedef void (*free_func)(void *ptr);

AocHashTablePtr aoc_hash_table_create(AocKeyType type);
AocHashTablePtr aoc_hash_table_create_custom(uint32_t size, hash_function hf, free_func key_free_function, free_func value_free_function, AocKeyType type);

AocHashEntry *aoc_hash_table_lookup_entry(AocHashTablePtr ht, const void *key);
void         *aoc_hash_table_lookup(AocHashTablePtr ht, const void *key);
bool          aoc_hash_table_insert(AocHashTablePtr ht, const void *key, const void *obj);
bool          aoc_hash_table_replace(AocHashTablePtr ht, const void *key, const void *obj);
bool          aoc_hash_table_add(AocHashTablePtr ht, const void *key);

void  aoc_hash_table_destroy(AocHashTablePtr *ht);
void *aoc_hash_table_delete(AocHashTablePtr ht, const void *key);

size_t aoc_hash_table_size(AocHashTablePtr hash_table);
size_t aoc_hash_table_count(AocHashTablePtr hash_table);

#endif /* AOC_HASH_H */
