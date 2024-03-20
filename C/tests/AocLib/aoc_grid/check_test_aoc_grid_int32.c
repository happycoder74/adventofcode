#include "aoc_grid.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static AocGrid       *grid = NULL;
static GridDimensions dimensions = {2, 3};

static int32_t  values_static[] = {1, 10, -10, 5};
static int32_t *values_dynamic = NULL;

static void aoc_grid_setup(void) {
    grid = aoc_grid_new(&dimensions);
    values_dynamic = (int32_t *)malloc(4 * sizeof(int32_t));
    values_dynamic[0] = 21;
    values_dynamic[1] = 201;
    values_dynamic[2] = -201;
    values_dynamic[3] = 25;
}

static void aoc_grid_teardown(void) {
    aoc_grid_free(grid);
    free(values_dynamic);
}

static void fill_grid(void) {
    aoc_grid_set(grid, 0, 0, &values_static[0]);
    aoc_grid_set(grid, 0, 1, &values_static[1]);
    aoc_grid_set(grid, 0, 2, &values_static[2]);
    aoc_grid_set(grid, 1, 2, &values_static[3]);
}

static void clear_grid(void) {
    aoc_grid_free(grid);
    grid = aoc_grid_new(&dimensions);
}

START_TEST(test_grid_create) {
    ck_assert_ptr_nonnull(grid);
}
END_TEST

START_TEST(test_aoc_grid_set) {
    bool result;
    result = aoc_grid_set(grid, 0, 0, &values_static[0]);
    ck_assert(!result);
    /* This test is currently not working.
     * Functionality for setting arbitrary indices is not implemented
     */
    /* result = aoc_grid_set(grid, -10, 11, &values_dynamic[0]); */
    /* cr_expect(!result, "Did not expect true"); */
}
END_TEST

START_TEST(test_aoc_grid_get) {
    bool result;
    result = aoc_grid_set(grid, 0, 0, &values_static[0]);
    ck_assert(!result);

    int32_t grid_value = *(int32_t *)aoc_grid_get(grid, 0, 0);
    ck_assert_msg(grid_value == values_static[0], "Expected %d, got %d", values_static[0],
                  grid_value);
}
END_TEST

START_TEST(test_aoc_grid_get_non_existing_inside) {
    fill_grid();
    int32_t *grid_value = (int32_t *)aoc_grid_get(grid, 1, 1);
    ck_assert_ptr_null(grid_value);
    clear_grid();
}
END_TEST

START_TEST(test_number_of_grid_rows) {
    fill_grid();
    int32_t rows = grid->rows;
    ck_assert_msg(rows == 2, "Expected 2, got %d", rows);
    clear_grid();
}
END_TEST

START_TEST(test_number_of_grid_columns) {
    fill_grid();
    int32_t columns = grid->columns;
    ck_assert_msg(columns == 3, "Expected 3, got %d", columns);
    clear_grid();
}
END_TEST

TCase *test_case_grid_int32(void) {
    TCase *aoc_grid_int32 = tcase_create("aoc_grid_int32");

    tcase_add_checked_fixture(aoc_grid_int32, aoc_grid_setup, aoc_grid_teardown);
    tcase_add_test(aoc_grid_int32, test_grid_create);
    tcase_add_test(aoc_grid_int32, test_aoc_grid_set);
    tcase_add_test(aoc_grid_int32, test_aoc_grid_get);
    tcase_add_test(aoc_grid_int32, test_aoc_grid_get_non_existing_inside);
    tcase_add_test(aoc_grid_int32, test_number_of_grid_rows);
    tcase_add_test(aoc_grid_int32, test_number_of_grid_columns);

    return aoc_grid_int32;
}
