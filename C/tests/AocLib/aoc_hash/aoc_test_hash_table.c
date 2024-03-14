#include "aoc_hash.h"
#include "aoc_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef bool(*TestFunc)(void);
typedef void(*TestSetup)(void);
typedef void(*TestTeardown)(void);

typedef struct TestCase {
    char test_name[100];
    TestFunc    test_func;
    TestSetup   setup_func;
    TestTeardown teardown_func;
} TestCase;
    
bool cr_expect(bool test) {
    if (!test) {
        printf("Test failed %s:%d\n", __FILE__, __LINE__);
        return false;
    } 
    return true;
}

bool cr_expect_str_eq(const char *str1, const char *str2) {
    return cr_expect(!strcmp(str1, str2));
}

bool cr_assert(bool test) {
    return cr_expect(test);
}

bool cr_expect_not(bool test) {
    return cr_expect(!test);
}

bool cr_expect_null(const void *test) {
    return cr_expect(test == NULL);
}

bool test_aoc_hash_table_extended(void) {
    AocHashTable *hash;
    const char   *original_key = NULL, *value = NULL;
    bool success = true;

    hash = aoc_hash_table_create_custom(0, NULL, free, free, AOC_STR);

    aoc_hash_table_insert(hash, strdup("a"), strdup("A"));
    aoc_hash_table_insert(hash, strdup("b"), strdup("B"));
    aoc_hash_table_insert(hash, strdup("c"), strdup("C"));
    aoc_hash_table_insert(hash, strdup("d"), strdup("D"));
    aoc_hash_table_insert(hash, strdup("e"), strdup("E"));
    aoc_hash_table_insert(hash, strdup("f"), strdup("F"));

    success = success && cr_expect(aoc_hash_table_lookup_extended(hash, "a", (void **)&original_key, (void **)&value));
    success = success && cr_expect_str_eq(original_key, "a");
    success = success && cr_expect_str_eq(value, "A");

    success = success && cr_expect(aoc_hash_table_lookup_extended(hash, "b", NULL, (void **)&value));
    success = success && cr_expect_str_eq(value, "B");

    success = success && cr_expect(aoc_hash_table_lookup_extended(hash, "c", (void **)&original_key, NULL));
    success = success && cr_expect_str_eq(original_key, "c");

    success = success && cr_expect(aoc_hash_table_lookup_extended(hash, "d", NULL, NULL));

    success = success && cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", (void **)&original_key, (void **)&value));
    success = success && cr_expect_null(original_key);
    success = success && cr_expect_null(value);

    success = success && cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", NULL, (void **)&value));
    success = success && cr_expect_null(value);

    success = success && cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", (void **)&original_key, NULL));
    success = success && cr_expect_null(original_key);

    success = success && cr_expect_not(aoc_hash_table_lookup_extended(hash, "not a key", NULL, NULL));

    aoc_hash_table_destroy(&hash);

    return success;
}

static void inc_state(void *user_data) {
    int *state = user_data;
    cr_expect(*state == 0);
    *state = 1;
}

bool test_new_similar(void) {
    AocHashTable *hash1;
    AocHashTable *hash2;
    int           state1;
    int           state2;
    bool success = true;

    hash1 = aoc_hash_table_create_custom(0, NULL, free, inc_state, AOC_STR);
    state1 = 0;
    aoc_hash_table_insert(hash1, strdup("test"), &state1);
    success = success && cr_expect(aoc_hash_table_lookup(hash1, "test") == &state1);

    hash2 = aoc_hash_table_new_similar(hash1);

    success = success && cr_expect(aoc_hash_table_lookup(hash1, "test") == &state1);
    success = success && cr_expect_null(aoc_hash_table_lookup(hash2, "test"));

    state2 = 0;
    aoc_hash_table_insert(hash2, strdup("test"), &state2);
    success = success && cr_expect(aoc_hash_table_lookup(hash2, "test") == &state2);
    aoc_hash_table_delete(hash2, "test");
    success = success && cr_expect(state2 == 1);

    success = success && cr_expect(state1 == 0);
    aoc_hash_table_delete(hash1, "test");
    success = success && cr_expect(state1 == 1);

    aoc_hash_table_destroy(&hash1);
    aoc_hash_table_destroy(&hash2);

    return success;
}

bool seen_key[6];

static void foreach_func(void *key, void *value, void *data) {
    seen_key[((char *)key)[0] - 'a'] = true;
}

bool test_foreach(void) {
    AocHashTable *hash = NULL;
    bool success = true;

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
        success = success && cr_expect(seen_key[i]);
        {}
    }

    aoc_hash_table_destroy(&hash);

    return success;
}

static bool remove_even_foreach(void *key, void *value, void *user_data) {
    const char *_key = (const char *)key;
    const char *_value = (const char *)value;
    int         i;
    char        val[20];

    cr_expect(_key != NULL);
    cr_expect(*_key != 0);
    cr_expect(_value != NULL);
    cr_expect(*_value != 0);

    i = atoi(_key);

    snprintf(val, 20, "%d value", i);
    cr_expect(strcmp(_value, val) == 0);

    return ((i % 2) == 0) ? true : false;
}

static void not_even_foreach(void *key, void *value, void *user_data) {
    const char *_key = (const char *)key;
    const char *_value = (const char *)value;
    int         i;
    char        val[20];

    cr_expect(_key != NULL);
    cr_expect(*_key != 0);
    cr_expect(_value != NULL);
    cr_expect(*_value != 0);

    i = atoi(_key);

    snprintf(val, 20, "%d value", i);
    cr_expect(strcmp(_value, val) == 0);

    cr_expect((i % 2) != 0);
    cr_expect(i != 3);
}

bool test_foreach_remove_even(void) {
    AocHashTable *hash;
    bool success = true;

    hash = aoc_hash_table_create(AOC_STR);

    success = success && cr_assert(hash != NULL);

    for (int i = 0; i < 20; i++) {
        char *key = strdup_printf("%d", i);
        success = success && cr_assert(atoi(key) == i);
        char *value = strdup_printf("%d value", i);
        success = success && cr_assert(atoi(value) == i);
        aoc_hash_table_insert(hash, key, value);
    }

    success = success && cr_expect(aoc_hash_table_count(hash) == 20);

    char key[20] = "";
    for (int i = 0; i < 20; i++) {
        snprintf(key, 20, "%d", i);
        success = success && cr_expect(atoi(key) == i);

        char *v = (char *)aoc_hash_table_lookup(hash, key);

        success = success && cr_expect(v != NULL);
        success = success && cr_expect(*v != 0);
        success = success && cr_expect(atoi(v) == i);
    }

    snprintf(key, 20, "%d", 3);
    aoc_hash_table_delete(hash, key);
    success = success && cr_expect(aoc_hash_table_count(hash) == 19);
    aoc_hash_table_foreach_remove(hash, remove_even_foreach, NULL);
    success = success && cr_expect(aoc_hash_table_count(hash) == 9);
    aoc_hash_table_foreach(hash, not_even_foreach, NULL);

    char *orig_val, *orig_key;
    char  val[20] = "";

    for (int i = 0; i < 20; i++) {
        snprintf(key, 20, "%d", i);
        success = success && cr_assert(atoi(key) == i);

        snprintf(val, 20, "%d value", i);
        success = success && cr_assert(atoi(val) == i);

        orig_key = orig_val = NULL;
        bool found =
            aoc_hash_table_lookup_extended(hash, key, (void *)&orig_key, (void *)&orig_val);
        if ((i % 2) == 0 || i == 3) {
            success = success && cr_expect(!found);
            continue;
        }

        success = success && cr_expect(found);

        success = success && cr_expect(orig_key != NULL);
        success = success && cr_expect(strcmp(key, orig_key) == 0);

        success = success && cr_expect(orig_val != NULL);
        success = success && cr_expect(strcmp(val, orig_val) == 0);
    }

    aoc_hash_table_destroy(&hash);
     
    return success;
}


int main(void) {
     TestCase tests[] = {
         {"test_aoc_hash_table_extended", test_aoc_hash_table_extended, NULL, NULL},
         {"test_new_similar", test_new_similar, NULL, NULL},
         {"test_foreach", test_foreach, NULL, NULL},
         {"test_foreach_remove_even", test_foreach_remove_even, NULL, NULL},
         {"", NULL, NULL, NULL}
     };

     unsigned testindex = 0;
     while (tests[testindex].test_func) {
         TestCase *test = &tests[testindex];
         printf("Running test %s...", test->test_name);
         if(test->setup_func) {
             test->setup_func();
         }
         printf("%s\n", test->test_func() ? "OK":"FAIL");
         if(test->teardown_func) {
             test->teardown_func();
         }
         testindex++;
     }
     printf("Completed!\n");
     return 0;
}

