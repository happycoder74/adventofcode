#include "aoc_hash.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocHashTablePtr hash_table = NULL;
AocHashTablePtr hash_table2 = NULL;
int32_t        *keys = NULL;
int32_t        *values = NULL;

static void aoc_hash_table_load_N(size_t size) {
    if (!hash_table) {
        return;
    }

    keys = (int32_t *)calloc(size, sizeof(int32_t));
    values = (int32_t *)calloc(size, sizeof(int32_t));

    for (size_t i = 0; i < size; i++) {
        keys[i] = i + 1;
        values[i] = i * 100;
        aoc_hash_table_insert(hash_table, int32_key(keys[i]), &values[i]);
    }
}

void aoc_hash_table_load_6(void) {
    aoc_hash_table_load_N(6);
}

void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create(3, aoc_hash, AOC_KEY_INT32);
}

void aoc_hash_table_teardown(void) {
    if (hash_table) {
        free(hash_table);
    }

    if (keys) {
        free(keys);
    }
    if (values) {
        free(values);
    }
}

TestSuite(aoc_hash_table, .init = aoc_hash_table_setup, .fini = aoc_hash_table_teardown);

Test(aoc_hash_table, test_hash_table_create) {
    cr_expect_not_null(hash_table, "Expected new hash_table to not be NULL");
}

Test(aoc_hash_table, test_hash_table_insert_lookup) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_hash_table_insert(hash_table, int32_key(30), value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_hash_table_insert(hash_table, int32_key(20), value);

    int32_t *data = (int32_t *)aoc_hash_table_lookup(hash_table, int32_key(30));
    int32_t  expected = 5;
    int32_t  actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, int32_key(20));
    expected = 10;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, int32_key(30));
    expected = 5;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);
}

Test(aoc_hash_table, test_hash_table_delete) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_hash_table_insert(hash_table, int32_key(30), value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_hash_table_insert(hash_table, int32_key(20), value);

    int32_t *return_value = (int32_t *)aoc_hash_table_delete(hash_table, int32_key(30));
    cr_expect_not_null(return_value, "Did not expect return value from delete to be NULL");
    cr_expect_eq(5, *return_value, "Expected %d, but got %d", 5, *return_value);
}

Test(aoc_hash_table, test_hash_table_rehash, .init = aoc_hash_table_load_6) {
    int32_t value = 1001;
    aoc_hash_table_insert(hash_table, int32_key(100), &value);
    int32_t expected = 17;
    int32_t actual = (int32_t)aoc_hash_table_size(hash_table);
    cr_expect_eq(expected, actual, "Expected size of %d, but got %d", expected, actual);
    expected = values[4];
    actual = int32_value(aoc_hash_table_lookup_new(hash_table, int32_key(keys[4])));
    cr_expect_eq(expected, actual, "Expected value of key: %d to be %d but got %d", keys[4], expected, actual);
}
