#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"

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
    KeyPadLayout layout;
    int rows;
    int columns;
    Directions_t directions[4];
    char **keys;
    char *code;
    int *pos;
} KeyPad_t;

#define NOT_FOUND -1
int command_get_index(char *commands, char command) {
    char needle[2];
    sprintf(needle, "%c", command);
    const char *p = strstr(commands, needle);
    if (p) {
        return (int)(p - commands);
    }
    return NOT_FOUND;
}

KeyPad_t *keypad_init(KeyPadLayout layout) {
    KeyPad_t *keypad = NULL;
    int i, j, index;
    char *keys[] = {"123456789", "0010002340567890ABC000D00"};

    keypad = (KeyPad_t *)calloc(1, sizeof(KeyPad_t));
    keypad->layout = layout;
    keypad->code = NULL;
    keypad->pos = (int *)calloc(2, sizeof(int));
    if (layout == KP_STD) {
        keypad->rows = 3;
        keypad->columns = 3;
        keypad->pos[0] = 1;
        keypad->pos[1] = 1;
    } else if (layout == KP_ALT) {
        keypad->rows= 5;
        keypad->columns = 5;
        keypad->pos[0] = 0;
        keypad->pos[1] = 2;
    }

    keypad->keys = (char **)malloc(sizeof(char *) * keypad->rows);
    for (i = 0; i < keypad->rows; i++) {
        keypad->keys[i] = (char *)malloc(sizeof(char)*keypad->columns);
        for (j = 0; j < keypad->columns; j++) {
            index = (j + i*keypad->columns);
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
    for (int i = 0; i < keypad->rows; i++) {
        free(keypad->keys[i]);
    }
    free(keypad->keys);
    free(keypad->code);
    free(keypad->pos);
    free(keypad);
}

char keypad_digit(KeyPad_t *keypad, int *pos) {
    char digit;
    if ((pos[0] >= 0) && (pos[0] <= keypad->columns - 1) &&
        (pos[1] >= 0) && (pos[1] <= keypad->rows - 1)) {
        digit = keypad->keys[pos[1]][pos[0]];
        if (digit != '0') {
            return digit;
        }
    }
    return 0;
}

int *keypad_key(KeyPad_t *keypad, char key) {
    Directions_t diff;
    int pos[2];
    int index;

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

char *keypad_get_code(KeyPad_t *keypad, GArray *data) {
    gchar *line = NULL;
    guint i;
    guint data_length;

    data_length = data->len;
    keypad->code = (char *)calloc(data_length + 1, sizeof(char));
    for (i = 0; i < data->len; i++) {
        line = g_array_index(data, char *, i);
        keypad->code[i] = keypad_keystring(keypad, line);
    }
    return keypad->code;
}

GArray *clean_input(GArray *data) {
    return data;
}

gpointer solve_part_1(AocData_t *data) {
    KeyPad_t *keypad = NULL;
    char *return_string;

    keypad = keypad_init(KP_STD);
    return_string = g_strdup(keypad_get_code(keypad, data->data));
    keypad_destroy(keypad);
    return return_string;
}

gpointer solve_part_2(AocData_t *data) {
    KeyPad_t *keypad = NULL;
    char *return_string;

    keypad = keypad_init(KP_ALT);
    return_string = g_strdup(keypad_get_code(keypad, data->data));
    keypad_destroy(keypad);
    return return_string;
}

gpointer solve_all(AocData_t *data) {
    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2016, 2);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
