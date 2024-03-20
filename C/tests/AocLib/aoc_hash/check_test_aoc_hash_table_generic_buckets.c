#include "aoc_hash.h"
#include <check.h>
#include <stdlib.h>

static AocHashTablePtr hash_table = NULL;
static int32_t        *keys = NULL;
static int32_t        *values = NULL;

static uint32_t custom_hash(const void *key) {
    if (key != NULL) {
        return 10;
    }
    return 10;
}

static void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, custom_hash, NULL, NULL, AOC_INT32);
}

static void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
    if (keys) {
        free(keys);
    }
    if (values) {
        free(values);
    }
}

START_TEST(test_hash_table_buckets) {
    int key1 = 10;
    int key2 = 20;

    int value1 = 100;
    int value2 = 200;

    aoc_hash_table_insert(hash_table, &key1, &value1);
    aoc_hash_table_insert(hash_table, &key2, &value2);

    int return_value1 = *(int32_t *)(aoc_hash_table_lookup(hash_table, &key1));
    int return_value2 = *(int32_t *)(aoc_hash_table_lookup(hash_table, &key2));
    ck_assert(return_value1 == value1);
    ck_assert(return_value2 == value2);
}
END_TEST

TCase *test_case_aoc_hash_buckets(void) {
    TCase *test_aoc_hash_buckets = tcase_create("aoc_hash_table_buckets");
    tcase_add_checked_fixture(test_aoc_hash_buckets, aoc_hash_table_setup, aoc_hash_table_teardown);
    tcase_add_test(test_aoc_hash_buckets, test_hash_table_buckets);

    return test_aoc_hash_buckets;
}
