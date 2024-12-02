#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_types.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocArrayPtr array = NULL;

static void aoc_double_array_setup(void) {
    array = aoc_double_array_new();
}

static void aoc_double_array_teardown(void) {
    aoc_double_array_free(array);
}

START_TEST(test_double_array_new) {
    ck_assert_msg(array != NULL, "Expected new array to not be NULL");
}
END_TEST

START_TEST(test_double_array_new_length) {
    ck_assert_msg(array->length == 0, "Expected new array length to be 0");
}
END_TEST

START_TEST(test_double_array_append) {
    double value = 5.125;
    aoc_double_array_append(array, value);
    double *data = (double *)aoc_array_get_data(array);

    double expected = value;
    double actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%lf] but got [%lf]", expected, actual);
}
END_TEST

START_TEST(test_double_array_index) {
    double values[3] = {15, 7, -5};
    aoc_double_array_append(array, values[0]);
    aoc_double_array_append(array, values[1]);
    aoc_double_array_append(array, values[2]);

    double data = aoc_double_array_index(array, 1);
    ck_assert_msg(data == 7, "Expected value to be 7");
}
END_TEST

START_TEST(test_double_array_remove_index) {
    double values[3] = {15, 7, -5};
    aoc_double_array_append(array, values[0]);
    aoc_double_array_append(array, values[1]);
    aoc_double_array_append(array, values[2]);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 0);

    ck_assert_ptr_nonnull(res);
    ck_assert(aoc_double_array_index(array, 0) == 7);
    ck_assert(aoc_double_array_index(array, 1) == -5);
    ck_assert_msg(aoc_array_length(array) == 2, "Expected a length of 2");
}
END_TEST

START_TEST(test_double_array_prepend_to_empty) {
    double value = 5;
    aoc_double_array_prepend(array, value);
    double *data = (double *)aoc_array_get_data(array);

    double expected = value;
    double actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be %lf but got %lf", expected, actual);
    ck_assert_msg(1 == array->length, "Expected length to be '1' but got %u",
                  (unsigned)array->length);
}
END_TEST

START_TEST(test_double_array_prepend_to_existing) {
    double value = 5;
    aoc_double_array_append(array, value);
    value = 10;
    aoc_double_array_prepend(array, value);
    double *data = (double *)aoc_array_get_data(array);

    double expected = value;
    double actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be %lf but got %lf", expected, actual);
    expected = 5;
    actual = data[1];
    ck_assert_msg(actual == expected, "Expected value to be %lf but got %lf", expected, actual);
    ck_assert_msg(2 == array->length, "Expected length to be '2' but got %u",
                  (unsigned)array->length);
}
END_TEST

START_TEST(test_double_array_copy) {
    double      values[5] = {1, 2, 3, 5, 7};
    AocArrayPtr array2 = NULL;

    for (int i = 0; i < 5; i++) {
        aoc_double_array_append(array, values[i]);
    }

    array2 = aoc_array_copy(array);

    double *data = (double *)aoc_array_get_data(array);
    double *data2 = (double *)aoc_array_get_data(array2);
    ck_assert_msg(data != data2, "Seem to be same array, not copied");
    for (unsigned i = 0; i < 5; i++) {
        ck_assert_msg(aoc_double_array_index(array, i) == aoc_double_array_index(array2, i),
                      "Expected array2[%u] = %lf but got %lf", i, values[i],
                      aoc_double_array_index(array2, i));
    }
    aoc_double_array_free(array2);
}
END_TEST

TCase *test_case_double_array(void) {
    TCase *test_aoc_double_array = tcase_create("test_case_aoc_double_array");

    tcase_add_checked_fixture(test_aoc_double_array, aoc_double_array_setup,
                              aoc_double_array_teardown);
    tcase_add_test(test_aoc_double_array, test_double_array_new);
    tcase_add_test(test_aoc_double_array, test_double_array_new_length);
    tcase_add_test(test_aoc_double_array, test_double_array_append);
    tcase_add_test(test_aoc_double_array, test_double_array_index);
    tcase_add_test(test_aoc_double_array, test_double_array_remove_index);
    tcase_add_test(test_aoc_double_array, test_double_array_prepend_to_empty);
    tcase_add_test(test_aoc_double_array, test_double_array_prepend_to_existing);
    tcase_add_test(test_aoc_double_array, test_double_array_copy);

    return test_aoc_double_array;
}
