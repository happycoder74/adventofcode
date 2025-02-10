#include "aoc_hash_light.h"
#include "aoc_header.h"
#include "aoc_timer.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Operation {
    uint64_t address;
    uint64_t value;
};

struct Instruction {
    char             mask[37];
    struct Operation operations[30];
    size_t           count;
};

struct Input {
    struct Instruction instructions[1000];
    uint64_t           registers[66000];
    AocHashTable      *memory_table;
    size_t             count;
};

typedef struct Vector {
    size_t    size;
    size_t    capacity;
    uint64_t *values;
} Vector_t;

void get_memory_addresses(Vector_t *v, char *mask, uint64_t address) {
    size_t  old_size = 0;
    uint8_t k;
    v->size = 1;
    v->values[0] = 0;
    for (size_t i = 0; i < 36; i++) {
        switch (mask[i]) {
            case '0':
                k = (address >> (35 - i)) & 1UL;
                if (k == 1) {
                    for (size_t m = 0; m < v->size; m++) {
                        v->values[m] |= 1UL << (35 - i);
                    }
                }
                break;
            case '1':
                for (size_t m = 0; m < v->size; m++) {
                    v->values[m] |= 1UL << (35 - i);
                }
                break;
            case 'X':
                old_size = v->size;
                for (size_t m = 0; m < old_size; m++) {
                    v->values[v->size++] = v->values[m] | (1UL << (35 - i));
                }
                break;
            default:
                fprintf(stderr, "Should not end up here!\n");
                exit(1);
                break;
        }
    }
}

void set_memory(struct Input *input, struct Vector *v, char *mask, uint64_t address,
                uint64_t value) {
    AocHashTable *memory_table = input->memory_table;

    get_memory_addresses(v, mask, address);
    for (size_t address_index = 0; address_index < v->size; address_index++) {
        uint64_t address = v->values[address_index];
        aoc_hash_table_replace(memory_table, (void *)(uint64_t)address, (void *)(uint64_t)value);
    }
}

uint64_t solve_part_1(void *inp) {
    struct Input     *input = (struct Input *)inp;
    struct Operation *op = NULL;
    uint64_t          result = 0;
    size_t            max_address = 0;

    for (size_t i = 0; i < input->count; i++) {
        char *mask = input->instructions[i].mask;
        for (size_t j = 0; j < input->instructions[i].count; j++) {
            op = input->instructions[i].operations + j;
            max_address = op->address > max_address ? op->address : max_address;
            uint64_t value = op->value;
            for (size_t m = 0; m < 36; m++) {
                uint8_t pos = 35 - m;
                switch (mask[pos]) {
                    case '0':
                        value = value & ~((uint64_t)1 << m);
                        break;
                    case '1':
                        value = value | ((uint64_t)1 << m);
                        break;
                    default:
                        break;
                }
            }
            input->registers[op->address] = value;
        }
    }
    for (size_t reg = 0; reg <= max_address; reg++) {
        result += input->registers[reg];
    }
    return result;
}

static void sum_values(void *key, void *value, void *data) {
    uint64_t  a = (uint64_t)(value);
    uint64_t *d = (uint64_t *)data;

    *d += a;

    return;
}

uint64_t solve_part_2(void *inp) {
    struct Input     *input = (struct Input *)inp;
    struct Operation *op = NULL;
    uint64_t          sum = 0;
    // clang-format off
    Vector_t vec = {
        .size = 0,
        .capacity = 1024,
        .values = calloc(1024, sizeof(uint64_t))
    };
    // clang-format on
    input->memory_table = aoc_hash_table_create(AOC_PTR);

    for (size_t i = 0; i < input->count; i++) {
        char *mask = input->instructions[i].mask;
        for (size_t j = 0; j < input->instructions[i].count; j++) {
            op = input->instructions[i].operations + j;
            set_memory(input, &vec, mask, op->address, op->value);
        }
    }
    aoc_hash_table_foreach(input->memory_table, sum_values, &sum);
    aoc_hash_table_destroy(&input->memory_table);
    free(vec.values);
    return sum;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 14;

    struct Input input = {0};

    AocTimer_t *timer = NULL;

    if ((argc > 1)) {
        if (!strcmp(argv[1], "--test")) {
            snprintf(filename, 40, "test_input.txt");
        } else {
            snprintf(filename, 40, "%s", argv[1]);
        }
    } else {
        snprintf(filename, 40, "input.txt");
    }

    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    struct Instruction *instruction = NULL;
    struct Operation   *op = NULL;
    while (fgets(line, 254, fp) != NULL) {
        if (!strncmp(line, "mask", 4)) {
            instruction = input.instructions + input.count;
            /* memmove(instruction->mask, line + 7, 36 * sizeof(char)); */
            sscanf(line, "mask = %s", instruction->mask);
            input.count++;
        } else if (!strncmp(line, "mem", 3)) {
            instruction = input.instructions + input.count - 1;
            op = instruction->operations + instruction->count;
            sscanf(line, "mem[%zu] = %zu", &op->address, &op->value);
            instruction->count += 1;
        }
    }

    fclose(fp);

    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_uint64(1, solve_part_1, &input, 1, NULL);
    timer_func_uint64(2, solve_part_2, &input, 1, NULL);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
