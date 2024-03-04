#include "aoc_alloc.h"
#include "aoc_stack.h"
#include <stdint.h>
#include <stdio.h>

AocStackPtr stack;

int main(void) {
    int value;
    int fail = 0;
    int success = 0;

    stack = aoc_stack_new();
    ssize_t sp = *((ssize_t *)stack);
    if (sp != -1) {
        printf("aoc_stack_new() stack pointer should be -1. Was %d\n", (int)sp);
        fail++;
    } else {
        printf("aoc_stack_new() (stack_pointer value) OK\n");
        success++;
    }

    value = 10;
    aoc_stack_push(stack, (void *)(uint64_t)value);
    int popped = (int)(uint64_t)aoc_stack_pop(stack);
    if (popped != value) {
        printf("aoc_stack_pop failed: expected %d, got %d\n", value, popped);
        fail++;
    } else {
        printf("aoc_stack_pop OK\n");
        success++;
    }

    /* Summary */
    printf("%d tests succeeded and %d tests failed\n", success, fail);

    aoc_stack_free(stack);
    aoc_free(stack);

    return aoc_mem_gc();
}
