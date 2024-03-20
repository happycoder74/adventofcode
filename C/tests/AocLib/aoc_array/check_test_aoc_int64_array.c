#include "aoc_array.h"
#include "aoc_types.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocArrayPtr array = NULL;

static void aoc_array_setup(void) {
    array = aoc_int64_array_new();
}

static void aoc_array_teardown(void) {
    aoc_int64_array_free(array);
}

START_TEST(test_int64_array_new) {
    ck_assert_ptr_nonnull(array);
}
END_TEST

START_TEST(test_int64_array_new_length) {
    ck_assert_ptr_nonnull(array);
    ck_assert_msg(array->length == 0, "Expected new array length to be 0");
}
END_TEST

START_TEST(test_int64_array_append) {
    ck_assert_ptr_nonnull(array);
    int64_t value = 5;
    aoc_int64_array_append(array, value);
    int64_t *data = (int64_t *)aoc_array_get_data(array);

    int64_t expected = value;
    int64_t actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
}
END_TEST

START_TEST(test_int64_array_append_int64_maxmin) {
    ck_assert_ptr_nonnull(array);
    int64_t values[2] = {INT64_MAX, INT64_MIN};
    aoc_int64_array_append(array, values[0]);
    aoc_int64_array_append(array, values[1]);
    int64_t *data = (int64_t *)aoc_array_get_data(array);

    ck_assert_msg(data[0] == INT64_MAX, "Expected value to be INT64_MAX");
    ck_assert_msg(data[1] == INT64_MIN, "Expected value to be INT64_MIN");
}
END_TEST

START_TEST(test_int64_array_index) {
    int64_t values[3] = {15, 7, -5};
    ck_assert_ptr_nonnull(array);
    aoc_int64_array_append(array, values[0]);
    aoc_int64_array_append(array, values[1]);
    aoc_int64_array_append(array, values[2]);

    int64_t data = aoc_int64_array_index(array, 1);
    ck_assert(data == 7);
}
END_TEST

START_TEST(test_int64_array_remove_index) {
    ck_assert_ptr_nonnull(array);
    int64_t values[3] = {15, 0, -5};
    aoc_int64_array_append(array, values[0]);
    aoc_int64_array_append(array, values[1]);
    aoc_int64_array_append(array, values[2]);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 0);

    ck_assert_ptr_nonnull(res);
    ck_assert(aoc_int64_array_index(array, 0) == 0);
    ck_assert(aoc_int64_array_index(array, 1) == -5);
    ck_assert_msg(aoc_array_length(array) == 2, "Expected a length of 2");
}
END_TEST

START_TEST(test_int64_array_prepend_to_empty) {
    ck_assert_ptr_nonnull(array);
    int64_t value = 5;
    aoc_int64_array_prepend(array, value);
    int64_t *data = (int64_t *)aoc_array_get_data(array);

    int64_t expected = value;
    int64_t actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
    ck_assert_msg(1 == array->length, "Expected length to be [1] but got [%d]", (int)array->length);
}
END_TEST

START_TEST(test_int64_array_prepend_to_existing) {
    ck_assert_ptr_nonnull(array);
    int64_t value = 5;
    aoc_int64_array_append(array, value);
    value = 10;
    aoc_int64_array_prepend(array, value);
    int64_t *data = (int64_t *)aoc_array_get_data(array);

    int64_t expected = value;
    int64_t actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
    expected = 5;
    actual = data[1];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
    ck_assert_msg(2 == array->length, "Expected length to be [2] but got [%d]", (int)array->length);
}
END_TEST

TCase *test_case_int64_array(void) {
    TCase *test_int64_array = tcase_create("test_int64_array");

    tcase_add_checked_fixture(test_int64_array, aoc_array_setup, aoc_array_teardown);
    tcase_add_test(test_int64_array, test_int64_array_new);
    tcase_add_test(test_int64_array, test_int64_array_new_length);
    tcase_add_test(test_int64_array, test_int64_array_append);
    tcase_add_test(test_int64_array, test_int64_array_append_int64_maxmin);
    tcase_add_test(test_int64_array, test_int64_array_index);
    tcase_add_test(test_int64_array, test_int64_array_remove_index);
    tcase_add_test(test_int64_array, test_int64_array_prepend_to_empty);
    tcase_add_test(test_int64_array, test_int64_array_prepend_to_existing);

    return test_int64_array;
}
