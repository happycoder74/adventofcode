#include "aoc_array.h"
#include "aoc_sets.h"
#include "aoc_types.h"
#include <criterion/criterion.h>

AocSet     *set = NULL;
AocSet     *set1 = NULL;
AocSet     *set2 = NULL;
AocArrayPtr initial_data = NULL;
AocArrayPtr arr1 = NULL;
AocArrayPtr arr2 = NULL;
int32_t     init_array[] = {20};
int32_t     array1[] = {10, 20, 30, 40};
int32_t     array2[] = {30, 40, 50, 60, 70};

void aoc_sets_setup(void) {
    initial_data = aoc_array_new_from_data(AOC_INT32, init_array, 1);
    arr1 = aoc_array_new_from_data(AOC_INT32, array1, 4);
    arr2 = aoc_array_new_from_data(AOC_INT32, array2, 5);
    set = aoc_set_new_with_data(initial_data, AOC_INT32);
    set1 = aoc_set_new_with_data(arr1, AOC_INT32);
    set2 = aoc_set_new_with_data(arr2, AOC_INT32);
}

void aoc_sets_teardown(void) {
    aoc_array_free(initial_data, 0);
    aoc_array_free(arr1, 0);
    aoc_array_free(arr2, 0);
    aoc_set_free(set);
    aoc_set_free(set1);
    aoc_set_free(set2);
}

TestSuite(aoc_sets, .init = aoc_sets_setup, .fini = aoc_sets_teardown);

Test(aoc_sets, aoc_sets_new_set_not_null) {
    cr_expect_not_null(set, "Expected set to be not NULL");
}

Test(aoc_sets, aoc_sets_initial_value_is_20) {
    int32_t value = aoc_int32_array_index(aoc_set_get_values(set), 0);

    cr_expect(value == 20, "Expected 20, got %d", value);
}

Test(aoc_sets, test_value_length_is_one) {
    AocArrayPtr return_values = aoc_set_get_values(set);
    cr_expect(return_values->length == 1, "Expected 1, got %zu", return_values->length);
}

Test(aoc_sets, test_value_length_is_four) {
    AocArrayPtr return_values = aoc_set_get_values(set1);
    int32_t     expected = 4;
    cr_expect((int32_t)return_values->length == expected, "Expected %d, got %zu", expected,
              return_values->length);
}

Test(aoc_sets, test_no_duplicate_values) {
    int32_t value = init_array[0];
    aoc_set_add(set, &value);
    cr_assert(aoc_set_size(set) > 0);
    cr_expect(1 == aoc_set_size(set), "Set contains duplicates");
}
