#include "aoc_grid.h"
#include "criterion/assert.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocGrid       *grid = NULL;
GridDimensions dimensions = {2, 3};

int32_t  values_static[] = {1, 10, -10, 5};
int32_t *values_dynamic = NULL;

void aoc_grid_setup(void) {
    grid = aoc_grid_new(&dimensions);
    values_dynamic = (int32_t *)malloc(4 * sizeof(int32_t));
    values_dynamic[0] = 21;
    values_dynamic[1] = 201;
    values_dynamic[2] = -201;
    values_dynamic[3] = 25;
}

void aoc_grid_teardown(void) {
    aoc_grid_free(grid);
    free(values_dynamic);
}

TestSuite(aoc_grid, .init = aoc_grid_setup, .fini = aoc_grid_teardown);

Test(aoc_grid, test_grid_create) {
    cr_expect_not_null(grid, "Expected new grid to not be NULL");
}

Test(aoc_grid, test_aoc_grid_set) {
    bool result;
    result = aoc_grid_set(grid, 0, 0, &values_static[0]);
    cr_expect(!result, "Did not expect true");
    /* This test is currently not working.
     * Functionality for setting arbitrary indices is not implemented
     */
    /* result = aoc_grid_set(grid, -10, 11, &values_dynamic[0]); */
    /* cr_expect(!result, "Did not expect true"); */
}

Test(aoc_grid, test_aoc_grid_get) {
    bool result;
    result = aoc_grid_set(grid, 0, 0, &values_static[0]);
    cr_assert_not(result);

    int32_t grid_value = *(int32_t *)aoc_grid_get(grid, 0, 0);
    cr_expect(grid_value == values_static[0], "Expected %d, got %d", values_static[0], grid_value);
}

void fill_grid(void) {
    aoc_grid_set(grid, 0, 0, &values_static[0]);
    aoc_grid_set(grid, 0, 1, &values_static[1]);
    aoc_grid_set(grid, 0, 2, &values_static[2]);
    aoc_grid_set(grid, 1, 2, &values_static[3]);
}

void clear_grid(void) {
    aoc_grid_free(grid);
    grid = aoc_grid_new(&dimensions);
}

Test(aoc_grid, test_aoc_grid_get_nonexisting_inside, .init = fill_grid, .fini = clear_grid) {
    int32_t *grid_value = (int32_t *)aoc_grid_get(grid, 1, 1);
    cr_expect_null(grid_value, "Expected NULL, got %d", *grid_value);
}

Test(aoc_grid, test_aoc_grid_get_number_of_rows_filled, .init = fill_grid, .fini = clear_grid) {
    int32_t rows = grid->rows;
    cr_expect(rows == 2, "Expected 2, got %d", rows);
}

Test(aoc_grid, test_aoc_grid_get_number_of_columns_filled, .init = fill_grid, .fini = clear_grid) {
    int32_t columns = grid->columns;
    cr_expect(columns == 3, "Expected 3, got %d", columns);
}

/* Test(aoc_grid, test_grid_rehash, .init = aoc_grid_load_6) { */
/*     int32_t value = 1001; */
/*     aoc_grid_insert(grid, int32_key(100), &value); */
/*     int32_t expected = 17; */
/*     int32_t actual = (int32_t)aoc_grid_size(grid); */
/*     cr_expect_eq(expected, actual, "Expected size of %d, but got %d", expected, actual); */
/*     expected = values[4]; */
/*     actual = int32_value(aoc_grid_lookup_new(grid, int32_key(keys[4]))); */
/*     cr_expect_eq(expected, actual, "Expected value of key: %d to be %d but got %d", keys[4],
 * expected, actual); */
/* } */
