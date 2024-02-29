#include "aoc_hash.h"
#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    AocKey k;

    int32_t value = 0x12345678;

    k = int32_key(value);
    for (unsigned i = 0; i < sizeof value; i++) {
        printf("%4d %4x\n", k.key[i], k.key[i]);
    }
    printf("\n");
    int32_t keyval = *(int32_t *)k.key;
    printf("%4d %4x\n", keyval, keyval);

    char str[] = "abcdefgh";
    k = str_key(str);
    for (unsigned i = 0; i < strlen(str); i++) {
        printf("%d: %4d %4x\n", i, k.key[i], k.key[i]);
    }
    printf("\n");
    char *str_keyval = (char *)k.key;
    printf("%s\n", str_keyval);
}
