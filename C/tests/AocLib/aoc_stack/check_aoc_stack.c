#include "check_stack.h"
#include <check.h>

Suite *test_aoc_stack(void) {
    Suite *s = suite_create("aoc_stack");

    suite_add_tcase(s, test_case_aoc_stack());

    return s;
}
