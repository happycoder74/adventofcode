#include "aoc_hash.h"
#include "aoc_string.h"
#include <criterion/criterion.h>
#include <stdlib.h>

Test(aoc_hash_table_from_glib, test_aoc_hash_table_extended) {
    AocHashTable *hash;
    const char   *original_key = NULL, *value = NULL;

    hash = aoc_hash_table_create_custom(0, NULL, free, free, AOC_STR);

    aoc_hash_table_insert(hash, strdup("a"), strdup("A"));
    aoc_hash_table_insert(hash, strdup("b"), strdup("B"));
    aoc_hash_table_insert(hash, strdup("c"), strdup("C"));
    aoc_hash_table_insert(hash, strdup("d"), strdup("D"));
    aoc_hash_table_insert(hash, strdup("e"), strdup("E"));
    aoc_hash_table_insert(hash, strdup("f"), strdup("F"));

    cr_expect(aoc_hash_table_lookup_extended(hash, "a", (void **)&original_key, (void **)&value));
    cr_expect_str_eq(original_key, "a");
    cr_expect_str_eq(value, "A");

    cr_expect(aoc_hash_table_lookup_extended(hash, "b", NULL, (void **)&value));
    cr_expect_str_eq(value, "B");

    cr_expect(aoc_hash_table_lookup_extended(hash, "c", (void **)&original_key, NULL));
    cr_expect_str_eq(original_key, "c");

    cr_expect(aoc_hash_table_lookup_extended(hash, "d", NULL, NULL));

    cr_expect_not(
        aoc_hash_table_lookup_extended(hash, "not a key", (void **)&original_key, (void **)&value));
    cr_expect_null(original_key);
    cr_expect_null(value);

    cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", NULL, (void **)&value));
    cr_expect_null(value);

    cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", (void **)&original_key, NULL));
    cr_expect_null(original_key);

    cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", NULL, NULL));

    aoc_hash_table_destroy(&hash);
}

static void inc_state(void *user_data) {
    int *state = user_data;
    cr_expect_eq(*state, 0, "expected 0, got %d", *state);
    *state = 1;
}

Test(aoc_hash_table_from_glib, test_new_similar) {
    AocHashTable *hash1;
    AocHashTable *hash2;
    int           state1;
    int           state2;

    hash1 = aoc_hash_table_create_custom(0, NULL, free, inc_state, AOC_STR);
    state1 = 0;
    aoc_hash_table_insert(hash1, strdup("test"), &state1);
    cr_expect(aoc_hash_table_lookup(hash1, "test") == &state1);

    hash2 = aoc_hash_table_new_similar(hash1);

    cr_expect(aoc_hash_table_lookup(hash1, "test") == &state1);
    cr_expect_null(aoc_hash_table_lookup(hash2, "test"));

    state2 = 0;
    aoc_hash_table_insert(hash2, strdup("test"), &state2);
    cr_expect(aoc_hash_table_lookup(hash2, "test") == &state2);
    aoc_hash_table_delete(hash2, "test");
    cr_expect_eq(state2, 1);

    cr_expect_eq(state1, 0);
    aoc_hash_table_delete(hash1, "test");
    cr_expect_eq(state1, 1);

    aoc_hash_table_destroy(&hash1);
    aoc_hash_table_destroy(&hash2);
}

bool seen_key[6];

static void foreach_func(void *key, void *value, void *data) {
    seen_key[((char *)key)[0] - 'a'] = true;
}

Test(aoc_hash_table_from_glib, test_foreach) {
    AocHashTable *hash = NULL;

    hash = aoc_hash_table_create(AOC_STR);

    aoc_hash_table_insert(hash, "a", "A");
    aoc_hash_table_insert(hash, "b", "B");
    aoc_hash_table_insert(hash, "c", "C");
    aoc_hash_table_insert(hash, "d", "D");
    aoc_hash_table_insert(hash, "e", "E");
    aoc_hash_table_insert(hash, "f", "F");

    for (unsigned i = 0; i < 6; i++) {
        seen_key[i] = false;
    }

    aoc_hash_table_foreach(hash, foreach_func, NULL);

    for (unsigned i = 0; i < 6; i++) {
        cr_expect(seen_key[i]);
        {}
    }

    aoc_hash_table_destroy(&hash);
}

static bool remove_even_foreach(void *key, void *value, void *user_data) {
    const char *_key = (const char *)key;
    const char *_value = (const char *)value;
    int         i;
    char        val[20];

    cr_assert(_key != NULL);
    cr_assert(*_key != 0);
    cr_assert(_value != NULL);
    cr_assert(*_value != 0);

    i = atoi(_key);

    sprintf(val, "%d value", i);
    cr_assert(strcmp(_value, val) == 0);

    return ((i % 2) == 0) ? true : false;
}

static void not_even_foreach(void *key, void *value, void *user_data) {
    const char *_key = (const char *)key;
    const char *_value = (const char *)value;
    int         i;
    char        val[20];

    cr_assert(_key != NULL);
    cr_assert(*_key != 0);
    cr_assert(_value != NULL);
    cr_assert(*_value != 0);

    i = atoi(_key);

    sprintf(val, "%d value", i);
    cr_assert(strcmp(_value, val) == 0);

    cr_expect((i % 2) != 0, "Expected odd value, got %d", i);
    cr_expect(i != 3);
}

Test(aoc_hash_table_from_glib, test_foreach_remove_even) {
    AocHashTable *hash;

    hash = aoc_hash_table_create(AOC_STR);

    cr_assert_not_null(hash);

    for (int i = 0; i < 20; i++) {
        char *key = strdup_printf("%d", i);
        cr_assert(atoi(key) == i);
        char *value = strdup_printf("%d value", i);
        cr_assert(atoi(value) == i);
        aoc_hash_table_insert(hash, key, value);
    }

    cr_expect(aoc_hash_table_count(hash) == 20);

    char key[20] = "";
    for (int i = 0; i < 20; i++) {
        snprintf(key, 20, "%d", i);
        cr_expect(atoi(key) == i);

        char *v = (char *)aoc_hash_table_lookup(hash, key);

        cr_expect(v != NULL);
        cr_expect(*v != 0);
        cr_expect(atoi(v) == i);
    }

    sprintf(key, "%d", 3);
    aoc_hash_table_delete(hash, key);
    cr_expect(aoc_hash_table_count(hash) == 19);
    aoc_hash_table_foreach_remove(hash, remove_even_foreach, NULL);
    cr_expect(aoc_hash_table_count(hash) == 9);
    aoc_hash_table_foreach(hash, not_even_foreach, NULL);

    char *orig_val, *orig_key;
    char  val[20] = "";

    for (int i = 0; i < 20; i++) {
        sprintf(key, "%d", i);
        cr_assert(atoi(key) == i);

        sprintf(val, "%d value", i);
        cr_assert(atoi(val) == i);

        orig_key = orig_val = NULL;
        bool found =
            aoc_hash_table_lookup_extended(hash, key, (void *)&orig_key, (void *)&orig_val);
        if ((i % 2) == 0 || i == 3) {
            cr_expect(!found);
            continue;
        }

        cr_expect(found);

        cr_expect(orig_key != NULL);
        cr_expect(strcmp(key, orig_key) == 0);

        cr_expect(orig_val != NULL);
        cr_expect(strcmp(val, orig_val) == 0);
    }

    aoc_hash_table_destroy(&hash);
}
