#include "aoc_stack.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>

static AocStackPtr stack = NULL;

static void test_aoc_stack_setup(void) {
    stack = aoc_stack_new();
}

static void test_aoc_stack_teardown(void) {
    aoc_stack_free(stack);
}

START_TEST(aoc_stack_initial_pointer) {
    ck_assert_ptr_nonnull(stack);
    ssize_t sp = *((ssize_t *)stack);
    ck_assert_msg(sp == -1, "Expected -1, got %d", (int)sp);
}
END_TEST

START_TEST(aoc_stack_push_one_value) {
    ck_assert_ptr_nonnull(stack);
    int32_t value = 10;

    aoc_stack_push(stack, &value);
    ssize_t  sp = *((ssize_t *)stack);
    int32_t *result = aoc_stack_peek(stack);
    ssize_t  sp2 = *((ssize_t *)stack);

    ck_assert_msg(value == *result, "expected %d, got %d", value, *result);
    ck_assert_msg(sp == 0, "expected %d, got %d", 0, (int)sp);
    ck_assert_msg(sp == sp2, "expected %d, got %d", (int)sp, (int)sp2);
}
END_TEST

START_TEST(test_aoc_stack_pop) {
    ck_assert_ptr_nonnull(stack);
    int32_t value = 10;

    aoc_stack_push(stack, &value);
    ssize_t sp = *((ssize_t *)stack);
    ck_assert_msg(sp == 0, "expected %d, got %d", 0, (int)sp);
    int32_t *result = aoc_stack_pop(stack);
    sp = *((ssize_t *)stack);
    ck_assert_msg(sp == -1, "expected %d, got %d", -1, (int)sp);

    ck_assert_msg(value == *result, "expected %d, got %d", value, *result);
}
END_TEST

TCase *test_case_aoc_stack(void) {
    TCase *test_aoc_stack = tcase_create("test_aoc_stack");

    tcase_add_checked_fixture(test_aoc_stack, test_aoc_stack_setup, test_aoc_stack_teardown);

    tcase_add_test(test_aoc_stack, aoc_stack_initial_pointer);
    tcase_add_test(test_aoc_stack, aoc_stack_push_one_value);
    tcase_add_test(test_aoc_stack, test_aoc_stack_pop);

    return test_aoc_stack;
}
