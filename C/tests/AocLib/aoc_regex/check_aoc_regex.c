#include "check_regex.h"
#include <check.h>

Suite *test_aoc_regex(void) {
    Suite *s = suite_create("aoc_regex");

    suite_add_tcase(s, test_case_regex_count());
    suite_add_tcase(s, test_case_regex_split());

    return s;
}
