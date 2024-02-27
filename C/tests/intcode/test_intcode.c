#include "aoc_array.h"
#include "aoc_types.h"
#include "intcode.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocArrayPtr    program = NULL;
int32_t        ip[] = {0, 8, 10};
IntCodeInput_t input = {3, ip};

TestSuite(test_intcode);

void test_position_equal_to_setup(void) {
    int32_t instructions[] = {3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}

void test_position_less_than_setup(void) {
    int32_t instructions[] = {3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}

void test_immediate_equal_to_setup(void) {
    int32_t instructions[] = {3, 3, 1108, -1, 8, 3, 4, 3, 99};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}

void test_immediate_less_than_setup(void) {
    int32_t instructions[] = {3, 3, 1107, -1, 8, 3, 4, 3, 99};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}

void test_position_jump_setup(void) {
    int32_t instructions[] = {3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}

void test_immediate_jump_setup(void) {
    int32_t instructions[] = {3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}

void test_combinations_setup(void) {
    int32_t instructions[] = {3,   21, 1008, 21, 8,    20, 1005, 20,  22,  107,  8, 21, 20,   1006, 20, 31, 1106, 0,  36,   98, 0,  0,  1002, 21,
                              125, 20, 4,    20, 1105, 1,  46,   104, 999, 1105, 1, 46, 1101, 1000, 1,  20, 4,    20, 1105, 1,  46, 98, 99};
    program = aoc_array_new_from_data(AOC_ARRAY_INT32, instructions, sizeof(instructions) / sizeof(int32_t));
}
void test_int_code_teardown(void) {
    aoc_int32_array_free(program);
}

Test(test_intcode, test_position_equal_to, .init = test_position_equal_to_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {0, 1, 0};

    for (size_t i = 0; i < input.size; i++) {
        IntCodeReturn_t *rv = intcode(program, &input.input[i]);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d', got '%d'", expected[i], returned);
        intcode_return_free(rv);
    }
}

Test(test_intcode, test_position_less_than, .init = test_position_less_than_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {1, 0, 0};

    for (size_t i = 0; i < input.size; i++) {
        IntCodeReturn_t *rv = intcode(program, &input.input[i]);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d', got '%d'", expected[i], returned);
        intcode_return_free(rv);
    }
}

Test(test_intcode, test_immediate_equal_to, .init = test_immediate_equal_to_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {0, 1, 0};

    for (size_t i = 0; i < input.size; i++) {
        IntCodeReturn_t *rv = intcode(program, &input.input[i]);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d', got '%d'", expected[i], returned);
        intcode_return_free(rv);
    }
}

Test(test_intcode, test_immediate_less_than, .init = test_immediate_less_than_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {1, 0, 0};

    for (size_t i = 0; i < input.size; i++) {
        IntCodeReturn_t *rv = intcode(program, &input.input[i]);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d', got '%d'", expected[i], returned);
        intcode_return_free(rv);
    }
}

Test(test_intcode, test_position_jump, .init = test_position_jump_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {0, 1};

    for (size_t i = 0; i < 2; i++) {
        int32_t          input = (int32_t)i;
        IntCodeReturn_t *rv = intcode(program, &input);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d' from input '%d', got '%d'", expected[i], i, returned);
        intcode_return_free(rv);
    }
}

Test(test_intcode, test_immediate_jump, .init = test_position_jump_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {0, 1};

    for (size_t i = 0; i < 2; i++) {
        int32_t          input = (int32_t)i;
        IntCodeReturn_t *rv = intcode(program, &input);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d' from input '%d', got '%d'", expected[i], i, returned);
        intcode_return_free(rv);
    }
}

Test(test_intcode, test_immediate_jump_0, .init = test_immediate_jump_setup, .fini = test_int_code_teardown) {
    int32_t expected = 0;
    int32_t input = 0;

    IntCodeReturn_t *rv = intcode(program, &input);
    int32_t          returned = aoc_int32_array_last(rv->return_buffer);
    cr_expect(expected == returned, "Expected '%d' from input '%d', got '%d'", expected, input, returned);
    intcode_return_free(rv);
}

Test(test_intcode, test_immediate_jump_1, .init = test_immediate_jump_setup, .fini = test_int_code_teardown) {
    int32_t expected = 1;
    int32_t input = 1;

    IntCodeReturn_t *rv = intcode(program, &input);
    int32_t          returned = aoc_int32_array_last(rv->return_buffer);
    cr_expect(expected == returned, "Expected '%d' from input '%d', got '%d'", expected, input, returned);
    intcode_return_free(rv);
}

Test(test_intcode, test_immediate_jump_8, .init = test_immediate_jump_setup, .fini = test_int_code_teardown) {
    int32_t expected = 1;
    int32_t input = 8;

    IntCodeReturn_t *rv = intcode(program, &input);
    int32_t          returned = aoc_int32_array_last(rv->return_buffer);
    cr_expect(expected == returned, "Expected '%d' from input '%d', got '%d'", expected, input, returned);
    intcode_return_free(rv);
}

Test(test_intcode, test_combinations, .init = test_combinations_setup, .fini = test_int_code_teardown) {
    int32_t expected[] = {999, 1000, 1001};
    int32_t input[] = {7, 8, 9};

    for (size_t i = 0; i < 3; i++) {
        int32_t          inp = input[i];
        IntCodeReturn_t *rv = intcode(program, &inp);
        int32_t          returned = aoc_int32_array_last(rv->return_buffer);
        cr_expect(expected[i] == returned, "Expected '%d' from input '%d', got '%d'", expected[i], input, returned);
        intcode_return_free(rv);
    }
}
