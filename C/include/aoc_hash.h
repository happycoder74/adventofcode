#ifndef AOC_HASH_H
#define AOC_HASH_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t (*hashfunction) (const char *key, size_t);
typedef struct _aoc_hash_table aoc_hash_table;

aoc_hash_table *aoc_hash_table_create(uint32_t size, hashfunction hf);
void aoc_hash_table_destroy(aoc_hash_table *ht);
bool aoc_hash_table_insert(aoc_hash_table *ht, const char *key, void *obj);
void *aoc_hash_table_lookup(aoc_hash_table *ht, const char *key);
void *aoc_hash_table_delete(aoc_hash_table *ht, const char *key);

#endif /* AOC_HASH_H */
