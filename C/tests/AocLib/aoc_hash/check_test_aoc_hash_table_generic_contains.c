#include "aoc_hash.h"
#include <check.h>
#include <stdlib.h>
#include <string.h>

static AocHashTablePtr hash_table = NULL;
static AocHashTablePtr hash_table_str = NULL;

static void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, NULL, NULL, NULL, AOC_PTR);
    hash_table_str = aoc_hash_table_create_custom(0, NULL, free, NULL, AOC_STR);
}

static void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
    aoc_hash_table_destroy(&hash_table_str);
}

START_TEST(aoc_hash_table_contains_key) {
    void *key = (void *)10;
    void *lookup_key = (void *)10;

    aoc_hash_table_add(hash_table, key);

    ck_assert_msg(aoc_hash_table_contains(hash_table, lookup_key), "Expected table to contain key");
}
END_TEST

START_TEST(aoc_hash_table_str_contains_key) {
    void *key = strdup("First key");
    void *lookup_key = strdup("First key");

    aoc_hash_table_add(hash_table_str, key);

    ck_assert_msg(aoc_hash_table_contains(hash_table_str, lookup_key),
                  "Expected table to contain key");
}
END_TEST

START_TEST(aoc_hash_table_does_not_contain_key) {
    void *key = (void *)20;
    void *lookup_key = (void *)30;

    aoc_hash_table_add(hash_table, key);

    ck_assert_msg(!aoc_hash_table_contains(hash_table, lookup_key),
                  "Expected table to not contain key");
}
END_TEST

START_TEST(aoc_hash_table_contains_null) {
    void *key = NULL;
    void *lookup_key = NULL;

    aoc_hash_table_add(hash_table, key);

    ck_assert_msg(aoc_hash_table_contains(hash_table, lookup_key), "Expected table to contain key");
}
END_TEST

START_TEST(aoc_hash_table_does_not_contain_null) {
    void *key = (void *)10;
    void *lookup_key = NULL;

    ck_assert(aoc_hash_table_count(hash_table) == 0);
    aoc_hash_table_add(hash_table, key);

    ck_assert_msg(!aoc_hash_table_contains(hash_table, lookup_key),
                  "Expected table to not contain key");
}
END_TEST

START_TEST(aoc_hash_table_empty_does_not_contain_null) {
    void *lookup_key = NULL;

    ck_assert_msg(!aoc_hash_table_contains(hash_table, lookup_key),
                  "Expected table to not contain key");
}
END_TEST

TCase *test_case_aoc_hash_contains(void) {
    TCase *test_aoc_hash_contains = tcase_create("test_aoc_hash_table_contains");

    tcase_add_checked_fixture(test_aoc_hash_contains, aoc_hash_table_setup,
                              aoc_hash_table_teardown);
    tcase_add_test(test_aoc_hash_contains, aoc_hash_table_contains_key);
    tcase_add_test(test_aoc_hash_contains, aoc_hash_table_str_contains_key);
    tcase_add_test(test_aoc_hash_contains, aoc_hash_table_does_not_contain_key);
    tcase_add_test(test_aoc_hash_contains, aoc_hash_table_contains_null);
    tcase_add_test(test_aoc_hash_contains, aoc_hash_table_does_not_contain_null);
    tcase_add_test(test_aoc_hash_contains, aoc_hash_table_empty_does_not_contain_null);

    return test_aoc_hash_contains;
}
