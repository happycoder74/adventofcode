#include "aoc_regex.h"
#include <criterion/criterion.h>

Test(aoc_regex, test_regex_split_NULL_should_return_NULL) {
    const char *string = NULL;
    char      **split_string = regex_split("ab", string, 0);

    cr_expect(split_string[0] == NULL);
}

Test(aoc_regex, test_regex_split_error_in_pattern_should_return_NULL) {
    const char string[] = "abc123";
    char     **split_string = regex_split("[ab", string, 0);

    cr_expect(split_string == NULL, "Expected NULL");
}

Test(aoc_regex, test_regex_split_single) {
    const char string[] = "kalle1anka";
    char     **split_string = regex_split("[0-9]", string, 0);
    unsigned   count = 0;
    while (split_string[count]) {
        count++;
    }

    cr_expect(count == 2, "Expected length to be 2");
}

Test(aoc_regex, test_regex_split_single_fail) {
    const char string[] = "kalle1anka";
    char     **split_string = regex_split("[2-9]", string, 0);
    unsigned   count = 0;
    while (split_string[count]) {
        count++;
    }

    cr_expect(count == 1, "Expected length to be 1");
}

Test(aoc_regex, test_regex_split_complex) {
    const char string[] = "rnqfzoisbqxbdlkgfh[lwlybvcsiupwnsyiljz]kmbgyaptjcsvwcltrdx[ntrpwgkrfeljpye]jxjdlgtntpljxaojufe";
    const char pattern[] = "\\[\\w+\\]";

    char **split_string = regex_split(pattern, string, 0);

    unsigned count;
    for (count = 0; split_string[count] != NULL; count++) {
        ;
    }

    cr_expect(count == 3, "Expected count = 3, got %d", count);
    cr_expect(!strcmp(split_string[0], "rnqfzoisbqxbdlkgfh"));
    cr_expect(!strcmp(split_string[1], "kmbgyaptjcsvwcltrdx"));
    cr_expect(!strcmp(split_string[2], "jxjdlgtntpljxaojufe"));
    cr_expect(split_string[3] == NULL);
}
