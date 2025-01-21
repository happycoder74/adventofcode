#include "aoc_header.h"
#include "aoc_timer.h"
#include "glib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bag {
    char         color[100];
    char         line[255];
    unsigned int number[100];
    char         bags[100][100];
    size_t       count;
};

struct Input {
    struct Bag  bags[600];
    size_t      bag_count;
    GHashTable *bag_table;
};

int find_bag_func(const void *a, const void *b) {
    /* printf("'%s' -- '%s'\n", (char *)a, (char *)b); */
    if (!strcmp((char *)a, (char *)b))
        return TRUE;
    return FALSE;
}

char *find_parent(char *bag, GHashTable *bag_table, GHashTable *bag_set) {
    /* printf("Checking %s\n", bag); */
    GHashTableIter iter;
    gpointer       key;
    gpointer       content;

    g_hash_table_iter_init(&iter, bag_table);
    while (g_hash_table_iter_next(&iter, &key, &content)) {
        if (g_ptr_array_find_with_equal_func((GPtrArray *)content, bag, find_bag_func, NULL)) {
            g_hash_table_add(bag_set, find_parent((char *)key, bag_table, bag_set));
        }
    }
    return bag;
}

int solve_part_1(void *inp) {
    GHashTable   *table = g_hash_table_new(g_str_hash, g_str_equal);
    struct Input *input = (struct Input *)inp;
    find_parent("shiny gold", input->bag_table, table);

    int result = g_hash_table_size(table);
    g_hash_table_destroy(table);
    return result;
}

int solve_part_2(void *inp) {
    int count = 0;
    return count;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 7;

    struct Input *input = ((struct Input *)calloc(1, sizeof(struct Input)));
    input->bag_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

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
        char **line_split = g_strsplit(line, "contain", 0);
        char  *str = g_strstrip(line_split[0]);
        /* char  *start = strstr(str, " "); */
        char  *end = strstr(str, " bag");
        *end = '\0';
        char      *key = g_strdup(str);
        char     **contents = g_strsplit(line_split[1], ", ", 0);
        GPtrArray *bag_contents = g_ptr_array_new();
        for (char **bag = contents; *bag != NULL; bag++) {
            char *str = g_strstrip(*bag);
            char *start = strstr(str, " ");
            char *end = strstr(str, " bag");
            *end = '\0';
            char *tmp = g_strdup(start + 1);
            g_ptr_array_add(bag_contents, tmp);
        }
        /* printf("str = %s, key = %s\n", str, key); */
        g_hash_table_insert(input->bag_table, g_strdup(key), bag_contents);
        g_strfreev(contents);
        g_strfreev(line_split);
    }
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, input, 1);
    timer_func_new(2, solve_part_2, input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    g_hash_table_destroy(input->bag_table);
    free(input);
    aoc_timer_delete(timer);
    return 0;
}
