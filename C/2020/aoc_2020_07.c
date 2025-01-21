#include "aoc_hash.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POINTER_TO_INT(X) (int)(int64_t)(X)
#define INT_TO_POINTER(X) (void *)(int64_t)(X)

char *find_parent(char *bag, AocHashTable *bag_table, AocHashTable *bag_set) {
    AocHashIterator iter;

    void *key;
    void *content;

    aoc_hash_table_iter_init(&iter, bag_table);
    while (aoc_hash_table_iter_next(&iter, &key, &content)) {
        if (aoc_hash_table_contains((AocHashTable *)content, bag)) {
            aoc_hash_table_add(bag_set, find_parent((char *)key, bag_table, bag_set));
        }
    }
    return bag;
}

unsigned int count_bags(char *bag, AocHashTable *bag_table) {
    unsigned int    sum_bags = 0;
    AocHashTable   *contents = (AocHashTable *)aoc_hash_table_lookup(bag_table, bag);
    AocHashIterator iter;
    void           *key;
    void           *value;
    if (contents != NULL) {
        aoc_hash_table_iter_init(&iter, contents);
        while (aoc_hash_table_iter_next(&iter, &key, &value)) {
            sum_bags += (POINTER_TO_INT(value)) * count_bags((char *)key, bag_table);
        }
    }
    return sum_bags + 1;
}

int solve_part_1(void *inp) {
    AocHashTable *input = (AocHashTable *)inp;
    AocHashTable *table = aoc_hash_table_create(AOC_STR);
    find_parent("shiny gold", input, table);

    int result = aoc_hash_table_count(table);

    aoc_hash_table_destroy(&table);
    return result;
}

int solve_part_2(void *inp) {
    return count_bags("shiny gold", (AocHashTable *)inp) - 1;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 7;

    AocHashTable *bag_table = aoc_hash_table_create(AOC_STR);

    AocTimer_t *timer = NULL;

    if ((argc > 1)) {
        if (!strcmp(argv[1], "--test")) {
            sprintf(filename, "test_input.txt");
        } else {
            sprintf(filename, "%s", argv[1]);
        }
    } else {
        sprintf(filename, "input.txt");
    }

    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 254, fp) != NULL) {
        char **line_split = aoc_str_split(line, "contain", 0);
        char  *str = str_trim(line_split[0]);
        /* char  *start = strstr(str, " "); */
        char  *end = strstr(str, " bag");
        *end = '\0';
        char         *key = strdup(str);
        char        **contents = aoc_str_split(line_split[1], ", ", 0);
        AocHashTable *bag_contents = aoc_hash_table_create(AOC_STR);
        for (char **bag = contents; *bag != NULL; bag++) {
            if (str_startswith(*bag, "no"))
                continue;

            int   no_bags = atoi(*bag);
            char *str = str_trim(*bag);
            char *start = strstr(str, " ");
            char *end = strstr(str, " bag");
            *end = '\0';
            char *tmp = strdup(start + 1);
            aoc_hash_table_insert(bag_contents, tmp, INT_TO_POINTER(no_bags));
        }
        aoc_hash_table_insert(bag_table, strdup(key), bag_contents);
        aoc_str_freev(contents);
        aoc_str_freev(line_split);
    }
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, bag_table, 1);
    timer_func_new(2, solve_part_2, bag_table, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_hash_table_destroy(&bag_table);
    aoc_timer_delete(timer);
    return 0;
}
