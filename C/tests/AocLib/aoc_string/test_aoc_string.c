#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "aoc_string.h"

char *str_dynamic = NULL;
char str_literal[] = "Test string";

void aoc_string_setup(void) {
    str_dynamic = (char *)calloc(strlen(str_literal) + 1, sizeof(char));
}

void aoc_string_teardown(void) {
    free(str_dynamic);
}

TestSuite(aoc_string, .init=aoc_string_setup, .fini=aoc_string_teardown);

Test(aoc_string, test_string_new) {
    cr_expect(str_dynamic != NULL, "Expected new array to not be NULL");
}

Test(aoc_string, test_string_new_length) {
    size_t expected = strlen(str_literal);
    size_t actual = strlen(str_dynamic);
    cr_expect_eq(actual, expected, "Actual = [%u], Expected = [%u]", actual, expected);
}

