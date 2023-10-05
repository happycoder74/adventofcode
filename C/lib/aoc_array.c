#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "aoc_types.h"
#include "aoc_array.h"




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
    char *string_repr[AOC_ARRAY_COUNT + 2] = {
        "AOC_ARRAY_CHAR",
        "AOC_ARRAY_UCHAR",
        "AOC_ARRAY_INT32",
        "AOC_ARRAY_UINT32",
        "AOC_ARRAY_INT64",
        "AOC_ARRAY_UINT64",
        "AOC_ARRAY_STR",
        "AOC_ARRAY_LINE",
        "AOC_ARRAY_POINT",
        "NOT DEFINED",
        "NOT DEFINED"

    };
    return string_repr[type];
}

AocArray *aoc_array_new(AocArrayType array_type, size_t size) {
    AocGenArray *array = (AocGenArray *)malloc(sizeof(AocGenArray));

    switch(array_type) {
        case AOC_ARRAY_INT32:
        case AOC_ARRAY_UINT32:
            array->element_size = sizeof(int32_t);
            break;
        case AOC_ARRAY_INT64:
        case AOC_ARRAY_UINT64:
            array->element_size = sizeof(int64_t);
            break;
        case AOC_ARRAY_STR:
            array->element_size = sizeof(char *);
            break;
        case AOC_ARRAY_CHAR:
        case AOC_ARRAY_UCHAR:
            array->element_size = sizeof(char);
            break;
        case AOC_ARRAY_POINT:
            array->element_size = sizeof(Point);
            break;
        default:
            return NULL;
            break;
    }
    array->data = (uint8_t *)malloc(array->element_size * size);
    array->type = array_type;
    array->length = 0;
    array->capacity = size;
    return (AocArray *)array;
}

void aoc_array_append(AocArray *array, void *value) {
    switch(array->type) {
        case AOC_ARRAY_INT32:
        case AOC_ARRAY_CHAR:
        case AOC_ARRAY_POINT:
        case AOC_ARRAY_STR:
            {
                AocGenArray *arr = (AocGenArray *)array;
                if (array->length == arr->capacity) {
                    #ifdef DEBUG
                    fprintf(stderr, "Array full, reallocating...\n");
                    #endif
                    arr->data = (uint8_t *)realloc(arr->data, arr->element_size * (arr->capacity << 1));
                    arr->capacity <<= 1;
                }
                memcpy(&arr->data[array->length * arr->element_size], value, arr->element_size);
            }
            break;
        default:
            fprintf(stderr, "Type %s is not implemented in append\n", aoc_type_string(array->type));
            return;
    }
    array->length += 1;
    return;
}

void *aoc_array_index(AocArray *array, size_t index) {
    AocGenArray *arr = (AocGenArray *)array;
    size_t real_index = index * arr->element_size;
    void *address = (void *)((int64_t)(&arr->data[real_index]));
    return (void *)address;
}

void aoc_array_free(AocArray *array, int free_segments) {
    AocGenArray *arr = (AocGenArray *)array;
    if(free_segments) {
        for (size_t index = 0; index < array->length; index++) {
            free(&arr->data[index * arr->element_size]);
        }
    }
    free(arr->data);
    free(array);
}

void aoc_array_print(AocArray *array) {
    char buffer[100];
    AocGenArray *arr = (AocGenArray *)array;
    printf("Length: %llu, Capacity: %llu\n", array->length, arr->capacity);
    for (size_t i = 0; i < array->length; i++) {
        switch (array->type) {
            case AOC_ARRAY_INT32:
                printf("%s%d%s", i == 0 ? "{" : "", aoc_int32_array_index(array, i), i == array->length - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_STR:
                printf("%s\"%s\"%s", i == 0 ? "{" : "", aoc_str_array_index(array, i), i == array->length - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_CHAR:
                printf("%s'%c'%s", i == 0 ? "{" : "", aoc_char_array_index(array, i), i == array->length - 1 ? "}\n":", ");
                break;
            case AOC_ARRAY_POINT:
                printf("%s%s%s", i == 0 ? "{" : "", point_to_string(aoc_point_array_index(array, i), buffer), i == array->length - 1 ? "}\n":", ");
                break;
            default:
                printf("Print of requested array type is not implemented\n");
                return;
        }
    }
}


