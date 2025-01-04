#include "check_array.h"
#include <check.h>

Suite *test_aoc_array(void) {
    Suite *s = suite_create("aoc_array");

    suite_add_tcase(s, test_case_int32_array());
    suite_add_tcase(s, test_case_ptr_array());
    suite_add_tcase(s, test_case_double_array());
    suite_add_tcase(s, test_case_str_array());
    suite_add_tcase(s, test_case_int64_array());

    return s;
}
