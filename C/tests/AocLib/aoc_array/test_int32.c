#include "aoc_array.h"
#include <stdint.h>
#include "test_int32.h"

int test_int32_array_new(void) {
    AocArrayPtr array = aoc_int32_array_new();

    int result = ((array == NULL) &&
                  (array->type == AOC_ARRAY_INT32));

    aoc_int32_array_free(array);

    return result;
}

int test_int32_array_append(void) {
    AocArrayPtr array = aoc_int32_array_new();
    aoc_int32_array_append(array, 5);
    int32_t *data = (int *)aoc_array_get_data(array);

    int result = !(data[0] == 5);
    aoc_int32_array_free(array);

    return result;
}

int test_int32_array_index(void) {
    AocArrayPtr array = aoc_int32_array_new();
    aoc_int32_array_append(array, 15);
    aoc_int32_array_append(array, 0);
    aoc_int32_array_append(array, -5);

    int result = (
        (aoc_int32_array_index(array, 0) == 15) &&
        (aoc_int32_array_index(array, 2) == -5) &&
        (aoc_array_index(array, 5) == NULL )
    );

    aoc_int32_array_free(array);
    return !result;
}

int test_int32_array_remove_index(void) {
    AocArrayPtr array = aoc_int32_array_new();
    aoc_int32_array_append(array, 15);
    aoc_int32_array_append(array, 0);
    aoc_int32_array_append(array, -5);

    AocArrayPtr res = NULL;
    int result = ((res = aoc_array_remove_index(array, 0)) != NULL);

    result = result && (
        (aoc_int32_array_index(array, 0) == 0) &&
        (aoc_int32_array_index(array, 1) == -5) &&
        (aoc_array_length(array) == 2)
    );

    result = result && (
        ((res = aoc_array_remove_index(array, 3)) == NULL)
    );

    aoc_int32_array_free(array);
    return !result;
}

int test_int32_array_append_to_null(void) {
    int result = false;

    return !result;
}

int test_int32_array_insert(void) {
    int result = false;
    return !result;
}

int test_int32_array_insert_at_beginning(void) {
    int result = false;
    return !result;
}

int test_int32_array_insert_at_end(void) {
    int result = false;
    return !result;
}

int test_int32_array_insert_outside(void) {
    int result = false;
    return !result;
}
