#include "aoc_array.h"
#include "aoc_types.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static AocArrayPtr array = NULL;

void aoc_ptr_array_setup(void) {
    array = aoc_ptr_array_new();
}

void aoc_ptr_array_teardown(void) {
    aoc_ptr_array_free(array);
}

START_TEST(test_ptr_array_new) {
    ck_assert_msg(array != NULL, "Expected new array to not be NULL");
}
END_TEST

START_TEST(test_ptr_array_new_length) {
    ck_assert_msg(array->length == 0, "Expected new array length to be 0");
}
END_TEST

START_TEST(test_ptr_array_append) {
    char  str[] = "Test String";
    char *test_string = (char *)calloc(strlen(str) + 1, sizeof(char));
    test_string = strncpy(test_string, str, (strlen(str) + 1));
    aoc_ptr_array_append(array, test_string);
    char **data = (char **)aoc_array_get_data(array);
    char  *result = data[0];

    ck_assert_msg(!strcmp(result, "Test String"), "Expected value to be '%s', but got '%s'", str,
                  result);
    free(test_string);
}
END_TEST

START_TEST(test_ptr_array_prepend_to_empty) {
    char  str[] = "Test String";
    char *test_string = (char *)calloc(strlen(str) + 1, sizeof(char));
    test_string = strncpy(test_string, str, (strlen(str) + 1));
    aoc_ptr_array_prepend(array, test_string);
    char **data = (char **)aoc_array_get_data(array);
    ck_assert_msg(!strcmp((char *)data[0], str), "Expected value to be %s", str);
    free(test_string);
}
END_TEST

START_TEST(test_ptr_array_index) {
    int *val1 = (int *)malloc(sizeof(int));
    int *val2 = (int *)malloc(sizeof(int));
    aoc_ptr_array_append(array, val1);
    aoc_ptr_array_append(array, val2);

    int *data = aoc_ptr_array_index(array, 1);

    ck_assert_msg(val2 == data, "Expected '%p', got '%p'", (void *)val2, (void *)data);

    free(val1);
    free(val2);
}
END_TEST

START_TEST(test_ptr_array_remove_index) {
    int    *val1 = (int *)malloc(sizeof(int));
    int    *val2 = (int *)malloc(sizeof(int));
    double *val3 = (double *)malloc(sizeof(double));

    aoc_ptr_array_append(array, val1);
    aoc_ptr_array_append(array, val2);
    aoc_ptr_array_append(array, val3);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 1);

    ck_assert_ptr_nonnull(res);
    ck_assert_msg(array->length == 2, "Expected array length to be 2");
    ck_assert(aoc_ptr_array_index(array, 1) == (void *)val3);

    free(val1);
    free(val3);
}
END_TEST

START_TEST(test_ptr_array_pop_index) {
    ck_assert_ptr_nonnull(array);
    int    *val1 = (int *)malloc(sizeof(int));
    int    *val2 = (int *)malloc(sizeof(int));
    double *val3 = (double *)malloc(sizeof(double));
    double  check_val = 2.5;

    *val1 = 10;
    *val2 = 20;
    *val3 = check_val;

    aoc_ptr_array_append(array, val1);
    aoc_ptr_array_append(array, val2);
    aoc_ptr_array_append(array, val3);

    ck_assert(array->length == 3);
    int *return_value = aoc_array_pop_index(array, 1);
    ck_assert_msg(*return_value == 20, "Expected 20, got %d", *return_value);
    ck_assert(array->length == 2);
    ck_assert_int_eq(*(int *)aoc_ptr_array_index(array, 0), 10);
    ck_assert_double_eq(*(double *)aoc_ptr_array_index(array, 1), check_val);

    free(val1);
    free(return_value);
    free(val3);
}

TCase *test_case_ptr_array(void) {
    TCase *test_ptr_array = tcase_create("aoc_ptr_array");
    tcase_add_checked_fixture(test_ptr_array, aoc_ptr_array_setup, aoc_ptr_array_teardown);
    tcase_add_test(test_ptr_array, test_ptr_array_new);
    tcase_add_test(test_ptr_array, test_ptr_array_new_length);
    tcase_add_test(test_ptr_array, test_ptr_array_append);
    tcase_add_test(test_ptr_array, test_ptr_array_prepend_to_empty);
    tcase_add_test(test_ptr_array, test_ptr_array_index);
    tcase_add_test(test_ptr_array, test_ptr_array_remove_index);
    tcase_add_test(test_ptr_array, test_ptr_array_pop_index);

    return test_ptr_array;
}
