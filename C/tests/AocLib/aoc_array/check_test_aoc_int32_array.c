#include "aoc_array.h"
#include "aoc_types.h"
#include "check.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocArrayPtr array = NULL;

void aoc_int32_array_setup(void) {
    array = aoc_int32_array_new();
}

void aoc_int32_array_teardown(void) {
    aoc_int32_array_free(array);
}

START_TEST(test_int32_array_new) {
    ck_assert_msg(array != NULL, "Expected new array to not be NULL");
}
END_TEST

START_TEST(test_int32_array_new_length) {
    ck_assert(array != NULL);
    ck_assert_msg(array->length == 0, "Expected new array length to be 0");
}
END_TEST

START_TEST(test_int32_array_append) {
    int32_t value = 5;
    aoc_int32_array_append(array, value);
    int32_t *data = (int *)aoc_array_get_data(array);

    int64_t expected = value;
    int64_t actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
}
END_TEST

START_TEST(test_int32_array_append_maxmin) {
    int32_t int32_maxmin[2] = {INT32_MAX, INT32_MIN};

    aoc_int32_array_append(array, int32_maxmin[0]);
    aoc_int32_array_append(array, int32_maxmin[1]);
    int32_t *data = (int *)aoc_array_get_data(array);
    ck_assert_msg(data[0] == INT32_MAX, "Expected INT32_MAX (%d), got %d", INT32_MAX, data[0]);
    ck_assert_msg(data[1] == INT32_MIN, "Expected INT32_MIN (%d), got %d", INT32_MIN, data[1]);
}
END_TEST

START_TEST(test_int32_array_index) {
    int32_t values[3] = {15, 7, -5};
    aoc_int32_array_append(array, values[0]);
    aoc_int32_array_append(array, values[1]);
    aoc_int32_array_append(array, values[2]);

    int32_t data = aoc_int32_array_index(array, 1);
    ck_assert_msg(data == 7, "Expected value to be 7");
}
END_TEST

START_TEST(test_int32_array_index_out_of_bounds) {
    int32_t values[3] = {15, 7, -5};
    aoc_int32_array_append(array, values[0]);
    aoc_int32_array_append(array, values[1]);
    aoc_int32_array_append(array, values[2]);

    int32_t *data = aoc_array_index(array, 3);
    ck_assert_msg(data == NULL, "Expected to return NULL");
}
END_TEST

START_TEST(test_int32_array_remove_index) {
    int32_t values[3] = {15, 7, -5};
    aoc_int32_array_append(array, values[0]);
    aoc_int32_array_append(array, values[1]);
    aoc_int32_array_append(array, values[2]);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 0);

    ck_assert_ptr_nonnull(res);
    ck_assert(aoc_int32_array_index(array, 0) == 7);
    ck_assert(aoc_int32_array_index(array, 1) == -5);
    ck_assert_msg(aoc_array_length(array) == 2, "Expected a length of 2");
}
END_TEST

START_TEST(test_int32_array_prepend_to_empty) {
    int32_t value = 5;
    aoc_int32_array_prepend(array, value);
    int32_t *data = (int32_t *)aoc_array_get_data(array);

    int32_t expected = value;
    int32_t actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
    ck_assert_msg(1 == array->length, "Expected length to be [1] but got [%d]", (int)array->length);
}
END_TEST

START_TEST(test_int32_array_prepend_to_existing) {
    int32_t value = 5;
    aoc_int32_array_append(array, value);
    value = 10;
    aoc_int32_array_prepend(array, value);
    int32_t *data = (int32_t *)aoc_array_get_data(array);

    int32_t expected = value;
    int32_t actual = data[0];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
    expected = 5;
    actual = data[1];
    ck_assert_msg(actual == expected, "Expected value to be [%d] but got [%d]", (int)expected,
                  (int)actual);
    ck_assert_msg(2 == array->length, "Expected length to be [2] but got [%d]", (int)array->length);
}
END_TEST

START_TEST(test_int32_array_copy) {
    int32_t values[5] = {1, 2, 3, 5, 7};

    for (int i = 0; i < 5; i++) {
        aoc_int32_array_append(array, values[i]);
    }

    AocArrayPtr array2 = aoc_array_copy(array);

    int32_t *data = (int32_t *)aoc_array_get_data(array);
    int32_t *data2 = (int32_t *)aoc_array_get_data(array2);
    ck_assert_msg(data != data2, "Seem to be same array, not copied");
    for (uint32_t i = 0; i < 5; i++) {
        ck_assert_msg(aoc_int32_array_index(array, i) == aoc_int32_array_index(array2, i),
                      "Expected array2[%d] = %d but got %d", i, values[i],
                      aoc_int32_array_index(array2, i));
    }

    aoc_int32_array_free(array2);
}
END_TEST

TCase *test_case_int32_array(void) {
    TCase *test_int32_array = tcase_create("aoc_int32_array");
    tcase_add_checked_fixture(test_int32_array, aoc_int32_array_setup, aoc_int32_array_teardown);
    tcase_add_test(test_int32_array, test_int32_array_new);
    tcase_add_test(test_int32_array, test_int32_array_copy);
    tcase_add_test(test_int32_array, test_int32_array_new_length);
    tcase_add_test(test_int32_array, test_int32_array_append);
    tcase_add_test(test_int32_array, test_int32_array_append_maxmin);
    tcase_add_test(test_int32_array, test_int32_array_index);
    tcase_add_test(test_int32_array, test_int32_array_index_out_of_bounds);
    tcase_add_test(test_int32_array, test_int32_array_remove_index);
    tcase_add_test(test_int32_array, test_int32_array_prepend_to_empty);
    tcase_add_test(test_int32_array, test_int32_array_prepend_to_existing);

    return test_int32_array;
}
