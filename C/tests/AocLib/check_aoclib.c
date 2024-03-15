#include <check.h>

#include "aoc_array/check_array.h"
#include "aoc_hash/check_hash.h"


int main(void) {
    SRunner *runner;

    runner = srunner_create(test_aoc_int32_array());
    srunner_add_suite(runner, test_aoc_ptr_array());
    srunner_add_suite(runner, test_aoc_hash_table());

    srunner_run_all(runner, CK_ENV);

    srunner_free(runner);

    return 0;
}

