#include "aoc_hash.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static AocHashTablePtr hash_table = NULL;
static AocHashTablePtr hash_table2 = NULL;
static void          **keys = NULL;
static char          **values = NULL;

static void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create(AOC_STR);
}

static void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
}

START_TEST(test_hash_table_create) {
    ck_assert_ptr_nonnull(hash_table);
}
END_TEST

START_TEST(test_hash_table_insert_lookup) {
    ck_assert_ptr_nonnull(hash_table);
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    aoc_hash_table_insert(hash_table, "KEY1", value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    aoc_hash_table_insert(hash_table, "KEY2", value);

    int32_t *data = (int32_t *)aoc_hash_table_lookup(hash_table, "KEY1");
    int32_t  expected = 5;
    int32_t  actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, "KEY2");
    expected = 10;
    actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);

    data = (int32_t *)aoc_hash_table_lookup(hash_table, "KEY1");
    expected = 5;
    actual = *data;
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", expected, actual);
}
END_TEST

START_TEST(aoc_hash_table_custom_str_table) {
    AocHashTablePtr ht = aoc_hash_table_create_custom(0, NULL, free, NULL, AOC_STR);

    aoc_hash_table_add(ht, strdup("First key"));

    aoc_hash_table_destroy(&ht);
}
END_TEST

/* START_TEST(test_hash_table_pop) { */
/*     int32_t *value = (int32_t *)malloc(sizeof(int32_t)); */
/*     *value = 5; */
/*     aoc_hash_table_insert(hash_table, int32_key(30), value); */
/*     value = (int32_t *)malloc(sizeof(int32_t)); */
/*     *value = 10; */
/*     aoc_hash_table_insert(hash_table, int32_key(20), value); */

/*     int32_t *return_value = (int32_t *)aoc_hash_table_pop(hash_table, int32_key(30)); */
/*     ck_assert_ptr_nonnull(return_value); */
/*     ck_assert_msg(5 == *return_value, "Expected %d, but got %d", 5, *return_value); */
/* } */
/* END_TEST */

/* START_TEST(.init = aoc_hash_table_load_6) { */
/*     int32_t value = 1001; */
/*     aoc_hash_table_insert(hash_table, int32_key(100), &value); */
/*     int32_t expected = 17; */
/*     int32_t actual = (int32_t)aoc_hash_table_size(hash_table); */
/*     ck_assert_msg(expected == actual, "Expected size of %d, but got %d", expected, actual); */
/*     expected = values[4]; */
/*     actual = *(int32_t *)aoc_hash_table_lookup(hash_table, keys[4]); */
/*     cr_expect_eq(expected, actual, "Expected value of key: %d to be %d but got %d",
 * *(int32_t*)keys[4].key, expected, actual); */
/* } */
/* END_TEST */

TCase *test_case_aoc_hash_table_str(void) {
    TCase *aoc_hash_table_str = tcase_create("aoc_hash_table_str");

    tcase_add_checked_fixture(aoc_hash_table_str, aoc_hash_table_setup, aoc_hash_table_teardown);
    tcase_add_test(aoc_hash_table_str, test_hash_table_create);
    tcase_add_test(aoc_hash_table_str, test_hash_table_insert_lookup);
    tcase_add_test(aoc_hash_table_str, test_hash_table_create);
    tcase_add_test(aoc_hash_table_str, test_hash_table_insert_lookup);
    tcase_add_test(aoc_hash_table_str, aoc_hash_table_custom_str_table);
    /* START_TEST(test_hash_table_pop); */
    /* START_TEST(.init = aoc_hash_table_load_6); */

    return aoc_hash_table_str;
}
