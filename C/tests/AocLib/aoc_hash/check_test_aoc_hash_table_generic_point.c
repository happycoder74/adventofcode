#include "aoc_hash.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocHashTablePtr hash_table = NULL;
static AocHashTablePtr hash_table2 = NULL;

static void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, NULL, NULL, free, AOC_POINT);
}

static void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
}
END_TEST

START_TEST(test_hash_table_create) {
    ck_assert_ptr_nonnull(hash_table);
}
END_TEST

START_TEST(test_hash_table_insert_lookup) {
    Point p = {2, 4};
    Point p2 = {-6, 8};

    Point   *key1 = &p;
    Point   *key2 = &p2;
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_hash_table_insert(hash_table, key1, value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_hash_table_insert(hash_table, key2, value);

    int32_t *data = (int32_t *)aoc_hash_table_lookup(hash_table, key1);
    int32_t  expected = 5;
    int32_t  actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, key2);
    expected = 10;
    actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, key1);
    expected = 5;
    actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);
}
END_TEST

START_TEST(test_hash_table_pop) {
    Point p = {2, 4};
    Point p2 = {-6, 8};

    Point   *key1 = &p;
    Point   *key2 = &p2;
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_hash_table_insert(hash_table, key1, value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_hash_table_insert(hash_table, key2, value);

    int32_t *return_value = (int32_t *)aoc_hash_table_pop(hash_table, key1);
    ck_assert_ptr_nonnull(return_value);
    ck_assert_msg(5 == *return_value, "Expected %d, but got %d", 5, *return_value);
}
END_TEST

START_TEST(test_hash_table_insert_existing) {
    Point    p = {2, 4};
    Point   *key1 = &p;
    int32_t *value1 = (int32_t *)malloc(sizeof(int32_t));
    *value1 = 5;
    bool insert_result = aoc_hash_table_insert(hash_table, key1, value1);
    ck_assert(insert_result);
    int result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    ck_assert_msg(result == *value1, "Expected first lookup to be 5");
    int32_t *value2 = (int32_t *)malloc(sizeof(int32_t));
    *value2 = 10;
    insert_result = aoc_hash_table_insert(hash_table, key1, value2);
    ck_assert(!insert_result);
    result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    ck_assert_msg(result == *value1, "Expected second lookup to be 5");
}
END_TEST

START_TEST(test_hash_table_replace_existing) {
    Point    p = {2, 4};
    Point   *key1 = &p;
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    bool insert_result = aoc_hash_table_replace(hash_table, key1, value);
    ck_assert(insert_result);
    int result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    ck_assert(result == *value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    insert_result = aoc_hash_table_replace(hash_table, key1, value);
    ck_assert(!insert_result);
    result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    ck_assert(result == *value);
}
END_TEST

TCase *test_case_aoc_hash_point(void) {
    TCase *aoc_hash_point = tcase_create("aoc_hash_point");
    tcase_add_checked_fixture(aoc_hash_point, aoc_hash_table_setup, aoc_hash_table_teardown);
    tcase_add_test(aoc_hash_point, test_hash_table_create);
    tcase_add_test(aoc_hash_point, test_hash_table_insert_lookup);
    tcase_add_test(aoc_hash_point, test_hash_table_pop);
    tcase_add_test(aoc_hash_point, test_hash_table_insert_existing);
    tcase_add_test(aoc_hash_point, test_hash_table_replace_existing);

    return aoc_hash_point;
}
