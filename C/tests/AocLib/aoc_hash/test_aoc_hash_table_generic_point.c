#include "aoc_hash.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocHashTablePtr hash_table = NULL;
AocHashTablePtr hash_table2 = NULL;

void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, NULL, NULL, free, AOC_KEY_POINT);
}

void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
}

TestSuite(aoc_hash_table, .init = aoc_hash_table_setup, .fini = aoc_hash_table_teardown);

Test(aoc_hash_table, test_hash_table_create) {
    cr_expect_not_null(hash_table, "Expected new hash_table to not be NULL");
}

Test(aoc_hash_table, test_hash_table_insert_lookup) {
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
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, key2);
    expected = 10;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, key1);
    expected = 5;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);
}

Test(aoc_hash_table, test_hash_table_delete) {
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

    int32_t *return_value = (int32_t *)aoc_hash_table_delete(hash_table, key1);
    cr_expect_not_null(return_value, "Did not expect return value from delete to be NULL");
    cr_expect_eq(5, *return_value, "Expected %d, but got %d", 5, *return_value);
}

Test(aoc_hash_table, test_hash_table_insert_existing) {
    Point    p = {2, 4};
    Point   *key1 = &p;
    int32_t *value1 = (int32_t *)malloc(sizeof(int32_t));
    *value1 = 5;
    bool insert_result = aoc_hash_table_insert(hash_table, key1, value1);
    cr_expect(insert_result, "Expected true value on first insert");
    int result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    cr_expect(result == *value1, "Expected first lookup to be 5");
    int32_t *value2 = (int32_t *)malloc(sizeof(int32_t));
    *value2 = 10;
    insert_result = aoc_hash_table_insert(hash_table, key1, value2);
    cr_expect_not(insert_result, "Expected false value on second insert");
    result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    cr_expect(result == *value1, "Expected second lookup to be 5");
}

Test(aoc_hash_table, test_hash_table_replace_existing) {
    Point    p = {2, 4};
    Point   *key1 = &p;
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    bool insert_result = aoc_hash_table_replace(hash_table, key1, value);
    cr_expect(insert_result, "Expected true value on first insert");
    int result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    cr_expect(result == *value, "Expected first lookup to be 5");
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    insert_result = aoc_hash_table_replace(hash_table, key1, value);
    cr_expect_not(insert_result, "Expected false value on second insert");
    result = *(int32_t *)aoc_hash_table_lookup(hash_table, key1);
    cr_expect(result == *value, "Expected second lookup to be 10");
}
