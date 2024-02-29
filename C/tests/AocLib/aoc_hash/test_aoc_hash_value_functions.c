#include "aoc_hash.h"
#include <criterion/criterion.h>

Test(aoc_hash_value_functions, test_int32_value) {
    AocHashTablePtr ht = aoc_hash_table_create(10, aoc_hash, AOC_KEY_INT32);

    int32_t value = 10;
    aoc_hash_table_insert(ht, int32_key(10), &value);

    AocHashEntry *result = aoc_hash_table_lookup_new(ht, int32_key(10));

    cr_expect(value == int32_value(result), "Expected %d, got %d", value, int32_value(result));
}

Test(aoc_hash_value_functions, test_int64_value) {
    AocHashTablePtr ht = aoc_hash_table_create(10, aoc_hash, AOC_KEY_INT32);

    int64_t value = 10;
    aoc_hash_table_insert(ht, int32_key(10), &value);

    AocHashEntry *result = aoc_hash_table_lookup_new(ht, int32_key(10));

    cr_expect(value == int64_value(result), "Expected %lld, got %lld", value, int64_value(result));
}

Test(aoc_hash_value_functions, test_int64_large_value) {
    AocHashTablePtr ht = aoc_hash_table_create(10, aoc_hash, AOC_KEY_INT32);

    int64_t value = (int64_t)INT32_MAX * 2;
    aoc_hash_table_insert(ht, int32_key(10), &value);

    AocHashEntry *result = aoc_hash_table_lookup_new(ht, int32_key(10));

    cr_expect(value == int64_value(result), "Expected %d, got %d", value, int64_value(result));
}

Test(aoc_hash_value_functions, test_str_value) {
    AocHashTablePtr ht = aoc_hash_table_create(10, aoc_hash, AOC_KEY_INT32);

    char value[] = "This is a value";
    aoc_hash_table_insert(ht, int32_key(10), &value);

    AocHashEntry *result = aoc_hash_table_lookup_new(ht, int32_key(10));

    cr_expect_str_eq(value, str_value(result), "Expected %s, got %s", value, str_value(result));
}

Test(aoc_hash_value_functions, test_point_value) {
    AocHashTablePtr ht = aoc_hash_table_create(10, aoc_hash, AOC_KEY_INT32);

    Point value = {-1, 200};
    aoc_hash_table_insert(ht, int32_key(10), &value);

    AocHashEntry *result = aoc_hash_table_lookup_new(ht, int32_key(10));

    Point p = point_value(result);
    cr_expect(value.x == p.x, "Expected %d, got %d", value.x, p.x);
    cr_expect(value.y == p.y, "Expected %d, got %d", value.y, p.y);
}
