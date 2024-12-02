#include "check_sets.h"
#include <check.h>

Suite *test_aoc_set(void) {
    Suite *s = suite_create("aoc_sets");

    TCase *test_int32_sets = test_case_aoc_set_int32();

    suite_add_tcase(s, test_int32_sets);

    return s;
}
