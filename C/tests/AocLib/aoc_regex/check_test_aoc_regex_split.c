#include "aoc_regex.h"
#include <check.h>

START_TEST(test_regex_split_NULL_should_return_NULL) {
    const char *string = NULL;
    char      **split_string = regex_split("ab", string, 0);

    ck_assert_ptr_null(split_string[0]);
}

START_TEST(test_regex_split_error_in_pattern_should_return_NULL) {
    const char string[] = "abc123";
    char     **split_string = regex_split("[ab", string, 0);

    ck_assert_ptr_null(split_string);
}

START_TEST(test_regex_split_single) {
    const char string[] = "kalle1anka";
    char     **split_string = regex_split("[0-9]", string, 0);
    unsigned   count = 0;
    while (split_string[count]) {
        count++;
    }

    ck_assert(count == 2);
}

START_TEST(test_regex_split_single_fail) {
    const char string[] = "kalle1anka";
    char     **split_string = regex_split("[2-9]", string, 0);
    unsigned   count = 0;
    while (split_string[count]) {
        count++;
    }

    ck_assert(count == 1);
}

START_TEST(test_regex_split_complex) {
    const char string[] = "rnqfzoisbqxbdlkgfh[lwlybvcsiupwnsyiljz]kmbgyaptjcsvwcltrdx["
                          "ntrpwgkrfeljpye]jxjdlgtntpljxaojufe";
    const char pattern[] = "\\[\\w+\\]";

    char **split_string = regex_split(pattern, string, 0);

    unsigned count;
    for (count = 0; split_string[count] != NULL; count++) {
        ;
    }

    ck_assert_msg(count == 3, "Expected count = 3, got %d", count);
    ck_assert_str_eq(split_string[0], "rnqfzoisbqxbdlkgfh");
    ck_assert_str_eq(split_string[1], "kmbgyaptjcsvwcltrdx");
    ck_assert_str_eq(split_string[2], "jxjdlgtntpljxaojufe");
    ck_assert_ptr_null(split_string[3]);
}

TCase *test_case_regex_split(void) {
    TCase *aoc_regex_split = tcase_create("aoc_regex_split");

    tcase_add_test(aoc_regex_split, test_regex_split_NULL_should_return_NULL);
    tcase_add_test(aoc_regex_split, test_regex_split_error_in_pattern_should_return_NULL);
    tcase_add_test(aoc_regex_split, test_regex_split_single);
    tcase_add_test(aoc_regex_split, test_regex_split_single_fail);
    tcase_add_test(aoc_regex_split, test_regex_split_complex);

    return aoc_regex_split;
}
