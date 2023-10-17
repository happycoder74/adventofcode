#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "aoc_array.h"
#include "aoc_types.h"

AocArrayPtr array = NULL;
AocArrayPtr array2 = NULL;

void aoc_int32_array_setup(void) {
    array = aoc_int32_array_new();
}

void aoc_int32_array_teardown(void) {
    aoc_int32_array_free(array);
    aoc_int32_array_free(array2);
}

TestSuite(aoc_int32_array, .init=aoc_int32_array_setup, .fini=aoc_int32_array_teardown);

Test(aoc_int32_array, test_int32_array_new) {
    cr_expect(array != NULL, "Expected new array to not be NULL");
}

Test(aoc_int32_array, test_int32_array_new_length) {
    cr_expect(array->length == 0, "Expected new array length to be 0");
}

Test(aoc_int32_array, test_int32_array_append) {
    int32_t value = 5;
    aoc_int32_array_append(array, value);
    int32_t *data = (int *)aoc_array_get_data(array);

    int64_t expected = value;
    int64_t actual = data[0];
    cr_expect(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);
}

Test(aoc_int32_array, test_int32_array_append_maxmin) {
    int32_t int32_maxmin[2] = {INT32_MAX, INT32_MIN};

    aoc_int32_array_append(array, int32_maxmin[0]);
    aoc_int32_array_append(array, int32_maxmin[1]);
    int32_t *data = (int *)aoc_array_get_data(array);
    cr_expect(data[0] == INT32_MAX, "Expected INT32_MAX (%d), got %d", INT32_MAX, data[0]);
    cr_expect(data[1] == INT32_MIN, "Expected INT32_MIN (%d), got %d", INT32_MIN, data[1]);
}

Test(aoc_int32_array, test_int32_array_index) {
    int32_t values[3] = {15, 7, -5};
    aoc_int32_array_append(array, values[0]);
    aoc_int32_array_append(array, values[1]);
    aoc_int32_array_append(array, values[2]);

    int32_t data = aoc_int32_array_index(array, 1);
    cr_expect(data == 7, "Expected value to be 7");
}

Test(aoc_int32_array, test_int32_array_remove_index) {
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

Test(aoc_int32_array, test_int32_array_prepend_to_empty) {
    int32_t value = 5;
    aoc_int32_array_prepend(array, value);
    int32_t *data = (int32_t *)aoc_array_get_data(array);

    int32_t expected = value;
    int32_t actual = data[0];
    cr_expect(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);
    cr_expect_eq(1, array->length, "Expected length to be [1] but got [%d]", (int)array->length);
}

Test(aoc_int32_array, test_int32_array_prepend_to_existing) {
    int32_t value = 5;
    aoc_int32_array_append(array, value);
    value = 10;
    aoc_int32_array_prepend(array, value);
    int32_t *data = (int32_t *)aoc_array_get_data(array);

    int32_t expected = value;
    int32_t actual = data[0];
    cr_expect(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);
    expected = 5;
    actual = data[1];
    cr_expect(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected, (int)actual);
    cr_expect_eq(2, array->length, "Expected length to be [2] but got [%d]", (int)array->length);
}

Test(aoc_int32_array, test_int32_array_copy) {
    int32_t values[5] = {1,2,3,5,7};

    for (int i = 0; i < 5; i++) {
        aoc_int32_array_append(array, values[i]);
    }

    array2 = aoc_array_copy(array);

    int32_t *data = (int32_t *)aoc_array_get_data(array);
    int32_t *data2 = (int32_t *)aoc_array_get_data(array2);
    cr_expect_neq(data, data2, "Seem to be same array, not copied");
    for(uint32_t i = 0; i < 5; i++) {
        cr_expect_eq(aoc_int32_array_index(array, i), aoc_int32_array_index(array2, i), "Expected array2[%d] = %d but got %d", i, values[i], aoc_int32_array_index(array2, i));
    }
}

