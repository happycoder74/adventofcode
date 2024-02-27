#ifndef AOC_HASH_H
#define AOC_HASH_H

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
    AOC_KEY_COUNT
} AocKeyType;

typedef enum {
    AOC_HASH_INT32,
    AOC_HASH_UINT32,
    AOC_HASH_INT64,
    AOC_HASH_UINT64,
    AOC_HASH_STR,
    AOC_HASH_COUNT
} AocHashType;

typedef struct Key {
    AocKeyType type;
    uint8_t    key[80];
} AocKey;

AocKey int32_key(int32_t value);
AocKey int64_key(int64_t value);
AocKey uint32_key(uint32_t value);
AocKey uint64_key(uint64_t value);
AocKey str_key(const char *value);

typedef struct _aoc_hash_table AocHashTable;
typedef AocHashTable          *AocHashTablePtr;

typedef uint64_t (*str_hashfunction)(const char *key, size_t);
typedef uint64_t (*ptr_hashfunction)(const void *key, size_t);
typedef uint64_t (*int32_hashfunction)(const int32_t key);
typedef uint64_t (*int64_hashfunction)(const int64_t key, size_t);
typedef uint64_t (*uint32_hashfunction)(const uint32_t key, size_t);
typedef uint64_t (*uint64_hashfunction)(const uint64_t key, size_t);
typedef uint64_t (*point_hashfunction)(const Point key, size_t);
typedef uint64_t (*line_hashfunction)(const Line key, size_t);

typedef uint64_t (*hash_function)(const AocKey key);

AocHashTablePtr aoc_hash_table_create(uint32_t size, hash_function hf, AocHashType type);
void           *aoc_hash_table_lookup(AocHashTablePtr ht, AocKey key);
bool            aoc_hash_table_insert(AocHashTablePtr ht, const AocKey key, const void *obj);

AocHashTablePtr aoc_int32_hash_table_create(uint32_t size, int32_hashfunction hf);
void           *aoc_int32_hash_table_lookup(AocHashTablePtr ht, const int32_t key);
void            aoc_int32_hash_table_destroy(AocHashTablePtr ht);
bool            aoc_int32_hash_table_insert(AocHashTablePtr ht, const int32_t key, const void *obj);
void           *aoc_int32_hash_table_delete(AocHashTablePtr ht, const int32_t key);

AocHashTablePtr aoc_int64_hash_table_create(uint32_t size, int64_hashfunction hf);
void           *aoc_int64_hash_table_lookup(AocHashTablePtr ht, const int64_t key);

AocHashTablePtr aoc_uint32_hash_table_create(uint32_t size, uint32_hashfunction hf);
AocHashTablePtr aoc_uint64_hash_table_create(uint32_t size, uint64_hashfunction hf);
AocHashTablePtr aoc_str_hash_table_create(uint32_t size, str_hashfunction hf);
AocHashTablePtr aoc_ptr_hash_table_create(uint32_t size, ptr_hashfunction hf);

void  aoc_hash_table_destroy(AocHashTablePtr ht);
void *aoc_hash_table_delete(AocHashTablePtr ht, AocKey key);

size_t aoc_hash_table_size(AocHashTablePtr hash_table);
size_t aoc_hash_table_count(AocHashTablePtr hash_table);

#endif /* AOC_HASH_H */
