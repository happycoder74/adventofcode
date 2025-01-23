#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Directions_t;

typedef enum {
    KP_STD,
    KP_ALT,
    KP_COUNT
} KeyPadLayout;

typedef struct {
    KeyPadLayout  layout;
    unsigned int  rows;
    unsigned int  columns;
    Directions_t  directions[4];
    char        **keys;
    char         *code;
    unsigned int *pos;
} KeyPad_t;

#define NOT_FOUND (-1)
unsigned int command_get_index(char *commands, char command) {
    char needle[2];
    snprintf(needle, 2, "%c", command);
    const char *p = strstr(commands, needle);
    if (p) {
        return (unsigned int)(p - commands);
    }
    return NOT_FOUND;
}

KeyPad_t *keypad_init(KeyPadLayout layout) {
    KeyPad_t    *keypad = NULL;
    unsigned int i, j, index;
    char        *keys[] = {"123456789", "0010002340567890ABC000D00"};

    keypad = (KeyPad_t *)calloc(1, sizeof(KeyPad_t));
    keypad->layout = layout;
    keypad->code = NULL;
    keypad->pos = (unsigned int *)calloc(2, sizeof(unsigned int));
    keypad->rows = 0;
    keypad->columns = 0;
    if (layout == KP_STD) {
        keypad->rows = 3;
        keypad->columns = 3;
        keypad->pos[0] = 1;
        keypad->pos[1] = 1;
    } else {
        keypad->rows = 5;
        keypad->columns = 5;
        keypad->pos[0] = 0;
        keypad->pos[1] = 2;
    }

    keypad->keys = (char **)malloc(sizeof(char *) * keypad->rows);
    for (i = 0; i < keypad->rows; i++) {
        keypad->keys[i] = (char *)calloc(keypad->columns, sizeof(char));
        for (j = 0; j < keypad->columns; j++) {
            index = (j + i * keypad->columns);
            keypad->keys[i][j] = keys[layout][index];
        }
    }

    keypad->directions[0].x = 0;
    keypad->directions[0].y = -1;
    keypad->directions[1].x = 0;
    keypad->directions[1].y = 1;
    keypad->directions[2].x = -1;
    keypad->directions[2].y = 0;
    keypad->directions[3].x = 1;
    keypad->directions[3].y = 0;

    return keypad;
}

void keypad_destroy(KeyPad_t *keypad) {
    for (unsigned int i = 0; i < keypad->rows; i++) {
        free(keypad->keys[i]);
    }
    free(keypad->keys);
    free(keypad->code);
    free(keypad->pos);
    free(keypad);
}

char keypad_digit(KeyPad_t *keypad, unsigned int *pos) {
    char digit;
    if ((pos[0] <= keypad->columns - 1) && (pos[1] <= keypad->rows - 1)) {
        digit = keypad->keys[pos[1]][pos[0]];
        if (digit != '0') {
            return digit;
        }
    }
    return aoc_mem_gc();
}

unsigned int *keypad_key(KeyPad_t *keypad, char key) {
    Directions_t diff;
    unsigned int pos[2];
    unsigned int index;

    index = command_get_index("UDLR", key);

    diff = keypad->directions[index];
    pos[0] = keypad->pos[0] + diff.x;
    pos[1] = keypad->pos[1] + diff.y;

    if ((keypad_digit(keypad, pos))) {
        keypad->pos[0] = pos[0];
        keypad->pos[1] = pos[1];
        return keypad->pos;
    }
    return keypad->pos;
}

char keypad_keystring(KeyPad_t *keypad, char *line) {
    unsigned long i;

    for (i = 0; i < strlen(line); i++) {
        keypad->pos = keypad_key(keypad, line[i]);
    }
    return keypad_digit(keypad, keypad->pos);
}

char *keypad_get_code(KeyPad_t *keypad, AocArrayPtr data) {
    char        *line = NULL;
    unsigned int i;
    unsigned int data_length;

    data_length = aoc_array_length(data);
    keypad->code = (char *)calloc(data_length + 1, sizeof(char));
    for (i = 0; i < aoc_array_length(data); i++) {
        line = aoc_str_array_index(data, i);
        keypad->code[i] = keypad_keystring(keypad, line);
    }
    return keypad->code;
}

void *solve_part_1(AocData_t *data) {
    KeyPad_t *keypad = NULL;
    char     *return_string;

    keypad = keypad_init(KP_STD);
    return_string = strdup(keypad_get_code(keypad, aoc_data_get(data)));
    keypad_destroy(keypad);
    return return_string;
}

void *solve_part_2(AocData_t *data) {
    KeyPad_t *keypad = NULL;
    char     *return_string;

    keypad = keypad_init(KP_ALT);
    return_string = strdup(keypad_get_code(keypad, aoc_data_get(data)));
    keypad_destroy(keypad);
    return return_string;
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2016;
    const unsigned day = 2;

    AocTimer_t *timer = aoc_timer_new();

    aoc_timer_start(timer);
    AocData_t *data = get_data(argc, argv, year, day, NULL);
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func(0, solve_all, data, 0);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    aoc_data_free(data);

    return aoc_mem_gc();
}
