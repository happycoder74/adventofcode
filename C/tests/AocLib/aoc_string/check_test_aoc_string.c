#include "aoc_string.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *str_dynamic = NULL;
static char  str_literal[] = "Test string";

static void aoc_string_setup(void) {
    size_t length = strlen(str_literal) + 1;
    str_dynamic = (char *)calloc(length, sizeof(char));
    strncpy(str_dynamic, str_literal, length);
}

static void aoc_string_with_whitespace_setup(void) {
    char str_literal_with_ws[] = "   Test string   ";
    size_t length = strlen(str_literal_with_ws) + 1;
    if (str_dynamic) {
        char *new_ptr =
            (char *)realloc(str_dynamic, sizeof(char) * length);
        if (new_ptr) {
            str_dynamic = new_ptr;
        }
        strncpy(str_dynamic, str_literal_with_ws, length);
    }
}

static void aoc_string_teardown(void) {
    if (str_dynamic) {
        free(str_dynamic);
    }
}

START_TEST(test_string_new) {
    ck_assert_ptr_nonnull(str_dynamic);
}
END_TEST

START_TEST(test_string_new_length) {
    size_t expected = strlen(str_literal);
    size_t actual = strlen(str_dynamic);
    ck_assert_msg(actual == expected, "Actual = %d, Expected = %d", (int)actual, (int)expected);
}
END_TEST

START_TEST(test_string_str_trim_all_whitespace) {
    aoc_string_with_whitespace_setup();
    char *expected = str_literal;
    char *actual = str_trim(str_dynamic);

    ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_str_split) {
    char  *test_string = "Here I Come";
    char **result = str_split(test_string, " ", 0);

    ck_assert_str_eq(result[0], "Here");
    ck_assert_str_eq(result[1], "I");
    ck_assert_str_eq(result[2], "Come");
}
END_TEST

START_TEST(test_str_split_max_tokens) {
    char  *test_string = "Here I Come";
    char **result = str_split(test_string, " ", 2);

    ck_assert_str_eq(result[0], "Here");
    ck_assert_str_eq(result[1], "I Come");
}
END_TEST

TCase *test_case_aoc_string(void) {
    TCase *test_aoc_string = tcase_create("test_aoc_string");

    tcase_add_checked_fixture(test_aoc_string, aoc_string_setup, aoc_string_teardown);
    tcase_add_test(test_aoc_string, test_string_new);
    tcase_add_test(test_aoc_string, test_string_new_length);
    tcase_add_test(test_aoc_string, test_string_str_trim_all_whitespace);
    tcase_add_test(test_aoc_string, test_str_split);
    tcase_add_test(test_aoc_string, test_str_split_max_tokens);

    return test_aoc_string;
}
