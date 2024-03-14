#include "aoc_hash.h"
#include "aoc_string.h"
#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

AocHashTablePtr hash_table = NULL;
AocHashTablePtr hash_table_str = NULL;

void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, NULL, NULL, NULL, AOC_PTR);
    hash_table_str = aoc_hash_table_create_custom(0, NULL, free, NULL, AOC_STR);
}

void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
    aoc_hash_table_destroy(&hash_table_str);
}

TestSuite(aoc_hash_table, .init = aoc_hash_table_setup, .fini = aoc_hash_table_teardown);

Test(aoc_hash_table, aoc_hash_table_contains_key) {
    void *key = (void *)10;
    void *lookup_key = (void *)10;

    aoc_hash_table_add(hash_table, key);

    cr_expect(aoc_hash_table_contains(hash_table, lookup_key), "Expected table to contain key");
}

Test(aoc_hash_table, aoc_hash_table_str_contains_key) {
    void *key = strdup("First key");
    void *lookup_key = strdup("First key");

    aoc_hash_table_add(hash_table_str, key);

    cr_expect(aoc_hash_table_contains(hash_table_str, lookup_key), "Expected table to contain key");
}

Test(aoc_hash_table, aoc_hash_table_does_not_contain_key) {
    void *key = (void *)20;
    void *lookup_key = (void *)30;

    aoc_hash_table_add(hash_table, key);

    cr_expect_not(aoc_hash_table_contains(hash_table, lookup_key),
                  "Expected table to not contain key");
}

Test(aoc_hash_table, aoc_hash_table_contains_null) {
    void *key = NULL;
    void *lookup_key = NULL;

    aoc_hash_table_add(hash_table, key);

    cr_expect(aoc_hash_table_contains(hash_table, lookup_key), "Expected table to contain key");
}

Test(aoc_hash_table, aoc_hash_table_does_not_contain_null) {
    void *key = (void *)10;
    void *lookup_key = NULL;

    cr_assert(aoc_hash_table_count(hash_table) == 0);
    aoc_hash_table_add(hash_table, key);

    cr_expect_not(aoc_hash_table_contains(hash_table, lookup_key),
                  "Expected table to not contain key");
}

Test(aoc_hash_table, aoc_hash_table_empty_does_not_contain_null) {
    void *lookup_key = NULL;

    cr_expect_not(aoc_hash_table_contains(hash_table, lookup_key),
                  "Expected table to not contain key");
}
