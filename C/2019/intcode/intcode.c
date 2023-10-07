#include "aoc_array.h"

int intcode(AocArrayPtr instructions) {
    int i = 0;
    int dest, op, op1, op2;
    while((op = aoc_int32_array_index(instructions, i)) != 99) {
        dest = aoc_int32_array_index(instructions, i + 3);
        op1 = aoc_int32_array_index(instructions, i + 1);
        op2 = aoc_int32_array_index(instructions, i + 2);
        switch(op) {
            case 1:
                aoc_int32_array_set_index(instructions, dest,
                    aoc_int32_array_index(instructions, op1) +
                    aoc_int32_array_index(instructions, op2));
                i += 4;
                break;
            case 2:
                aoc_int32_array_set_index(instructions, dest,
                    aoc_int32_array_index(instructions, op1) *
                    aoc_int32_array_index(instructions, op2));
                i += 4;
                break;
            default:
                return 0;
        }
    }
    return aoc_int32_array_index(instructions, 0);

}

