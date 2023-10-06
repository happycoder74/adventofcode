#include "aoc_array.h"
#include <stdio.h>
#include <stdlib.h>
#include "aoc_test.h"

int test_int32_array_new(void) {
    AocArrayPtr array = aoc_int32_array_new();

    int result = (array == NULL);
    aoc_int32_array_free(array);

    return result;
}

int test_int32_array_append(void) {
    AocArrayPtr array = aoc_int32_array_new();
    aoc_int32_array_append(array, 5);

    int result = !(aoc_int_array_index(array, 0) == 5);
    aoc_int32_array_free(array);

    return !result;
}

int main(void) {

    TestCaseStructure *ts = init_test_structure(10);
    add_case(ts, "test_int32_array_new()", test_int32_array_new, NULL);
    add_case(ts, "test_int32_array_append()", test_int32_array_append, NULL);

    run_test_cases(ts);

    test_report(ts);

    tear_down(ts);

    return EXIT_SUCCESS;
}
