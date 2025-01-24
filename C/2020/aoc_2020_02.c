#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    unsigned int start;
    unsigned int end;
    char         letter;
    char         password[255];
};

struct Input {
    struct Record records[1000];
    size_t        count;
};

static unsigned short int is_valid_1(struct Record *record) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < strlen(record->password); i++) {
        if (record->password[i] == record->letter) {
            count++;
            if (count > record->end)
                return 0;
        }
    }

    if (count >= record->start) {
        return 1;
    }
    return 0;
}

static unsigned short int is_valid_2(struct Record *record) {
    return ((record->password[record->start - 1] == record->letter) !=
            (record->password[record->end - 1] == record->letter));
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    int           count = 0;
    for (unsigned int i = 0; i < input->count; i++) {
        count += is_valid_1(&input->records[i]);
    }
    return count;
}

int solve_part_2(void *inp) {
    struct Input *input = (struct Input *)inp;
    int           count = 0;
    for (unsigned int i = 0; i < input->count; i++) {
        count += is_valid_2(&input->records[i]);
    }
    return count;

    return 0;
}

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isalnum((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}
int main(int argc, char **argv) {
    FILE              *fp = NULL;
    char               line[255];
    char               filepath[255];
    unsigned short int test = 0;

    const unsigned int year = 2020;
    const unsigned int day = 2;

    struct Input input = {0};
    AocTimer_t  *timer = NULL;

    if ((argc > 1) && !strcmp(argv[1], "--test")) {
        test = 1;
    }

    snprintf(filepath, 254, "%s/%d/%02d/%sinput.txt", getenv("AOC_DATA_LOCATION"), year, day,
             test ? "test_" : "");

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    while (fgets(line, 254, fp) != NULL) {
        char *ptr = strchr(line, ':');
        sscanf(line, "%d-%d %c: ", &input.records[index].start, &input.records[index].end,
               &input.records[index].letter);
        char *trimmed = str_trim_trailing(ptr + 2);
	memmove(input.records[index].password, trimmed, (strlen(trimmed) + 1) * sizeof(char));
        index++;
    }
    input.count = index;
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
