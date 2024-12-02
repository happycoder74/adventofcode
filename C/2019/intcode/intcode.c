#include "intcode.h"
#include "aoc_array.h"
#include <stdio.h>
#include <stdlib.h>

static IntCodeReturn_t *intcode_return_new(void) {
    IntCodeReturn_t *rv = (IntCodeReturn_t *)malloc(sizeof(IntCodeReturn_t));
    rv->return_buffer = aoc_int32_array_new();

    return rv;
}

IntCodeReturn_t *intcode(AocArrayPtr instructions, int *input) {
    int i = 0;
    int instruction;
    int op, op1, op2, op3, src;
    int mode;
    int value;
    int val1, val2;
    int mainloop = 1;

    IntCodeReturn_t *rv = intcode_return_new();

    while (mainloop) {
        instruction = aoc_int32_array_index(instructions, i);
        op = instruction % 100;
        mode = instruction / 100;
        int modes[] = {mode % 10, (mode / 10) % 10, mode / 100};

        switch (op) {
            case 1: // Opcode 01 - Addition
                op1 = aoc_int32_array_index(instructions, i + 1);
                op2 = aoc_int32_array_index(instructions, i + 2);
                op3 = aoc_int32_array_index(instructions, i + 3);
                val1 = modes[0] == 0 ? aoc_int32_array_index(instructions, op1) : op1;
                val2 = modes[1] == 0 ? aoc_int32_array_index(instructions, op2) : op2;
#ifndef NDEBUG
                printf("OP ADD: %d (%d) + %d (%d) => %d (%d)\n", val1, op1, val2, op2, op3,
                       val1 + val2);
#endif
                aoc_int32_array_set_index(instructions, op3, val1 + val2);
                i += 4;
                break;
            case 2: // Opcode 02 - Multiplication
                op1 = aoc_int32_array_index(instructions, i + 1);
                op2 = aoc_int32_array_index(instructions, i + 2);
                op3 = aoc_int32_array_index(instructions, i + 3);
                val1 = modes[0] == 0 ? aoc_int32_array_index(instructions, op1) : op1;
                val2 = modes[1] == 0 ? aoc_int32_array_index(instructions, op2) : op2;

#ifndef NDEBUG
                printf("OP MUL: %d * %d => %d\n", val1, val2, op3);
#endif
                aoc_int32_array_set_index(instructions, op3, val1 * val2);
                i += 4;
                break;
            case 3: // Opcode 03 - Input
                // TODO (Christian): Rewrite this to read from an input buffer.
                if (input == NULL) {
                    printf("Input value: ");
                    char  buf[20];
                    char *s = fgets(buf, 20, stdin);
                    if (!s) {
                        fprintf(stderr, "Error in input\n");
                        exit(EXIT_FAILURE);
                    }
                    value = atoi(buf);
                } else {
                    value = *input;
                }
                op1 = aoc_int32_array_index(instructions, i + 1);
#ifndef NDEBUG
                printf("You entered %d to %d\n", value, op1);
#endif
                aoc_int32_array_set_index(instructions, op1, value);
                i += 2;
                break;
            case 4: // Opcode 04 - Output
                // TODO (Christian): Rewrite this to write to an output buffer/array
                src = aoc_int32_array_index(instructions, i + 1);
                value = modes[0] == 0 ? aoc_int32_array_index(instructions, src) : src;
                aoc_int32_array_append(rv->return_buffer, value);
#ifndef NDEBUG
                printf("Value at %d is %d\n", src, value);
#endif
                if (value != 0) {
                    mainloop = 0;
                }
                i += 2;
                break;
            case 5: // Opcode 05 - Jump if true
                op1 = aoc_int32_array_index(instructions, i + 1);
                op2 = aoc_int32_array_index(instructions, i + 2);
                val1 = modes[0] == 0 ? aoc_int32_array_index(instructions, op1) : op1;
                val2 = modes[1] == 0 ? aoc_int32_array_index(instructions, op2) : op2;
                if (val1 != 0) {
                    i = val2;
                } else {
                    i += 3;
                }
#ifndef NDEBUG
                printf("OP JIT: %s (%d) Jump to %d\n", val1 ? "TRUE" : "FALSE", val1, i);
#endif
                break;
            case 6: // Opcode 06 - Jump if false
                op1 = aoc_int32_array_index(instructions, i + 1);
                op2 = aoc_int32_array_index(instructions, i + 2);
                val1 = modes[0] == 0 ? aoc_int32_array_index(instructions, op1) : op1;
                val2 = modes[1] == 0 ? aoc_int32_array_index(instructions, op2) : op2;
                if (val1 == 0) {
                    i = val2;
                } else {
                    i += 3;
                }
#ifndef NDEBUG
                printf("OP JIF: %s (%d) Jump to %d\n", !val1 ? "TRUE" : "FALSE", val1, i);
#endif
                break;
            case 7: // Opcode 07 - Less than
                op1 = aoc_int32_array_index(instructions, i + 1);
                op2 = aoc_int32_array_index(instructions, i + 2);
                op3 = aoc_int32_array_index(instructions, i + 3);

                val1 = modes[0] == 0 ? aoc_int32_array_index(instructions, op1) : op1;
                val2 = modes[1] == 0 ? aoc_int32_array_index(instructions, op2) : op2;

                if (val1 < val2) {
                    aoc_int32_array_set_index(instructions, op3, 1);
                } else {
                    aoc_int32_array_set_index(instructions, op3, 0);
                }
                i += 4;
#ifndef NDEBUG
                printf("OP  LT: %s (%d < %d ?)\n", val1 < val2 ? "TRUE" : "FALSE", val1, val2);
#endif
                break;
            case 8: // Opcode 08 - Equal
                op1 = aoc_int32_array_index(instructions, i + 1);
                op2 = aoc_int32_array_index(instructions, i + 2);
                op3 = aoc_int32_array_index(instructions, i + 3);

                val1 = modes[0] == 0 ? aoc_int32_array_index(instructions, op1) : op1;
                val2 = modes[1] == 0 ? aoc_int32_array_index(instructions, op2) : op2;

                if (val1 == val2) {
                    aoc_int32_array_set_index(instructions, op3, 1);
                } else {
                    aoc_int32_array_set_index(instructions, op3, 0);
                }
                i += 4;
#ifndef NDEBUG
                printf("OP  EQ: %s (%d == %d ?)\n", val1 < val2 ? "TRUE" : "FALSE", val1, val2);
#endif
                break;
            case 99:
                mainloop = 0;
                break;
            default:
                fprintf(stderr, "Should not be here. Invalid instruction encountered\n");
                fprintf(stderr, "OPCODE %02d\n", op);
                return 0;
        }
    }
    rv->return_value = aoc_int32_array_index(instructions, 0);
    return rv;
}

void intcode_return_free(IntCodeReturn_t *rv) {
    if (rv) {
        aoc_int32_array_free(rv->return_buffer);
        free(rv);
    }
}
