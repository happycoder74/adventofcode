#include <stdio.h>
#include <stdlib.h>
#include "aoc_test.h"

#include "test_int32.h"


int main(void) {

    TestCaseStructure *ts = init_test_structure(1);
    add_case(ts, "test_int32_array_new()", test_int32_array_new, NULL);
    add_case(ts, "test_int32_array_append()", test_int32_array_append, NULL);
    add_case(ts, "test_int32_array_index()", test_int32_array_index, NULL);
    add_case(ts, "test_int32_array_remove_index()", test_int32_array_remove_index, NULL);
    add_case(ts, "test_int32_array_append_to_null()", test_int32_array_append_to_null, NULL);
    add_case(ts, "test_int32_array_append_to_wrong_type()", test_int32_array_append_to_wrong_type, NULL);
    add_case(ts, "test_int32_array_insert_at_beginning()", test_int32_array_insert_at_beginning, NULL);

    run_test_cases(ts);

    test_report(ts);

    tear_down(ts);

    return EXIT_SUCCESS;
}
