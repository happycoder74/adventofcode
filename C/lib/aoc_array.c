#include <glib.h>
#include "aoc_types.h"
#include "aoc_array.h"

void aoc_array_sort(AocArrayPtr array, int (*compare_function)(const void *, const void *)) {
    size_t element_size = g_array_get_element_size(array);

    qsort(array->data, aoc_array_length(array), element_size, compare_function);
}
