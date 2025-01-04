#include "aoc_array.h"
#include "aoc_types.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocArrayPtr array = NULL;

static void aoc_array_setup(void) {
    array = aoc_str_array_new();
}

static void aoc_array_teardown(void) {
    free(array);
}

START_TEST(test_str_array_new) {
    ck_assert_msg(array != NULL, "Expected new array to not be NULL");
}
END_TEST

START_TEST(test_str_array_new_length) {
    ck_assert_msg(array->length == 0, "Expected new array length to be 0");
}
END_TEST

START_TEST(test_str_array_append_string_literal) {
    aoc_str_array_append(array, "Test String");
    char **data = (char **)aoc_array_get_data(array);
    ck_assert_msg(!strcmp(data[0], "Test String"), "Expected value to be \"Test String\"");
}
END_TEST

START_TEST(test_str_array_index) {
    aoc_str_array_append(array, "One");
    aoc_str_array_append(array, "Two");
    aoc_str_array_append(array, "Three");

    char *data = aoc_str_array_index(array, 1);
    ck_assert_msg(!strcmp(data, "Two"), "Expected value to be \"Two\"");
}
END_TEST

START_TEST(test_str_array_remove_index) {
    aoc_str_array_append(array, "One");
    aoc_str_array_append(array, "Two");
    aoc_str_array_append(array, "Three");

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 1);

    ck_assert_ptr_nonnull(res);
    ck_assert_msg(!strcmp(aoc_str_array_index(array, 0), "One"), "Expected value to be \"One\"");
    ck_assert_msg(!strcmp(aoc_str_array_index(array, 1), "Three"),
                  "Expected value to be \"Three\"");
    ck_assert_msg(aoc_array_length(array) == 2, "Expected a length of 2");
}
END_TEST

START_TEST(test_str_array_prepend_to_empty) {
    char str[] = "Test String Prepend";
    array = aoc_str_array_prepend(array, str);

    ck_assert_ptr_nonnull(array);
    ck_assert_msg(array->length == 1, "String length should be 1");
    ck_assert_str_eq(aoc_str_array_index(array, 0), str);
}
END_TEST

START_TEST(test_str_array_prepend_to_existing) {
    char str[] = "Test String Prepend";
    array = aoc_str_array_append(array, "First string (append)");
    array = aoc_str_array_prepend(array, str);

    ck_assert_ptr_nonnull(array);
    ck_assert_msg(array->length == 2, "String length should be 1");
    ck_assert_str_eq(aoc_str_array_index(array, 0), str);
    ck_assert_str_eq(aoc_str_array_index(array, 1), "First string (append)");
}
END_TEST

START_TEST(test_str_array_steal) {
    ck_assert_ptr_nonnull(array);
    aoc_str_array_append(array, "One");
    aoc_str_array_append(array, "Two");
    aoc_str_array_append(array, "Three");

    size_t length;
    char **array_data = aoc_array_steal(array, &length);

    ck_assert(length == 3);
    ck_assert_str_eq("One", array_data[0]);
    ck_assert_str_eq("Three", array_data[2]);
}
END_TEST

TCase *test_case_str_array(void) {
    TCase *test_aoc_str_array = tcase_create("test_aoc_str_array");

    tcase_add_checked_fixture(test_aoc_str_array, aoc_array_setup, aoc_array_teardown);
    tcase_add_test(test_aoc_str_array, test_str_array_new);
    tcase_add_test(test_aoc_str_array, test_str_array_new_length);
    tcase_add_test(test_aoc_str_array, test_str_array_append_string_literal);
    tcase_add_test(test_aoc_str_array, test_str_array_index);
    tcase_add_test(test_aoc_str_array, test_str_array_remove_index);
    tcase_add_test(test_aoc_str_array, test_str_array_prepend_to_empty);
    tcase_add_test(test_aoc_str_array, test_str_array_prepend_to_existing);
    tcase_add_test(test_aoc_str_array, test_str_array_steal);

    return test_aoc_str_array;
}
