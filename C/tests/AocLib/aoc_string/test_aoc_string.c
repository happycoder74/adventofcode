#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include <string.h>
#include "aoc_string.h"

char *str_dynamic = NULL;
char str_literal[] = "Test string";

void aoc_string_setup(void) {
    str_dynamic = (char *)calloc(strlen(str_literal) + 1, sizeof(char));
    strcpy(str_dynamic, str_literal);
}

void aoc_string_with_whitespace_setup(void) {
    char str_literal_with_ws[] = "   Test string   ";
    if(str_dynamic) {
        str_dynamic = (char *)realloc(str_dynamic, sizeof(char)*(strlen(str_literal_with_ws) + 1));
    }
    strcpy(str_dynamic, str_literal_with_ws);
}

void aoc_string_teardown(void) {
    if(str_dynamic)
        free(str_dynamic);
}

TestSuite(aoc_string, .init=aoc_string_setup, .fini=aoc_string_teardown);

Test(aoc_string, test_string_new, .description="Check that the new allocated dynamic string is not NULL") {
    cr_assert_not_null(str_dynamic, "Expected new array to not be NULL");
}

Test(aoc_string, test_string_new_length) {
    size_t expected = strlen(str_literal);
    size_t actual = strlen(str_dynamic);
    cr_expect_eq(actual, expected, "Actual = %d, Expected = %d", (int)actual, (int)expected);
}

Test(aoc_string, test_string_str_trim_all_whitespace,
        .init = aoc_string_with_whitespace_setup,
        .description = "Test if str_trim trims of all surrounding whitespace (spaces)") {

    char *expected = str_literal;
    char *actual  = str_trim(str_dynamic);

    cr_expect_str_eq(actual, expected, "Expected '%s' but got '%s", expected, actual);

}

