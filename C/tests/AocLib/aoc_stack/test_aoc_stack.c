#include "aoc_alloc.h"
#include "aoc_stack.h"
#include "criterion/assert.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>

AocStackPtr stack = NULL;

void test_aoc_stack_setup(void) {
    stack = aoc_stack_new();
}

void test_aoc_stack_teardown(void) {
    aoc_stack_free(stack);
}

TestSuite(aoc_stack, .init = test_aoc_stack_setup, .fini = test_aoc_stack_teardown);

Test(aoc_stack, aoc_stack_initial_pointer) {
    ssize_t sp = *((ssize_t *)stack);
    cr_expect(sp == -1, "Expected -1, got %d", (int)sp);
}

Test(aoc_stack, aoc_stack_push_one_value) {
    int32_t value = 10;

    aoc_stack_push(stack, &value);
    ssize_t  sp = *((ssize_t *)stack);
    int32_t *result = aoc_stack_peek(stack);
    ssize_t  sp2 = *((ssize_t *)stack);

    cr_expect(value == *result, "expected %d, got %d", value, *result);
    cr_expect(sp == 0, "expected %d, got %d", 0, (int)sp);
    cr_expect(sp == sp2, "expected %d, got %d", (int)sp, (int)sp2);
}

Test(aoc_stack, aoc_stack_pop) {
    int32_t value = 10;

    aoc_stack_push(stack, &value);
    ssize_t sp = *((ssize_t *)stack);
    cr_expect(sp == 0, "expected %d, got %d", 0, (int)sp);
    int32_t *result = aoc_stack_pop(stack);
    sp = *((ssize_t *)stack);
    cr_expect(sp == -1, "expected %d, got %d", -1, (int)sp);

    cr_expect(value == *result, "expected %d, got %d", value, *result);
}

/* int main(void) { */
/*     int value; */
/*     int fail = 0; */
/*     int success = 0; */

/*     value = 10; */
/*     aoc_stack_push(stack, (void *)(uint64_t)value); */
/*     int popped = (int)(uint64_t)aoc_stack_pop(stack); */
/*     if (popped != value) { */
/*         printf("aoc_stack_pop failed: expected %d, got %d\n", value, popped); */
/*         fail++; */
/*     } else { */
/*         printf("aoc_stack_pop OK\n"); */
/*         success++; */
/*     } */

/*     /1* Summary *1/ */
/*     printf("%d tests succeeded and %d tests failed\n", success, fail); */

/*     aoc_stack_free(stack); */
/*     aoc_free(stack); */

/*     return aoc_mem_gc(); */
/* } */
