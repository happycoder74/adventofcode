#include "check_grid.h"
#include <check.h>

Suite *test_aoc_grid(void) {
    Suite *s = suite_create("aoc_grid");

    suite_add_tcase(s, test_case_grid_int32());

    return s;
}
