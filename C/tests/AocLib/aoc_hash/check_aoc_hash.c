#include "check_hash.h"
#include <check.h>

Suite *test_aoc_hash_table(void) {
    Suite *s = suite_create("aoc_hash_table");
    suite_add_tcase(s, test_case_aoc_hash_fundamental());
    suite_add_tcase(s, test_case_aoc_hash_foreach());
    suite_add_tcase(s, test_case_aoc_hash_buckets());
    suite_add_tcase(s, test_case_aoc_hash_contains());
    suite_add_tcase(s, test_case_aoc_hash_char());
    suite_add_tcase(s, test_case_aoc_hash_int32());
    suite_add_tcase(s, test_case_aoc_hash_int32_loaded());
    suite_add_tcase(s, test_case_aoc_hash_int32_in_ptr());
    suite_add_tcase(s, test_case_aoc_hash_point());
    suite_add_tcase(s, test_case_aoc_hash_table_str());
    return s;
}
