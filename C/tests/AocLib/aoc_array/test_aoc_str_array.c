#include "aoc_array.h"
#include "aoc_types.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocArrayPtr array = NULL;

void aoc_array_setup(void) {
    array = aoc_str_array_new();
}

void aoc_array_teardown(void) {
    free(array);
}

TestSuite(aoc_array, .init = aoc_array_setup, .fini = aoc_array_teardown);

Test(aoc_array, test_str_array_new) {
    cr_expect(array != NULL, "Expected new array to not be NULL");
}

Test(aoc_array, test_str_array_new_length) {
    cr_expect(array->length == 0, "Expected new array length to be 0");
}

Test(aoc_array, test_str_array_append_string_literal) {
    aoc_str_array_append(array, "Test String");
    char **data = (char **)aoc_array_get_data(array);
    cr_expect(!strcmp(data[0], "Test String"), "Expected value to be \"Test String\"");
}

Test(aoc_array, test_str_array_index) {
    aoc_str_array_append(array, "One");
    aoc_str_array_append(array, "Two");
    aoc_str_array_append(array, "Three");

    char *data = aoc_str_array_index(array, 1);
    cr_expect(!strcmp(data, "Two"), "Expected value to be \"Two\"");
}

Test(aoc_array, test_str_array_remove_index) {
    aoc_str_array_append(array, "One");
    aoc_str_array_append(array, "Two");
    aoc_str_array_append(array, "Three");

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 1);

    cr_assert_not_null(res);
    cr_expect(!strcmp(aoc_str_array_index(array, 0), "One"), "Expected value to be \"One\"");
    cr_expect(!strcmp(aoc_str_array_index(array, 1), "Three"), "Expected value to be \"Three\"");
    cr_expect(aoc_array_length(array) == 2, "Expected a length of 2");
}

Test(aoc_array, test_str_array_prepend_to_empty) {
    char str[] = "Test String Prepend";
    array = aoc_str_array_prepend(array, str);

    cr_assert_not_null(array);
    cr_expect_eq(array->length, 1, "String length should be 1");
    cr_expect_str_eq(aoc_str_array_index(array, 0), str, "Strings not equal");
}

Test(aoc_array, test_str_array_prepend_to_existing) {
    char str[] = "Test String Prepend";
    array = aoc_str_array_append(array, "First string (append)");
    array = aoc_str_array_prepend(array, str);

    cr_assert_not_null(array);
    cr_expect_eq(array->length, 2, "String length should be 1");
    cr_expect_str_eq(aoc_str_array_index(array, 0), str, "Strings not equal");
    cr_expect_str_eq(aoc_str_array_index(array, 1), "First string (append)", "Strings not equal");
}
