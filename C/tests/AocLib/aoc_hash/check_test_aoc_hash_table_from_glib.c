#include "aoc_hash.h"
#include "aoc_string.h"
#include <check.h>
#include <stdlib.h>

static AocHashTable *hash = NULL;

static void aoc_hash_table_setup(void) {
    hash = aoc_hash_table_create(AOC_STR);
}

static void aoc_hash_table_teardown(void) {
    aoc_hash_table_destroy(&hash);
}

START_TEST(test_aoc_hash_table_extended) {
    const char *original_key = NULL, *value = NULL;

    AocHashTable *hash;
    hash = aoc_hash_table_create_custom(0, NULL, free, free, AOC_STR);

    aoc_hash_table_insert(hash, strdup("a"), strdup("A"));
    aoc_hash_table_insert(hash, strdup("b"), strdup("B"));
    aoc_hash_table_insert(hash, strdup("c"), strdup("C"));
    aoc_hash_table_insert(hash, strdup("d"), strdup("D"));
    aoc_hash_table_insert(hash, strdup("e"), strdup("E"));
    aoc_hash_table_insert(hash, strdup("f"), strdup("F"));

    ck_assert(aoc_hash_table_lookup_extended(hash, "a", (void **)&original_key, (void **)&value));
    ck_assert_str_eq(original_key, "a");
    ck_assert_str_eq(value, "A");

    ck_assert(aoc_hash_table_lookup_extended(hash, "b", NULL, (void **)&value));
    ck_assert_str_eq(value, "B");

    ck_assert(aoc_hash_table_lookup_extended(hash, "c", (void **)&original_key, NULL));
    ck_assert_str_eq(original_key, "c");

    ck_assert(aoc_hash_table_lookup_extended(hash, "d", NULL, NULL));

    ck_assert(!aoc_hash_table_lookup_extended(hash, "not a key", (void **)&original_key,
                                              (void **)&value));
    ck_assert_ptr_null(original_key);
    ck_assert_ptr_null(value);

    ck_assert(!aoc_hash_table_lookup_extended(hash, "not a key", NULL, (void **)&value));
    ck_assert_ptr_null(value);

    ck_assert(!aoc_hash_table_lookup_extended(hash, "not a key", (void **)&original_key, NULL));
    ck_assert_ptr_null(original_key);

    ck_assert(!aoc_hash_table_lookup_extended(hash, "not a key", NULL, NULL));

    aoc_hash_table_destroy(&hash);
}
END_TEST

static void inc_state(void *user_data) {
    int *state = user_data;
    ck_assert_msg(*state == 0, "expected 0, got %d", *state);
    *state = 1;
}

START_TEST(test_new_similar) {
    AocHashTable *hash1;
    AocHashTable *hash2;
    int           state1;
    int           state2;

    hash1 = aoc_hash_table_create_custom(0, NULL, free, inc_state, AOC_STR);
    state1 = 0;
    aoc_hash_table_insert(hash1, strdup("test"), &state1);
    ck_assert(aoc_hash_table_lookup(hash1, "test") == &state1);

    hash2 = aoc_hash_table_new_similar(hash1);

    ck_assert(aoc_hash_table_lookup(hash1, "test") == &state1);
    ck_assert_ptr_null(aoc_hash_table_lookup(hash2, "test"));

    state2 = 0;
    aoc_hash_table_insert(hash2, strdup("test"), &state2);
    ck_assert(aoc_hash_table_lookup(hash2, "test") == &state2);
    aoc_hash_table_delete(hash2, "test");
    ck_assert_int_eq(state2, 1);

    ck_assert_int_eq(state1, 0);
    aoc_hash_table_delete(hash1, "test");
    ck_assert_int_eq(state1, 1);

    aoc_hash_table_destroy(&hash1);
    aoc_hash_table_destroy(&hash2);
}
END_TEST

bool seen_key[6];

static void foreach_func(void *key, void *value, void *data) {
    seen_key[((char *)key)[0] - 'a'] = true;
}

START_TEST(test_foreach) {

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
        ck_assert(seen_key[i]);
        {}
    }
}

static bool remove_even_foreach(void *key, void *value, void *user_data) {
    const char *_key = (const char *)key;
    const char *_value = (const char *)value;
    int         i;
    char        val[20];

    ck_assert(_key != NULL);
    ck_assert(*_key != 0);
    ck_assert(_value != NULL);
    ck_assert(*_value != 0);

    i = atoi(_key);

    snprintf(val, 20, "%d value", i);
    ck_assert(strcmp(_value, val) == 0);

    return ((i % 2) == 0) ? true : false;
}

static void not_even_foreach(void *key, void *value, void *user_data) {
    const char *_key = (const char *)key;
    const char *_value = (const char *)value;
    int         i;
    char        val[20];

    ck_assert(_key != NULL);
    ck_assert(*_key != 0);
    ck_assert(_value != NULL);
    ck_assert(*_value != 0);

    i = atoi(_key);

    snprintf(val, 20, "%d value", i);
    ck_assert(strcmp(_value, val) == 0);

    ck_assert_msg((i % 2) != 0, "Expected odd value, got %d", i);
    ck_assert(i != 3);
}
END_TEST

START_TEST(test_foreach_remove_even) {

    ck_assert_ptr_nonnull(hash);

    for (int i = 0; i < 20; i++) {
        char *key = strdup_printf("%d", i);
        ck_assert(atoi(key) == i);
        char *value = strdup_printf("%d value", i);
        ck_assert(atoi(value) == i);
        aoc_hash_table_insert(hash, key, value);
    }

    ck_assert(aoc_hash_table_count(hash) == 20);

    char key[20] = "";
    for (int i = 0; i < 20; i++) {
        snprintf(key, 20, "%d", i);
        ck_assert_int_eq(atoi(key), i);

        char *v = (char *)aoc_hash_table_lookup(hash, key);

        ck_assert_ptr_nonnull(v);
        ck_assert_int_ne(*v, 0);
        ck_assert_int_eq(atoi(v), i);
    }

    snprintf(key, 20, "%d", 3);
    aoc_hash_table_delete(hash, key);
    ck_assert(aoc_hash_table_count(hash) == 19);
    aoc_hash_table_foreach_remove(hash, remove_even_foreach, NULL);
    ck_assert(aoc_hash_table_count(hash) == 9);
    aoc_hash_table_foreach(hash, not_even_foreach, NULL);

    char *orig_val, *orig_key;
    char  val[20] = "";

    for (int i = 0; i < 20; i++) {
        snprintf(key, 20, "%d", i);
        ck_assert_int_eq(atoi(key), i);

        snprintf(val, 20, "%d value", i);
        ck_assert_int_eq(atoi(val), i);

        orig_key = orig_val = NULL;
        bool found =
            aoc_hash_table_lookup_extended(hash, key, (void *)&orig_key, (void *)&orig_val);
        if ((i % 2) == 0 || i == 3) {
            ck_assert(!found);
            continue;
        }

        ck_assert(found);

        ck_assert_ptr_nonnull(orig_key);
        ck_assert_str_eq(key, orig_key);

        ck_assert_ptr_nonnull(orig_val);
        ck_assert_str_eq(val, orig_val);
    }
}
END_TEST

START_TEST(test_init_with_str_literal) {
    int value = 5;
    hash = aoc_hash_table_create(AOC_STR);
    ck_assert_ptr_nonnull(hash);
    aoc_hash_table_insert(hash, "KEY5", &value);

    int *return_ptr = (int *)aoc_hash_table_lookup(hash, "KEY5");
    ck_assert_ptr_nonnull(return_ptr);
    /* ck_assert(value != return_value); */
    aoc_hash_table_destroy(&hash);
}
END_TEST

TCase *test_case_aoc_hash_fundamental(void) {
    TCase *test_case_fundamental = tcase_create("aoc_hash_table_fundamental");
    tcase_add_test(test_case_fundamental, test_new_similar);
    tcase_add_test(test_case_fundamental, test_aoc_hash_table_extended);
    tcase_add_test(test_case_fundamental, test_init_with_str_literal);

    return test_case_fundamental;
}

TCase *test_case_aoc_hash_foreach(void) {
    TCase *test_case_foreach = tcase_create("aoc_hash_table_foreach");
    tcase_add_checked_fixture(test_case_foreach, aoc_hash_table_setup, aoc_hash_table_teardown);
    tcase_add_test(test_case_foreach, test_foreach);
    tcase_add_test(test_case_foreach, test_foreach_remove_even);

    return test_case_foreach;
}
