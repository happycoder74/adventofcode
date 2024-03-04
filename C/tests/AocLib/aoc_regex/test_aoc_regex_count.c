#include "aoc_regex.h"
#include <criterion/criterion.h>

Test(aoc_regex, test_regex_count_three_matches) {
    const char string[] = "abacad";
    const char pattern[] = "(a)";

    regex_t re;
    regcomp(&re, pattern, 0);
    unsigned count = regex_match_count(&re, string);

    cr_expect(count == 3, "Expected 3, got %d", count);
}
