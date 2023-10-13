#include "aoc_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include <string.h>
#include "aoc_array.h"

AocArrayPtr array = NULL;

void aoc_array_setup(void) {
    array = aoc_ptr_array_new();
}

void aoc_array_teardown(void) {
    aoc_array_free(array, false);
}

TestSuite(aoc_array, .init=aoc_array_setup, .fini=aoc_array_teardown);

Test(aoc_array, test_ptr_array_new) {
    cr_expect(array != NULL, "Expected new array to not be NULL");
}

Test(aoc_array, test_ptr_array_new_length) {
    cr_expect(array->length == 0, "Expected new array length to be 0");
}

Test(aoc_array, test_ptr_array_append) {
    char str[] = "Test String";
    char *test_string = (char *)calloc(strlen(str) + 1, sizeof(char));
    test_string = strcpy(test_string, str);
    aoc_ptr_array_append(array, test_string);
    char **data = (char **)aoc_array_get_data(array);
    cr_expect(!strcmp((char *)data[0], "Test String"), "Expected value to be \"Test String\"");
    free(test_string);
}

Test(aoc_array, test_ptr_array_prepend_to_empty) {
    char str[] = "Test String";
    char *test_string = (char *)calloc(strlen(str) + 1, sizeof(char));
    test_string = strcpy(test_string, str);
    aoc_ptr_array_prepend(array, test_string);
    char **data = (char **)aoc_array_get_data(array);
    cr_expect(!strcmp((char *)data[0], str), "Expected value to be %s", str);
    free(test_string);
}

Test(aoc_array, test_ptr_array_index) {
    int *val1 = (int *)malloc(sizeof(int));
    int *val2 = (int *)malloc(sizeof(int));
    aoc_ptr_array_append(array, val1);
    aoc_ptr_array_append(array, val2);

    int *data = aoc_ptr_array_index(array, 1);
    cr_expect(val2 == data, "Expected value to be \"Two\"");

    free(val1);
    free(val2);
}

Test(aoc_array, test_ptr_array_remove_index) {
    int *val1 = (int *)malloc(sizeof(int));
    int *val2 = (int *)malloc(sizeof(int));
    double *val3 = (double *)malloc(sizeof(double));

    aoc_ptr_array_append(array, val1);
    aoc_ptr_array_append(array, val2);
    aoc_ptr_array_append(array, val3);

    AocArrayPtr res = NULL;
    res = aoc_array_remove_index(array, 1);

    cr_assert_not_null(res);
    cr_expect(array->length == 2, "Expected array length to be 2");
    cr_expect(aoc_ptr_array_index(array, 1) == (void *)val3);

    free(val1);
    free(val3);
}
//
//     add_case(ts, "test_ptr_array_index()", test_ptr_array_index, NULL);
//     add_case(ts, "test_ptr_array_remove_index()", test_ptr_array_remove_index, NULL);
//     add_case(ts, "test_ptr_array_append_to_null()", test_ptr_array_append_to_null, NULL);
//     add_case(ts, "test_ptr_array_append_to_wrong_type()", test_ptr_array_append_to_wrong_type, NULL);
//     add_case(ts, "test_ptr_array_insert_at_beginning()", test_ptr_array_insert_at_beginning, NULL);
//
//     run_test_cases(ts);
//
//     test_report(ts);
//
//     tear_down(ts);
//
//     return EXIT_SUCCESS;
