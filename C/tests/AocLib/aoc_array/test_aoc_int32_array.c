#include "aoc_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "aoc_array.h"
#include "criterion/internal/assert.h"

AocArrayPtr array = NULL;

void aoc_array_setup(void) {
    array = aoc_int32_array_new();
}

void aoc_array_teardown(void) {
    aoc_int32_array_free(array);
}

TestSuite(aoc_array, .init=aoc_array_setup, .fini=aoc_array_teardown);

Test(aoc_array, test_int32_array_new) {
    cr_expect(array != NULL, "Expected new array to not be NULL");
}

Test(aoc_array, test_int32_array_new_length) {
    cr_expect(array->length == 0, "Expected new array length to be 0");
}

Test(aoc_array, test_int32_array_append) {
    int32_t value = 5;
    aoc_int32_array_append(array, value);
    int32_t *data = (int *)aoc_array_get_data(array);

    cr_expect(data[0] == 5, "Expected value to be 5");
}

Test(aoc_array, test_int32_array_index) {
    int32_t values[3] = {15, 7, -5};
    aoc_int32_array_append(array, values[0]);
    aoc_int32_array_append(array, values[1]);
    aoc_int32_array_append(array, values[2]);

    int32_t data = aoc_int32_array_index(array, 1);
    cr_expect(data == 7, "Expected value to be 7");
}

Test(aoc_array, test_int32_array_remove_index) {
    int32_t values[3] = {15, 7, -5};
    aoc_int32_array_append(array, values[0]);
    aoc_int32_array_append(array, values[1]);
    aoc_int32_array_append(array, values[2]);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 0);

    cr_assert_not_null(res);
    cr_assert(aoc_int32_array_index(array, 0) == 7);
    cr_assert(aoc_int32_array_index(array, 1) == -5);
    cr_expect(aoc_array_length(array) == 2, "Expected a length of 2");
}
//
//     add_case(ts, "test_int32_array_index()", test_int32_array_index, NULL);
//     add_case(ts, "test_int32_array_remove_index()", test_int32_array_remove_index, NULL);
//     add_case(ts, "test_int32_array_append_to_null()", test_int32_array_append_to_null, NULL);
//     add_case(ts, "test_int32_array_append_to_wrong_type()", test_int32_array_append_to_wrong_type, NULL);
//     add_case(ts, "test_int32_array_insert_at_beginning()", test_int32_array_insert_at_beginning, NULL);
//
//     run_test_cases(ts);
//
//     test_report(ts);
//
//     tear_down(ts);
//
//     return EXIT_SUCCESS;
