#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
    assert(argc == 2 && "Must provide one argument");

    char character;
    int level = 0;
    FILE *fp = fopen(argv[1], "r");
    int pos = 0;
    int found_position = 0;

    while ((character = fgetc(fp)) != EOF) {
        if (level >=0 && ! found_position)
            pos++;
        else if (!found_position)
            found_position = 1;
        if (character == '(')
            level += 1;
        else if (character == ')')
            level -= 1;

    }

    printf("Part 1: %d\n", level);
    printf("Part 2: %d\n", pos);


}
