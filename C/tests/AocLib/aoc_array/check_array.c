#include "check_array.h"
#include <check.h>

Suite *test_aoc_array(void) {
    Suite *s = suite_create("test_aoc_array");

    suite_add_tcase(s, test_case_int32_array());
    suite_add_tcase(s, test_case_ptr_array());

    return s;
}
