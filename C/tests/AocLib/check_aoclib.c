#include <check.h>

#include "aoc_array/check_array.h"
#include "aoc_hash/check_hash.h"
#include "aoc_sets/check_sets.h"

int main(void) {
    SRunner *runner;

    runner = srunner_create(test_aoc_array());
    srunner_add_suite(runner, test_aoc_hash_table());
    srunner_add_suite(runner, test_aoc_set());

    srunner_run_all(runner, CK_NORMAL);

    srunner_free(runner);

    return 0;
}
