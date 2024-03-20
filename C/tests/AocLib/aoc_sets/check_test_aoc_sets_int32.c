#include "aoc_array.h"
#include "aoc_sets.h"
#include "aoc_types.h"
#include <check.h>

static AocSet     *set = NULL;
static AocSet     *set1 = NULL;
static AocSet     *set2 = NULL;
static AocArrayPtr initial_data = NULL;
static AocArrayPtr arr1 = NULL;
static AocArrayPtr arr2 = NULL;
static int32_t     init_array[] = {20};
static int32_t     array1[] = {10, 20, 30, 40};
static int32_t     array2[] = {30, 40, 50, 60, 70};

static void aoc_sets_setup(void) {
    initial_data = aoc_array_new_from_data(AOC_INT32, init_array, 1);
    arr1 = aoc_array_new_from_data(AOC_INT32, array1, 4);
    arr2 = aoc_array_new_from_data(AOC_INT32, array2, 5);
    set = aoc_set_new_with_data(initial_data, AOC_INT32);
    set1 = aoc_set_new_with_data(arr1, AOC_INT32);
    set2 = aoc_set_new_with_data(arr2, AOC_INT32);
}

static void aoc_sets_teardown(void) {
    aoc_array_free(initial_data, 0);
    aoc_array_free(arr1, 0);
    aoc_array_free(arr2, 0);
    aoc_set_free(set);
    aoc_set_free(set1);
    aoc_set_free(set2);
}

START_TEST(aoc_sets_new_set_not_null) {
    ck_assert_ptr_nonnull(set);
}
END_TEST

START_TEST(aoc_sets_initial_value_is_20) {
    int32_t value = aoc_int32_array_index(aoc_set_get_values(set), 0);

    ck_assert_msg(value == 20, "Expected 20, got %d", value);
}
END_TEST

START_TEST(test_value_length_is_one) {
    AocArrayPtr return_values = aoc_set_get_values(set);
    ck_assert_msg(return_values->length == 1, "Expected 1, got %llu", return_values->length);
}
END_TEST

START_TEST(test_value_length_is_four) {
    AocArrayPtr return_values = aoc_set_get_values(set1);
    int32_t     expected = 4;
    ck_assert_msg((int32_t)return_values->length == expected, "Expected %d, got %llu", expected,
                  return_values->length);
}
END_TEST

START_TEST(test_no_duplicate_values) {
    int32_t value = init_array[0];
    int32_t value2 = 20;
    aoc_set_add(set, &value);
    aoc_set_add(set, &value2);
    ck_assert(aoc_set_size(set) > 0);
    ck_assert_msg(1 == aoc_set_size(set), "Set contains duplicates");
}
END_TEST

TCase *test_case_aoc_set_int32(void) {
    TCase *test_int32_sets = tcase_create("aoc_sets_int32");
    tcase_add_checked_fixture(test_int32_sets, aoc_sets_setup, aoc_sets_teardown);
    tcase_add_test(test_int32_sets, aoc_sets_new_set_not_null);
    tcase_add_test(test_int32_sets, aoc_sets_initial_value_is_20);
    tcase_add_test(test_int32_sets, test_value_length_is_one);
    tcase_add_test(test_int32_sets, test_value_length_is_four);
    tcase_add_test(test_int32_sets, test_no_duplicate_values);

    return test_int32_sets;
}
