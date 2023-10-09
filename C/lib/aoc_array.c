#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "aoc_types.h"
#include "aoc_array.h"
#ifndef NDEBUG
#include "aoc_mem.h"
#endif

typedef struct {
    AocArrayType type;
    size_t length;
    size_t element_size;
    size_t capacity;
    uint8_t *data;
} AocGenArray;


void aoc_array_sort(AocArrayPtr array, int (*compare_function)(const void *, const void *)) {
    AocGenArray *arr = (AocGenArray *)array;

    qsort(arr->data, arr->length, arr->element_size, compare_function);
}

static char *point_to_string(Point p, char *buf) {
    sprintf(buf, "Point(%d, %d)", p.x, p.y);
    return buf;
}

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

    if (type > AOC_ARRAY_COUNT) {
        fprintf(stderr, "Type ID (%d) is not defined. Exiting...", type);
        exit(EXIT_FAILURE);
    }

    return string_repr[type];
}

AocArray *aoc_array_new(AocArrayType array_type, size_t size) {
    AocGenArray *array = (AocGenArray *)malloc(sizeof(AocGenArray));

    switch(array_type) {
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
            break;
        case AOC_ARRAY_LINE:
            array->element_size = sizeof(Line);
            break;
        default:
            fprintf(stderr, "Requested array type (%s) is not implemented in %s\n", aoc_type_string(array_type), "aoc_array_new()");
            return NULL;
            break;
    }
    array->data = (uint8_t *)malloc(array->element_size * size);
    array->type = array_type;
    array->length = 0;
    array->capacity = size;
    return (AocArray *)array;
}

void *aoc_int32_array_append(AocArrayPtr array, int32_t value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_INT32) {
        return NULL;
    }
    int32_t val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_int64_array_append(AocArrayPtr array, int64_t value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_INT64) {
        return NULL;
    }
    int64_t val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_uint32_array_append(AocArrayPtr array, uint32_t value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_UINT32) {
        return NULL;
    }
    uint32_t val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_uint64_array_append(AocArrayPtr array, uint64_t value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_UINT64) {
        return NULL;
    }
    uint64_t val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_char_array_append(AocArrayPtr array, char value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_CHAR) {
        return NULL;
    }
    char val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_uchar_array_append(AocArrayPtr array, unsigned char value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_UCHAR) {
        return NULL;
    }
    unsigned char val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_str_array_append(AocArrayPtr array, char *value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_STR) {
        return NULL;
    }
    char *val_ = strdup(value);
    return aoc_array_append(array, &val_);
}

void *aoc_point_array_append(AocArrayPtr array, Point value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_POINT) {
        return NULL;
    }
    Point val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_line_array_append(AocArrayPtr array, Line value) {
    if (array == NULL) {
        return NULL;
    }

    if(array->type != AOC_ARRAY_LINE) {
        return NULL;
    }
    Line val_ = value;
    return aoc_array_append(array, &val_);
}

void *aoc_array_append(AocArray *array, void *value) {
    if(array == NULL) {
        return NULL;
    }

    if(array->type >= AOC_ARRAY_COUNT) {
        fprintf(stderr, "Type %s is not implemented in aoc_array_append()\n", aoc_type_string(array->type));
        return NULL;
    }

    AocGenArray *arr = (AocGenArray *)array;
    if (array->length == arr->capacity) {
        arr->data = (uint8_t *)realloc(arr->data, arr->element_size * (arr->capacity << 1));
        arr->capacity <<= 1;
    }
    memcpy((arr->data + (array->length * arr->element_size)), value, arr->element_size);
    array->length += 1;
    return array;
}

void *aoc_array_index(AocArray *array, size_t index) {
    if (index >= aoc_array_length(array))
        return NULL;

    AocGenArray *arr = (AocGenArray *)array;
    size_t real_index = index * arr->element_size;
    void *address = (void *)((&arr->data[real_index]));
    return (void *)address;
}

void aoc_array_free(AocArray *array, int free_segments) {
    AocGenArray *arr = (AocGenArray *)array;
    if(free_segments) {
        for (size_t index = 0; index < aoc_array_length(array); index++) {
            free(&(arr->data[index * arr->element_size]));
        }
    }
    free(arr->data);
    free(array);
}

void aoc_array_print(AocArray *array) {
    char buffer[100];
    Line l;
    AocGenArray *arr = (AocGenArray *)array;
    printf("Type: %s (%d), Length: %zu, Capacity: %zu\n", aoc_type_string(array->type), array->type, aoc_array_length(array), arr->capacity);
    for (size_t i = 0; i < aoc_array_length(array); i++) {
        switch (array->type) {
            case AOC_ARRAY_INT32:
                printf("%s%d%s", i == 0 ? "{" : "", aoc_int32_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_UINT32:
                printf("%s%u%s", i == 0 ? "{" : "", aoc_uint32_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_INT64:
                printf("%s%lld%s", i == 0 ? "{" : "", aoc_int64_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_UINT64:
                printf("%s%llu%s", i == 0 ? "{" : "", aoc_uint64_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_STR:
                printf("%s\"%s\"%s", i == 0 ? "{" : "", aoc_str_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_CHAR:
                printf("%s'%c'%s", i == 0 ? "{" : "", aoc_char_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_UCHAR:
                printf("%s'%uc'%s", i == 0 ? "{" : "", aoc_uchar_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_POINT:
                printf("%s%s%s", i == 0 ? "{" : "", point_to_string(aoc_point_array_index(array, i), buffer), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_LINE:
                l = aoc_line_array_index(array,i);
                printf("%s%s -> %s%s", i == 0 ? "{" : "", point_to_string(l.p0, buffer), point_to_string(l.p1, buffer), i == aoc_array_length(array) - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_PTR:
                printf("%s%p%s", i == 0 ? "{" : "", (void *)aoc_ptr_array_index(array, i), i == aoc_array_length(array) - 1 ? "}\n":", ");
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

    if (arr->type == AOC_ARRAY_STR) {
        char *str = aoc_str_array_index(array, index);
        free(str);
    }

    if (index != aoc_array_length(arr) - 1) {
        memmove((arr->data + index * arr->element_size), (arr->data + (index + 1) * arr->element_size), arr->element_size * (aoc_array_length(arr) - index - 1));
    }

    arr->length -= 1;

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
    int32_t *data = (int32_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_int64_array_set_index(AocArrayPtr array, size_t index, int64_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_INT64)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    int64_t *data = (int64_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_uint32_array_set_index(AocArrayPtr array, size_t index, uint32_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_UINT32)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    uint32_t *data = (uint32_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_uint64_array_set_index(AocArrayPtr array, size_t index, uint64_t value) {
    if (!array)
        return NULL;
    if (array->type != AOC_ARRAY_UINT64)
        return NULL;

    AocGenArray *dst = (AocGenArray *)array;
    uint64_t *data = (uint64_t *)dst->data;
    data[index] = value;

    return array;
}


