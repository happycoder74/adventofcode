#include "aoc_hash.h"
#include "aoc_types.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocHashTablePtr hash_table = NULL;
static AocHashTablePtr hash_table2 = NULL;
static int32_t        *keys = NULL;
static int32_t        *values = NULL;

static void aoc_hash_table_load_N(size_t size) {
    hash_table = aoc_hash_table_create(AOC_INT32);

    keys = (int32_t *)calloc(size, sizeof(int32_t));
    values = (int32_t *)calloc(size, sizeof(int32_t));

    for (size_t i = 0; i < size; i++) {
        keys[i] = i + 1;
        values[i] = i * 100;
        aoc_hash_table_insert(hash_table, &keys[i], &values[i]);
    }
}

static void aoc_hash_table_load_6(void) {
    aoc_hash_table_load_N(6);
}

static void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, NULL, NULL, free, AOC_INT32);
}

static void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
}

START_TEST(test_hash_table_create) {
    ck_assert_ptr_nonnull(hash_table);
}
END_TEST

START_TEST(test_hash_table_insert_lookup) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    int32_t key1 = 30;
    aoc_hash_table_insert(hash_table, &key1, value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    int32_t key2 = 20;
    aoc_hash_table_insert(hash_table, &key2, value);

    int32_t  key3 = 30;
    int32_t *data = (int32_t *)aoc_hash_table_lookup(hash_table, &key3);
    int32_t  expected = 5;
    int32_t  actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);

    int32_t key4 = 20;
    data = (int32_t *)aoc_hash_table_lookup(hash_table, &key4);
    expected = 10;
    actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);

    int32_t key5 = 30;
    data = (int32_t *)aoc_hash_table_lookup(hash_table, &key5);
    expected = 5;
    actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);
}
END_TEST

START_TEST(test_hash_table_pop) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    int32_t key1 = 30;
    bool    insert_result;
    insert_result = aoc_hash_table_insert(hash_table, &key1, value);
    ck_assert(insert_result);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    int32_t key2 = 20;
    insert_result = aoc_hash_table_insert(hash_table, &key2, value);
    ck_assert(insert_result);

    int32_t  key3 = 30;
    int32_t *return_value = (int32_t *)aoc_hash_table_pop(hash_table, &key3);
    ck_assert_ptr_nonnull(return_value);
    ck_assert_msg(5 == *return_value, "Expected %d, but got %d", 5, *return_value);
}
END_TEST

START_TEST(aoc_hash_table_loaded) {
    int32_t value = 1001;
    int32_t key = 100;
    aoc_hash_table_insert(hash_table, &key, &value);
    int32_t expected = 17;
    int32_t actual = (int32_t)aoc_hash_table_size(hash_table);
    ck_assert_msg(expected == actual, "Expected size of %d, but got %d", expected, actual);
    expected = values[4];
    actual = *(int32_t *)(aoc_hash_table_lookup(hash_table, &keys[4]));
    ck_assert_msg(expected == actual, "Expected value of key: %d to be %d but got %d", keys[4],
                  expected, actual);
}

TCase *test_case_aoc_hash_int32(void) {
    TCase *aoc_hash_int32 = tcase_create("aoc_hash_table_int32");

    tcase_add_checked_fixture(aoc_hash_int32, aoc_hash_table_setup, aoc_hash_table_teardown);
    tcase_add_test(aoc_hash_int32, test_hash_table_create);
    tcase_add_test(aoc_hash_int32, test_hash_table_insert_lookup);
    tcase_add_test(aoc_hash_int32, test_hash_table_pop);
    return aoc_hash_int32;
}

TCase *test_case_aoc_hash_int32_loaded(void) {
    TCase *aoc_hash_int32 = tcase_create("aoc_hash_table_int32_loaded");

    tcase_add_checked_fixture(aoc_hash_int32, aoc_hash_table_load_6, aoc_hash_table_teardown);
    tcase_add_test(aoc_hash_int32, aoc_hash_table_loaded);
    return aoc_hash_int32;
}
