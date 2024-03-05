#include "aoc_array.h"
#include "aoc_types.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocArrayPtr array = NULL;
AocArrayPtr array2 = NULL;

void aoc_double_array_setup(void) {
    array = aoc_double_array_new();
}

void aoc_double_array_teardown(void) {
    aoc_double_array_free(array);
    aoc_double_array_free(array2);
}

TestSuite(aoc_double_array, .init = aoc_double_array_setup, .fini = aoc_double_array_teardown);

Test(aoc_double_array, test_double_array_new) {
    cr_expect(array != NULL, "Expected new array to not be NULL");
}

Test(aoc_double_array, test_double_array_new_length) {
    cr_expect(array->length == 0, "Expected new array length to be 0");
}

Test(aoc_double_array, test_double_array_append) {
    double value = 5.125;
    aoc_double_array_append(array, value);
    double *data = (double *)aoc_array_get_data(array);

    double expected = value;
    double actual = data[0];
    cr_expect(actual == expected, "Expected value to be [%lf] but got [%lf]", expected, actual);
}

Test(aoc_double_array, test_double_array_index) {
    double values[3] = {15, 7, -5};
    aoc_double_array_append(array, values[0]);
    aoc_double_array_append(array, values[1]);
    aoc_double_array_append(array, values[2]);

    double data = aoc_double_array_index(array, 1);
    cr_expect(data == 7, "Expected value to be 7");
}

Test(aoc_double_array, test_double_array_remove_index) {
    double values[3] = {15, 7, -5};
    aoc_double_array_append(array, values[0]);
    aoc_double_array_append(array, values[1]);
    aoc_double_array_append(array, values[2]);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 0);

    cr_assert_not_null(res);
    cr_assert(aoc_double_array_index(array, 0) == 7);
    cr_assert(aoc_double_array_index(array, 1) == -5);
    cr_expect(aoc_array_length(array) == 2, "Expected a length of 2");
}

Test(aoc_double_array, test_double_array_prepend_to_empty) {
    double value = 5;
    aoc_double_array_prepend(array, value);
    double *data = (double *)aoc_array_get_data(array);

    double expected = value;
    double actual = data[0];
    cr_expect(actual == expected, "Expected value to be %lf but got %lf", expected, actual);
    cr_expect_eq(1, array->length, "Expected length to be '1' but got %u", (unsigned)array->length);
}

Test(aoc_double_array, test_double_array_prepend_to_existing) {
    double value = 5;
    aoc_double_array_append(array, value);
    value = 10;
    aoc_double_array_prepend(array, value);
    double *data = (double *)aoc_array_get_data(array);

    double expected = value;
    double actual = data[0];
    cr_expect(actual == expected, "Expected value to be %lf but got %lf", expected, actual);
    expected = 5;
    actual = data[1];
    cr_expect(actual == expected, "Expected value to be %lf but got %lf", expected, actual);
    cr_expect_eq(2, array->length, "Expected length to be '2' but got %u", (unsigned)array->length);
}

Test(aoc_double_array, test_double_array_copy) {
    double values[5] = {1, 2, 3, 5, 7};

    for (int i = 0; i < 5; i++) {
        aoc_double_array_append(array, values[i]);
    }

    array2 = aoc_array_copy(array);

    double *data = (double *)aoc_array_get_data(array);
    double *data2 = (double *)aoc_array_get_data(array2);
    cr_expect_neq(data, data2, "Seem to be same array, not copied");
    for (unsigned i = 0; i < 5; i++) {
        cr_expect_eq(aoc_double_array_index(array, i), aoc_double_array_index(array2, i), "Expected array2[%u] = %lf but got %lf", i, values[i], aoc_double_array_index(array2, i));
    }
}
