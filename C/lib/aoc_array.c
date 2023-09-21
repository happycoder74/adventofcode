#include "aoc_array.h"

// general array functions
size_t aoc_array_length(AocArray *array){
    return array->len;
}

void *aoc_array_index(AocArray *arr, size_t index) {
    return g_array_index(arr, void *, index);
}

AocArray *aoc_array_new(size_t element_size) {
    return g_array_new(TRUE, TRUE, element_size);
}


void aoc_array_append(AocArray *array, void *value) {
    g_array_append_vals(array, value, 1);
}


void aoc_array_free(AocArrayPtr array) {
    g_array_unref(array);
}


// int arrays

/*
AocArray *aoc_int_array_new(void) {

    return aoc_array_new(sizeof(int));
}

int aoc_int_array_index(AocArray *arr, size_t index) {
    return g_array_index(arr, int, index);
}

void aoc_int_array_append(AocArray *arr, int value) {
    g_array_append_vals(arr, &value, 1);
}
*/
