#include "check_aoc_string.h"
#include <check.h>

Suite *test_aoc_string(void) {
    Suite *s = suite_create("aoc_string");

    suite_add_tcase(s, test_case_aoc_string());

    return s;
}
