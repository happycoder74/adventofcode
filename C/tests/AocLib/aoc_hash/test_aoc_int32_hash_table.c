#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "aoc_hash.h"

AocHashTablePtr hash_table = NULL;
AocHashTablePtr hash_table2 = NULL;
int32_t *keys = NULL;
int32_t *values = NULL;

static uint64_t aoc_int_hash(int32_t key) {
    return key;
}

static void aoc_int32_hash_table_load_N(size_t size) {
    if(!hash_table)
        return;

    keys = (int32_t *)calloc(size, sizeof(int32_t));
    values = (int32_t *)calloc(size, sizeof(int32_t));

    for (size_t i = 0; i < size; i++){
        keys[i] = i + 1;
        values[i] = i*100;
        aoc_int32_hash_table_insert(hash_table, keys[i], &values[i]);
    }
}

void aoc_int32_hash_table_load_6(void) {
    aoc_int32_hash_table_load_N(6);
}

void aoc_int32_hash_table_setup(void) {
    hash_table = aoc_int32_hash_table_create(3, aoc_int_hash);
}

void aoc_int32_hash_table_teardown(void) {
    if(hash_table)
        free(hash_table);

    if(keys)
        free(keys);
    if(values)
        free(values);
}

TestSuite(aoc_int32_hash_table, .init=aoc_int32_hash_table_setup, .fini=aoc_int32_hash_table_teardown);

Test(aoc_int32_hash_table, test_int32_hash_table_create) {
    cr_expect_not_null(hash_table, "Expected new hash_table to not be NULL");
}

Test(aoc_int32_hash_table, test_int32_hash_table_insert_lookup) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_int32_hash_table_insert(hash_table, 30, value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_int32_hash_table_insert(hash_table, 20, value);

    int32_t *data = (int *)aoc_int32_hash_table_lookup(hash_table, 30);
    int32_t expected = 5;
    int32_t actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);

    data = (int *)aoc_int32_hash_table_lookup(hash_table, 20);
    expected = 10;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);

    data = (int *)aoc_int32_hash_table_lookup(hash_table, 30);
    expected = 5;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);
}

Test(aoc_int32_hash_table, test_int32_hash_table_delete) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_int32_hash_table_insert(hash_table, 30, value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_int32_hash_table_insert(hash_table, 20, value);

    int32_t *return_value = (int32_t *)aoc_int32_hash_table_delete(hash_table, 30);
    cr_expect_not_null(return_value, "Did not expect return value from delete to be NULL");
    cr_expect_eq(5, *return_value, "Expected %d, but got %d", 5, *return_value);

}

Test(aoc_int32_hash_table, test_int32_hash_table_rehash, .init=aoc_int32_hash_table_load_6) {
    int32_t value = 1001;
    aoc_int32_hash_table_insert(hash_table, 100, &value);
    int32_t expected = 7;
    int32_t actual = (int32_t)aoc_hash_table_size(hash_table);
    cr_expect_eq(expected, actual, "Expected size of %d, but got %d", expected, actual);
    expected = values[4];
    actual = *(int32_t *)aoc_int32_hash_table_lookup(hash_table, keys[4]);
    cr_expect_eq(expected, actual, "Expected value of key: %d to be %d but got %d", keys[4], expected, actual);
}

