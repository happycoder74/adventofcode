#include "aoc_hash.h"
#include "aoc_string.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocHashTablePtr hash_table = NULL;
AocHashTablePtr hash_table2 = NULL;
void          **keys = NULL;
char          **values = NULL;

void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create(AOC_STR);
}

void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
}

TestSuite(aoc_hash_table, .init = aoc_hash_table_setup, .fini = aoc_hash_table_teardown);

Test(aoc_hash_table, test_hash_table_create) {
    cr_expect_not_null(hash_table, "Expected new hash_table to not be NULL");
}

Test(aoc_hash_table, test_hash_table_insert_lookup) {
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_hash_table_insert(hash_table, "KEY1", value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_hash_table_insert(hash_table, "KEY2", value);

    int32_t *data = (int32_t *)aoc_hash_table_lookup(hash_table, "KEY1");
    int32_t  expected = 5;
    int32_t  actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, "KEY2");
    expected = 10;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, "KEY1");
    expected = 5;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);
}

Test(aoc_hash_table, aoc_hash_table_custom_str_table) {
    AocHashTablePtr ht = aoc_hash_table_create_custom(0, NULL, free, NULL, AOC_STR);

    aoc_hash_table_add(ht, strdup("First key"));

    aoc_hash_table_destroy(&ht);
}

/* Test(aoc_hash_table, test_hash_table_pop) { */
/*     int32_t *value = (int32_t *)malloc(sizeof(int32_t)); */
/*     *value = 5; */
/*     aoc_hash_table_insert(hash_table, int32_key(30), value); */
/*     value = (int32_t *)malloc(sizeof(int32_t)); */
/*     *value = 10; */
/*     aoc_hash_table_insert(hash_table, int32_key(20), value); */

/*     int32_t *return_value = (int32_t *)aoc_hash_table_pop(hash_table, int32_key(30)); */
/*     cr_expect_not_null(return_value, "Did not expect return value from pop to be NULL"); */
/*     cr_expect_eq(5, *return_value, "Expected %d, but got %d", 5, *return_value); */
/* } */

/* Test(aoc_hash_table, test_hash_table_rehash, .init = aoc_hash_table_load_6) { */
/*     int32_t value = 1001; */
/*     aoc_hash_table_insert(hash_table, int32_key(100), &value); */
/*     int32_t expected = 17; */
/*     int32_t actual = (int32_t)aoc_hash_table_size(hash_table); */
/*     cr_expect_eq(expected, actual, "Expected size of %d, but got %d", expected, actual); */
/*     expected = values[4]; */
/*     actual = *(int32_t *)aoc_hash_table_lookup(hash_table, keys[4]); */
/*     cr_expect_eq(expected, actual, "Expected value of key: %d to be %d but got %d",
 * *(int32_t*)keys[4].key, expected, actual); */
/* } */
