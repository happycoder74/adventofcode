#include "aoc_regex.h"
#include <check.h>

START_TEST(test_regex_count_three_matches) {
    const char string[] = "abacad";
    const char pattern[] = "(a)";

    regex_t re;
    regcomp(&re, pattern, 0);
    unsigned count = regex_match_count(&re, string);

    ck_assert_msg(count == 3, "Expected 3, got %d", count);
}

TCase *test_case_regex_count(void) {
    TCase *aoc_regex_count = tcase_create("aoc_regex_count");

    tcase_add_test(aoc_regex_count, test_regex_count_three_matches);

    return aoc_regex_count;
}
