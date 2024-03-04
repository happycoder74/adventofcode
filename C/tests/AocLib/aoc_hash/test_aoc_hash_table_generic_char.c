#include "aoc_hash.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocHashTablePtr hash_table = NULL;
AocHashTablePtr hash_table2 = NULL;
int32_t        *keys = NULL;
int32_t        *values = NULL;

void aoc_hash_table_setup(void) {
    hash_table = aoc_hash_table_create_custom(0, NULL, NULL, free, AOC_KEY_CHAR);
}

void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash_table);
}

TestSuite(aoc_hash_table, .init = aoc_hash_table_setup, .fini = aoc_hash_table_teardown);

Test(aoc_hash_table, test_hash_table_create) {
    cr_expect_not_null(hash_table, "Expected new hash_table to not be NULL");
}

Test(aoc_hash_table, test_hash_table_insert_lookup) {
    char     lookups[] = {'a', 'b', 'a', 'b'};
    int32_t *value = (int32_t *)malloc(sizeof(int32_t));
    *value = 5;
    char key1 = lookups[0];
    aoc_hash_table_insert(hash_table, &key1, value);
    value = (int32_t *)malloc(sizeof(int32_t));
    *value = 10;
    char key2 = lookups[1];
    aoc_hash_table_insert(hash_table, &key2, value);

    char     key3 = lookups[2];
    int32_t *data = (int32_t *)aoc_hash_table_lookup(hash_table, &key3);
    int32_t  expected = 5;
    int32_t  actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);

    char key4 = lookups[3];
    ;
    data = (int32_t *)aoc_hash_table_lookup(hash_table, &key4);
    expected = 10;
    actual = *data;
    cr_expect_eq(actual, expected, "Expected value to be [%d] but got [%d]", expected, actual);
}

/* Test(aoc_hash_table, test_hash_table_delete) { */
/*     int32_t *value = (int32_t *)malloc(sizeof(int32_t)); */
/*     *value = 5; */
/*     int32_t key1 = 30; */
/*     bool    insert_result; */
/*     insert_result = aoc_hash_table_insert(hash_table, &key1, value); */
/*     cr_assert(insert_result); */
/*     value = (int32_t *)malloc(sizeof(int32_t)); */
/*     *value = 10; */
/*     int32_t key2 = 20; */
/*     insert_result = aoc_hash_table_insert(hash_table, &key2, value); */
/*     cr_assert(insert_result); */

/*     int32_t  key3 = 30; */
/*     int32_t *return_value = (int32_t *)aoc_hash_table_delete(hash_table, &key3); */
/*     cr_expect_not_null(return_value, "Did not expect return value from delete to be NULL"); */
/*     cr_expect_eq(5, *return_value, "Expected %d, but got %d", 5, *return_value); */
/* } */
