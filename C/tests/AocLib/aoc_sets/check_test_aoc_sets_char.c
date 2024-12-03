#include "aoc_array.h"
#include "aoc_sets.h"
#include "aoc_types.h"
#include <check.h>

static AocSet *set = NULL;
char           letters[] = {'g', 'a'};

static void aoc_sets_setup(void) {
    set = aoc_set_new(AOC_CHAR);
    aoc_set_add(set, &letters[0]);
}

static void aoc_sets_teardown(void) {
    aoc_set_free(set);
}

START_TEST(aoc_sets_new_set_not_null) {
    ck_assert_ptr_nonnull(set);
}
END_TEST

START_TEST(aoc_sets_initial_value_is_g) {
    char value = aoc_char_array_index(aoc_set_get_values(set), 0);

    ck_assert_msg(value == 'g', "Expected 'g', got %c", value);
}
END_TEST

/* START_TEST(test_value_length_is_one) { */
/*     AocArrayPtr return_values = aoc_set_get_values(set); */
/*     ck_assert_msg(return_values->length == 1, "Expected 1, got %llu", return_values->length); */
/* } */
/* END_TEST */

/* START_TEST(test_value_length_is_four) { */
/*     AocArrayPtr return_values = aoc_set_get_values(set1); */
/*     int32_t     expected = 4; */
/*     ck_assert_msg((int32_t)return_values->length == expected, "Expected %d, got %llu", expected,
 */
/*                   return_values->length); */
/* } */
/* END_TEST */

/* START_TEST(test_no_duplicate_values) { */
/*     int32_t value = init_array[0]; */
/*     int32_t value2 = 20; */
/*     aoc_set_add(set, &value); */
/*     aoc_set_add(set, &value2); */
/*     ck_assert(aoc_set_size(set) > 0); */
/*     ck_assert_msg(1 == aoc_set_size(set), "Set contains duplicates"); */
/* } */
/* END_TEST */

TCase *test_case_aoc_set_int32(void) {
    TCase *test_int32_sets = tcase_create("aoc_sets_int32");
    tcase_add_checked_fixture(test_int32_sets, aoc_sets_setup, aoc_sets_teardown);
    tcase_add_test(test_int32_sets, aoc_sets_new_set_not_null);
    tcase_add_test(test_int32_sets, aoc_sets_initial_value_is_g);
    /* tcase_add_test(test_int32_sets, test_value_length_is_one); */
    /* tcase_add_test(test_int32_sets, test_value_length_is_four); */
    /* tcase_add_test(test_int32_sets, test_no_duplicate_values); */

    return test_int32_sets;
}
