#include "aoc_array.h"
#include "aoc_alloc.h"
#include "aoc_string.h"
#include "aoc_types.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    AocArrayType type;
    size_t       length;
    uint8_t      free_segments;
    size_t       element_size;
    size_t       capacity;
    uint8_t     *data;
} AocGenArray;

int aoc_array_contains(AocArrayPtr array, void *value) {
    for (size_t i = 0; i < array->length; i++) {
        switch (array->type) {
            case AOC_ARRAY_INT32:
                if (aoc_int32_array_index(array, i) == *(int32_t *)value)
                    return 1;
                break;
            case AOC_ARRAY_UINT32:
                if (aoc_uint32_array_index(array, i) == *(uint32_t *)value)
                    return 1;
                break;
            case AOC_ARRAY_INT64:
                if (aoc_int64_array_index(array, i) == *(int64_t *)value)
                    return 1;
                break;
            case AOC_ARRAY_UINT64:
                if (aoc_uint64_array_index(array, i) == *(uint64_t *)value)
                    return 1;
                break;
            case AOC_ARRAY_CHAR:
                if (aoc_char_array_index(array, i) == *(char *)value)
                    return 1;
                break;
            case AOC_ARRAY_UCHAR:
                if (aoc_uchar_array_index(array, i) == *(unsigned char *)value)
                    return 1;
                break;
            case AOC_ARRAY_PTR:
                if (aoc_ptr_array_index(array, i) == value)
                    return 1;
                break;
            default:
                break;
        }
    }
    return 0;
}

int aoc_array_find(AocArrayPtr array, void *value) {
    for (size_t i = 0; i < array->length; i++) {
        switch (array->type) {
            case AOC_ARRAY_INT32:
                if (aoc_int32_array_index(array, i) == *(int32_t *)value)
                    return (int)i;
                break;
            case AOC_ARRAY_UINT32:
                if (aoc_uint32_array_index(array, i) == *(uint32_t *)value)
                    return (int)i;
                break;
            case AOC_ARRAY_INT64:
                if (aoc_int64_array_index(array, i) == *(int64_t *)value)
                    return (int)i;
                break;
            case AOC_ARRAY_UINT64:
                if (aoc_uint64_array_index(array, i) == *(uint64_t *)value)
                    return (int)i;
                break;
            case AOC_ARRAY_CHAR:
                if (aoc_char_array_index(array, i) == *(char *)value)
                    return (int)i;
                break;
            case AOC_ARRAY_UCHAR:
                if (aoc_uchar_array_index(array, i) == *(unsigned char *)value)
                    return (int)i;
                break;
            case AOC_ARRAY_PTR:
                if (aoc_ptr_array_index(array, i) == value)
                    return (int)i;
                break;
            default:
                break;
        }
    }
    return -1;
}

void aoc_array_sort(AocArrayPtr array, int (*compare_function)(const void *, const void *)) {
    AocGenArray *arr = (AocGenArray *)array;

    qsort(arr->data, arr->length, arr->element_size, compare_function);
}

static char *point_to_string(Point p, char *buf) {
    sprintf(buf, "Point(%d, %d)", p.x, p.y);
    return buf;
}

size_t aoc_array_capacity(AocArrayPtr array) {
    return ((AocGenArray *)array)->capacity;
}

// clang-format off
static char* aoc_type_string(AocArrayType type) {
    char *string_repr[AOC_ARRAY_COUNT + 1] = {
        "AOC_ARRAY_CHAR",
        "AOC_ARRAY_UCHAR",
        "AOC_ARRAY_INT32",
        "AOC_ARRAY_UINT32",
        "AOC_ARRAY_INT64",
        "AOC_ARRAY_UINT64",
        "AOC_ARRAY_STR",
        "AOC_ARRAY_LINE",
        "AOC_ARRAY_POINT",
        "AOC_ARRAY_PTR",
        NULL
    };
    // clang-format on

    if (type > AOC_ARRAY_COUNT) {
        fprintf(stderr, "Type ID (%d) is not defined. Exiting...", type);
        exit(EXIT_FAILURE);
    }

    return string_repr[type];
}

AocArray *aoc_array_new(AocArrayType array_type, size_t size) {
    AocGenArray *array = (AocGenArray *)aoc_malloc(sizeof(AocGenArray));
    array->free_segments = 0;

    switch (array_type) {
        case AOC_ARRAY_INT32:
            array->element_size = sizeof(int32_t);
            break;
        case AOC_ARRAY_UINT32:
            array->element_size = sizeof(uint32_t);
            break;
        case AOC_ARRAY_INT64:
            array->element_size = sizeof(int64_t);
            break;
        case AOC_ARRAY_UINT64:
            array->element_size = sizeof(uint64_t);
            break;
        case AOC_ARRAY_STR:
            array->element_size = sizeof(char *);
            array->free_segments = 1;
            break;
        case AOC_ARRAY_CHAR:
            array->element_size = sizeof(char);
            break;
        case AOC_ARRAY_UCHAR:
            array->element_size = sizeof(unsigned char);
            break;
        case AOC_ARRAY_POINT:
            array->element_size = sizeof(Point);
            break;
        case AOC_ARRAY_PTR:
            array->element_size = sizeof(void *);
            array->free_segments = 1;
            break;
        case AOC_ARRAY_LINE:
            array->element_size = sizeof(Line);
            break;
        default:
            fprintf(stderr, "Requested array type (%s) is not implemented in %s\n", aoc_type_string(array_type), "aoc_array_new()");
            return NULL;
            break;
    }
    array->data = (uint8_t *)aoc_malloc(array->element_size * MAX(size, 1));
    array->type = array_type;
    array->length = 0;
    array->capacity = size;
    return (AocArray *)array;
}

void *aoc_str_array_append(AocArrayPtr array, char *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type != AOC_ARRAY_STR) {
        return NULL;
    }
    char *val_ = strdup(value);
    return aoc_array_append(array, &val_);
}

void *aoc_str_array_prepend(AocArrayPtr array, char *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type != AOC_ARRAY_STR) {
        return NULL;
    }
    char *val_ = strdup(value);
    return aoc_array_prepend(array, &val_);
}

static void *aoc_array_expand(AocArray *array) {
    AocGenArray *arr = (AocGenArray *)array;

    size_t new_capacity;
    if (arr->capacity == 0)
        new_capacity = 1;
    else
        new_capacity = arr->capacity << 1;

    arr->data = (uint8_t *)aoc_realloc(arr->data, arr->element_size * (new_capacity));
    arr->capacity = new_capacity;

    return array;
}

static void *aoc_array_shrink(AocArray *array) {
    AocGenArray *arr = (AocGenArray *)array;

    if (arr->length < (arr->capacity >> 1)) {
        arr->data = (uint8_t *)aoc_realloc(arr->data, arr->element_size * (MAX(arr->capacity, 1)));
        arr->capacity >>= 1;
    }

    return array;
}

void *aoc_array_append(AocArray *array, void *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type >= AOC_ARRAY_COUNT) {
        fprintf(stderr, "Type %s is not implemented in aoc_array_append()\n", aoc_type_string(array->type));
        return NULL;
    }

    AocGenArray *arr = (AocGenArray *)array;
    if (array->length == arr->capacity) {
        array = (AocArrayPtr)aoc_array_expand(array);
    }
    memcpy((arr->data + (array->length * arr->element_size)), value, arr->element_size);
    array->length += 1;
    return array;
}

void *aoc_array_prepend(AocArrayPtr array, void *value) {
    if (array == NULL)
        return NULL;

    if (array->type >= AOC_ARRAY_COUNT) {
        return NULL;
    }

    AocGenArray *arr = (AocGenArray *)array;
    if (array->length + 1 > arr->capacity) {
        array = (AocArrayPtr)aoc_array_expand(array);
    }

    memmove(arr->data + arr->element_size, arr->data, arr->element_size * arr->length);
    memcpy(arr->data, value, arr->element_size);

    array->length += 1;
    return array;
}

void *aoc_array_index(AocArray *array, size_t index) {
    if (index >= aoc_array_length(array))
        return NULL;

    AocGenArray *arr = (AocGenArray *)array;
    size_t       real_index = index * arr->element_size;
    void        *address = (void *)((&arr->data[real_index]));
    return (void *)address;
}

void aoc_array_free(AocArray *array, int free_segments) {
    if (array == NULL)
        return;

    AocGenArray *arr = (AocGenArray *)array;
    if (free_segments) {
        for (size_t index = 0; index < aoc_array_length(array); index++) {
            void *segment = (void *)*(char **)(arr->data + index * arr->element_size);
            aoc_free(segment);
        }
    }
    aoc_free(arr->data);
    aoc_free(array);
}

void aoc_array_print(AocArray *array) {
    char         buffer[100];
    Line         l;
    AocGenArray *arr = (AocGenArray *)array;
    printf("Type: %s (%d), Length: %zu, Capacity: %zu\n", aoc_type_string(array->type), array->type, aoc_array_length(array), arr->capacity);
    for (size_t i = 0; i < aoc_array_length(array); i++) {
        switch (array->type) {
            case AOC_ARRAY_INT32:
                printf("%s%d%s", i == 0 ? "{" : "", aoc_int32_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_UINT32:
                printf("%s%u%s", i == 0 ? "{" : "", aoc_uint32_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_INT64:
                printf("%s%" PRId64 "%s", i == 0 ? "{" : "", aoc_int64_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_UINT64:
                printf("%s%" PRIu64 "%s", i == 0 ? "{" : "", aoc_uint64_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_STR:
                printf("%s\"%s\"%s", i == 0 ? "{" : "", aoc_str_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_CHAR:
                printf("%s'%c'%s", i == 0 ? "{" : "", aoc_char_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_UCHAR:
                printf("%s'%uc'%s", i == 0 ? "{" : "", aoc_uchar_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_POINT:
                printf("%s%s%s", i == 0 ? "{" : "", point_to_string(aoc_point_array_index(array, i), buffer), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_LINE:
                l = aoc_line_array_index(array, i);
                printf("%s%s -> %s%s", i == 0 ? "{" : "", point_to_string(l.p0, buffer), point_to_string(l.p1, buffer), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_ARRAY_PTR:
                printf("%s%p%s", i == 0 ? "{" : "", (void *)aoc_ptr_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            default:
                printf("Print of requested array type is not implemented\n");
                return;
        }
    }
}

AocArrayPtr aoc_array_remove_index(AocArrayPtr array, size_t index) {
    AocGenArray *arr = (AocGenArray *)array;
    if (!arr) {
        return NULL;
    }

    if (index >= aoc_array_length(arr)) {
        return NULL;
    }

    if ((arr->type == AOC_ARRAY_STR) || (arr->type == AOC_ARRAY_PTR)) {
        void *ptr = aoc_ptr_array_index(array, index);
        aoc_free(ptr);
    }

    if (index != aoc_array_length(arr) - 1) {
        memmove((arr->data + index * arr->element_size), (arr->data + (index + 1) * arr->element_size), arr->element_size * (aoc_array_length(arr) - index - 1));
    }

    arr->length -= 1;

    array = aoc_array_shrink(array);

    return array;
}

void *aoc_array_get_data(AocArrayPtr array) {
    AocGenArray *arr = (AocGenArray *)array;

    void *data = (void *)arr->data;

    return data;
}

AocArrayPtr aoc_array_copy(AocArrayPtr array) {
    AocGenArray *source = (AocGenArray *)array;
    AocGenArray *destination = (AocGenArray *)aoc_array_new(source->type, source->capacity);
    memcpy(destination->data, source->data, source->capacity * source->element_size);
    destination->length = source->length;
    destination->element_size = source->element_size;

    return (AocArrayPtr)destination;
}

AocArrayPtr aoc_int32_array_set_index(AocArrayPtr array, size_t index, int32_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_INT32)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    int32_t     *data = (int32_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_int64_array_set_index(AocArrayPtr array, size_t index, int64_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_INT64)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    int64_t     *data = (int64_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_uint32_array_set_index(AocArrayPtr array, size_t index, uint32_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_UINT32)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    uint32_t    *data = (uint32_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_uint64_array_set_index(AocArrayPtr array, size_t index, uint64_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_UINT64)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    uint64_t    *data = (uint64_t *)dst->data;
    data[index] = value;

    return array;
}

size_t aoc_array_get_element_size(AocArrayPtr array) {
    return ((AocGenArray *)array)->element_size;
}
