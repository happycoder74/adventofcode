#include "aoc_types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "aoc_array.h"
#include "criterion/internal/assert.h"

AocArrayPtr array = NULL;

void aoc_array_setup(void) {
    array = aoc_int64_array_new();
}

void aoc_array_teardown(void) {
    aoc_int64_array_free(array);
}

TestSuite(aoc_array, .init=aoc_array_setup, .fini=aoc_array_teardown);

Test(aoc_array, test_int64_array_new) {
    cr_expect_not_null(array, "Expected new array to not be NULL");
}

Test(aoc_array, test_int64_array_new_length) {
    cr_expect_eq(array->length, 0, "Expected new array length to be 0");
}

Test(aoc_array, test_int64_array_append) {
    int64_t value = 5;
    aoc_int64_array_append(array, value);
    int64_t *data = (int64_t *)aoc_array_get_data(array);

    int64_t expected = value;
    int64_t actual = data[0];
    cr_expect(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);
}

Test(aoc_array, test_int64_array_append_int64_maxmin) {
    int64_t values[2] = {INT64_MAX, INT64_MIN};
    aoc_int64_array_append(array, values[0]);
    aoc_int64_array_append(array, values[1]);
    int64_t *data = (int64_t *)aoc_array_get_data(array);

    cr_expect(data[0] == INT64_MAX, "Expected value to be INT64_MAX");
    cr_expect(data[1] == INT64_MIN, "Expected value to be INT64_MIN");
}

Test(aoc_array, test_int64_array_index) {
    int64_t values[3] = {15, 7, -5};
    aoc_int64_array_append(array, values[0]);
    aoc_int64_array_append(array, values[1]);
    aoc_int64_array_append(array, values[2]);

    int64_t data = aoc_int64_array_index(array, 1);
    cr_expect(data == 7, "Expected value to be 7");
}

Test(aoc_array, test_int64_array_remove_index) {
    int64_t values[3] = {15, 0, -5};
    aoc_int64_array_append(array, values[0]);
    aoc_int64_array_append(array, values[1]);
    aoc_int64_array_append(array, values[2]);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 0);

    cr_assert_not_null(res);
    cr_assert(aoc_int64_array_index(array, 0) == 0);
    cr_assert(aoc_int64_array_index(array, 1) == -5);
    cr_expect(aoc_array_length(array) == 2, "Expected a length of 2");
}
//
//     add_case(ts, "test_int64_array_index()", test_int64_array_index, NULL);
//     add_case(ts, "test_int64_array_remove_index()", test_int64_array_remove_index, NULL);
//     add_case(ts, "test_int64_array_append_to_null()", test_int64_array_append_to_null, NULL);
//     add_case(ts, "test_int64_array_append_to_wrong_type()", test_int64_array_append_to_wrong_type, NULL);
//     add_case(ts, "test_int64_array_insert_at_beginning()", test_int64_array_insert_at_beginning, NULL);
//
//     run_test_cases(ts);
//
//     test_report(ts);
//
//     tear_down(ts);
//
//     return EXIT_SUCCESS;
