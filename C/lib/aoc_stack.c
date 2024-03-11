#include "aoc_stack.h"
#include <stdlib.h>

struct _AocStack {
    ssize_t stack_pointer;
    size_t  size;
    void  **data;
};

AocStackPtr aoc_stack_new(void) {
    AocStackPtr stack = (AocStackPtr)malloc(sizeof(AocStack));
    stack->stack_pointer = -1;
    stack->data = NULL;
    stack->size = 0;
    return stack;
}

void aoc_stack_push(AocStackPtr stack, void *item) {
    if (stack->data == NULL) {
        stack->data = calloc(16, sizeof(void *));
    } else if (stack->stack_pointer == (ssize_t)(stack->size - 1)) {
        size_t new_size = stack->size << 1;
        void  *new_data = (AocStackPtr)realloc(stack->data, new_size * sizeof(void *));
        if (new_data) {
            stack->data = new_data;
            stack->size = new_size;
        } else {
            return;
        }
    }

    stack->stack_pointer += 1;
    stack->data[stack->stack_pointer] = item;
}

void *aoc_stack_pop(AocStackPtr stack) {
    if (stack->stack_pointer < 0) {
        return NULL;
    }

    void *data = stack->data[stack->stack_pointer];
    stack->stack_pointer -= 1;
    return data;
}

void aoc_stack_free(AocStackPtr stack) {
    free(stack->data);
    stack->stack_pointer = -1;
    stack->data = NULL;
}

void *aoc_stack_peek(AocStackPtr stack) {
    if (stack->stack_pointer < 0) {
        return NULL;
    }

    return stack->data[stack->stack_pointer];
}
