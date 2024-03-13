#include "aoc_hash.h"
#include <criterion/criterion.h>

AocHashTablePtr hash_table = NULL;
int32_t        *keys = NULL;
int32_t        *values = NULL;

uint32_t custom_hash(const void *key) {
    return 10;
}

void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, custom_hash, NULL, NULL, AOC_INT32);
}

void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
    if (keys) {
        free(keys);
    }
    if (values) {
        free(values);
    }
}

TestSuite(aoc_hash_table, .init = aoc_hash_table_setup, .fini = aoc_hash_table_teardown);

Test(aoc_hash_table, test_hash_table_buckets) {
    int key1 = 10;
    int key2 = 20;

    int value1 = 100;
    int value2 = 200;

    aoc_hash_table_insert(hash_table, &key1, &value1);
    aoc_hash_table_insert(hash_table, &key2, &value2);

    int return_value1 = *(int32_t *)(aoc_hash_table_lookup(hash_table, &key1));
    int return_value2 = *(int32_t *)(aoc_hash_table_lookup(hash_table, &key2));
    cr_expect(return_value1 == value1);
    cr_expect(return_value2 == value2);
}
