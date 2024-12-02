#ifndef __AOC_STACK_H__
#define __AOC_STACK_H__

typedef struct _AocStack AocStack;
typedef AocStack        *AocStackPtr;

AocStackPtr aoc_stack_new(void);

void  aoc_stack_push(AocStackPtr stack, void *item);
void *aoc_stack_pop(AocStackPtr stack);
void *aoc_stack_peek(AocStackPtr stack);
void  aoc_stack_free(AocStackPtr stack);

#endif // !__AOC_STACK_H__
