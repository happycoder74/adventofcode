#include "aoc_array.h"
#include "aoc_alloc.h"
#include "aoc_string.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <inttypes.h>
#include <math.h>
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
    void       **ptr_data;
} AocGenArray;

int aoc_array_contains(AocArrayPtr array, void *value) {
    for (size_t i = 0; i < array->length; i++) {
        switch (array->type) {
            case AOC_INT32:
                if (aoc_int32_array_index(array, i) == *(int32_t *)value) {
                    return 1;
                }
                break;
            case AOC_UINT32:
                if (aoc_uint32_array_index(array, i) == *(uint32_t *)value) {
                    return 1;
                }
                break;
            case AOC_INT64:
                if (aoc_int64_array_index(array, i) == *(int64_t *)value) {
                    return 1;
                }
                break;
            case AOC_UINT64:
                if (aoc_uint64_array_index(array, i) == *(uint64_t *)value) {
                    return 1;
                }
                break;
            case AOC_CHAR:
                if (aoc_char_array_index(array, i) == *(char *)value) {
                    return 1;
                }
                break;
            case AOC_UCHAR:
                if (aoc_uchar_array_index(array, i) == *(unsigned char *)value) {
                    return 1;
                }
                break;
            case AOC_PTR:
                if (aoc_ptr_array_index(array, i) == value) {
                    return 1;
                }
                break;
            case AOC_DOUBLE:
                if (aoc_double_array_index(array, i) == *(double *)value) {
                    return 1;
                }
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
            case AOC_INT32:
                if (aoc_int32_array_index(array, i) == *(int32_t *)value) {
                    return (int)i;
                }
                break;
            case AOC_UINT32:
                if (aoc_uint32_array_index(array, i) == *(uint32_t *)value) {
                    return (int)i;
                }
                break;
            case AOC_INT64:
                if (aoc_int64_array_index(array, i) == *(int64_t *)value) {
                    return (int)i;
                }
                break;
            case AOC_UINT64:
                if (aoc_uint64_array_index(array, i) == *(uint64_t *)value) {
                    return (int)i;
                }
                break;
            case AOC_CHAR:
                if (aoc_char_array_index(array, i) == *(char *)value) {
                    return (int)i;
                }
                break;
            case AOC_UCHAR:
                if (aoc_uchar_array_index(array, i) == *(unsigned char *)value) {
                    return (int)i;
                }
                break;
            case AOC_PTR:
                if (aoc_ptr_array_index(array, i) == value) {
                    return (int)i;
                }
                break;
            case AOC_DOUBLE:
                if (aoc_uint64_array_index(array, i) == *(uint64_t *)value) {
                    return (int)i;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}

int int32_compare(const void *a, const void *b) {
    int64_t v_a = *(int64_t *)a;
    int64_t v_b = *(int64_t *)b;

    if (v_a == v_b) {
        return 0;
    } else {
        return (int)((v_a - v_b) / (llabs(v_a - v_b)));
    }
}

int int64_compare(const void *a, const void *b) {
    int64_t v_a = *(int64_t *)a;
    int64_t v_b = *(int64_t *)b;

    if (v_a == v_b) {
        return 0;
    } else {
        return (int)((v_a - v_b) / (llabs(v_a - v_b)));
    }
}

int double_compare(const void *a, const void *b) {
    double v_a = *(double *)a;
    double v_b = *(double *)b;

    if (v_a == v_b) {
        return 0;
    } else {
        return (int)((v_a - v_b) / (fabs(v_a - v_b)));
    }
}

void aoc_array_sort(AocArrayPtr array, int (*compare_function)(const void *, const void *)) {
    AocGenArray *arr = (AocGenArray *)array;

    qsort(arr->data, arr->length, arr->element_size, compare_function);
}

size_t aoc_array_capacity(AocArrayPtr array) {
    return ((AocGenArray *)array)->capacity;
}

// clang-format off
static char* aoc_type_string(AocArrayType type) {
    char *string_repr[AOC_COUNT + 1] = {
        "AOC_CHAR",
        "AOC_UCHAR",
        "AOC_INT32",
        "AOC_UINT32",
        "AOC_INT64",
        "AOC_UINT64",
        "AOC_STR",
        "AOC_LINE",
        "AOC_POINT",
        "AOC_PTR",
        "AOC_DOUBLE",
        NULL
    };
    // clang-format on

    if (type > AOC_COUNT) {
        fprintf(stderr, "Type ID (%d) is not defined. Exiting...", type);
        exit(EXIT_FAILURE);
    }

    return string_repr[type];
}

AocArray *aoc_array_new(AocArrayType array_type, size_t size) {
    AocGenArray *array = (AocGenArray *)malloc(sizeof(AocGenArray));
    array->free_segments = 0;
    array->data = NULL;
    array->ptr_data = NULL;

    switch (array_type) {
        case AOC_INT32:
            array->element_size = sizeof(int32_t);
            break;
        case AOC_UINT32:
            array->element_size = sizeof(uint32_t);
            break;
        case AOC_INT64:
            array->element_size = sizeof(int64_t);
            break;
        case AOC_UINT64:
            array->element_size = sizeof(uint64_t);
            break;
        case AOC_STR:
            array->element_size = sizeof(char *);
            array->free_segments = 1;
            break;
        case AOC_CHAR:
            array->element_size = sizeof(char);
            break;
        case AOC_UCHAR:
            array->element_size = sizeof(unsigned char);
            break;
        case AOC_POINT:
            array->element_size = sizeof(Point);
            break;
        case AOC_PTR:
            array->element_size = sizeof(void *);
            array->free_segments = 1;
            array->ptr_data = (void **)calloc(MAX(size, 1), sizeof(void *));
            break;
        case AOC_LINE:
            array->element_size = sizeof(Line);
            break;
        case AOC_DOUBLE:
            array->element_size = sizeof(double);
            break;
        default:
            fprintf(stderr, "Requested array type (%s) is not implemented in %s\n",
                    aoc_type_string(array_type), "aoc_array_new()");
            return NULL;
            break;
    }
    if (array_type != AOC_PTR) {
        array->data = (uint8_t *)malloc(array->element_size * MAX(size, 1));
    }
    array->type = array_type;
    array->length = 0;
    array->capacity = MAX(size, 1);
    return (AocArray *)array;
}

void *aoc_str_array_append(AocArrayPtr array, char *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type != AOC_STR) {
        return NULL;
    }
    char *val_ = strdup(value);
    return aoc_array_append(array, &val_);
}

void *aoc_str_array_prepend(AocArrayPtr array, char *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type != AOC_STR) {
        return NULL;
    }
    char *val_ = strdup(value);
    return aoc_array_prepend(array, &val_);
}

static void *aoc_array_expand(AocArray *array) {
    AocGenArray *arr = (AocGenArray *)array;
    uint8_t     *new_data = NULL;

    size_t new_capacity = 1;
    if (arr->capacity != 0) {
        new_capacity = arr->capacity << 1;
    }

    if (array->type == AOC_PTR) {
        void *new_ptr_data = realloc(arr->ptr_data, new_capacity * sizeof(void *));
        if (new_ptr_data) {
            arr->ptr_data = new_ptr_data;
            arr->capacity = new_capacity;
        }
    } else {
        new_data = (uint8_t *)realloc(arr->data, arr->element_size * (new_capacity));
        if (new_data) {
            arr->data = new_data;
            arr->capacity = new_capacity;
        }
    }

    return array;
}

static void *aoc_array_shrink(AocArray *array) {
    AocGenArray *arr = (AocGenArray *)array;
    uint8_t     *new_data = NULL;
    const size_t shrunk_capacity = arr->capacity >> 1;

    if (arr->length < shrunk_capacity) {
        if (array->type == AOC_PTR) {
            void *new_ptr_data = realloc(arr->ptr_data, sizeof(void *) * MAX(shrunk_capacity, 1));
            if (new_ptr_data) {
                arr->ptr_data = new_ptr_data;
                arr->capacity = shrunk_capacity;
            }
        } else {
            new_data = (uint8_t *)realloc(arr->data, arr->element_size * (MAX(shrunk_capacity, 1)));
            if (new_data) {
                arr->data = new_data;
                arr->capacity = shrunk_capacity;
            }
        }
    }

    return array;
}

void *aoc_array_append(AocArray *array, void *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type >= AOC_COUNT) {
        fprintf(stderr, "Type %s is not implemented in aoc_array_append()\n",
                aoc_type_string(array->type));
        return NULL;
    }

    AocGenArray *arr = (AocGenArray *)array;
    if (array->length == arr->capacity) {
        array = (AocArrayPtr)aoc_array_expand(array);
    }
    if (array->type == AOC_PTR) {
        arr->ptr_data[array->length] = value;
    } else {
        memcpy((arr->data + (array->length * arr->element_size)), value, arr->element_size);
    }
    array->length += 1;
    return array;
}

void *aoc_array_prepend(AocArrayPtr array, void *value) {
    if (array == NULL) {
        return NULL;
    }

    if (array->type >= AOC_COUNT) {
        return NULL;
    }

    AocGenArray *arr = (AocGenArray *)array;
    if (array->length + 1 > arr->capacity) {
        array = (AocArrayPtr)aoc_array_expand(array);
    }

    if (array->type == AOC_PTR) {
        memmove(arr->ptr_data + 1, arr->data, arr->length * sizeof(void *));
        arr->ptr_data[0] = value;
    } else {
        memmove(arr->data + arr->element_size, arr->data, arr->element_size * arr->length);
        memcpy(arr->data, value, arr->element_size);
    }
    array->length += 1;
    return array;
}

void *aoc_array_index(AocArray *array, size_t index) {
    if (index >= aoc_array_length(array)) {
        return NULL;
    }

    AocGenArray *arr = (AocGenArray *)array;
    size_t       real_index = index * arr->element_size;

    if (array->type == AOC_PTR) {
        return (arr->ptr_data[index]);
    }
    return (void *)((&arr->data[real_index]));
}

void aoc_array_free(AocArray *array, int free_segments) {
    if (array == NULL) {
        return;
    }

    AocGenArray *arr = (AocGenArray *)array;
    if (free_segments) {
        if (array->type == AOC_PTR) {
            for (size_t index = 0; index < aoc_array_length(array); index++) {
                void *segment = arr->ptr_data[index];
                free(segment);
            }
        } else {
            for (size_t index = 0; index < aoc_array_length(array); index++) {
                void *segment = (void *)*(char **)(arr->data + index * arr->element_size);
                free(segment);
            }
        }
    }
    if (array->type == AOC_PTR) {
        free(arr->ptr_data);
    } else {
        free(arr->data);
    }
    free(array);
}

void aoc_array_print(AocArray *array) {
    char         buffer[100];
    Line         l;
    AocGenArray *arr = (AocGenArray *)array;
    printf("Type: %s (%d), Length: %zu, Capacity: %zu\n", aoc_type_string(array->type), array->type,
           aoc_array_length(array), arr->capacity);
    for (size_t i = 0; i < aoc_array_length(array); i++) {
        switch (array->type) {
            case AOC_INT32:
                printf("%s%d%s", i == 0 ? "{" : "", aoc_int32_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_UINT32:
                printf("%s%u%s", i == 0 ? "{" : "", aoc_uint32_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_INT64:
                printf("%s%" PRId64 "%s", i == 0 ? "{" : "", aoc_int64_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_UINT64:
                printf("%s%" PRIu64 "%s", i == 0 ? "{" : "", aoc_uint64_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_STR:
                printf("%s\"%s\"%s", i == 0 ? "{" : "", aoc_str_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_CHAR:
                printf("%s'%c'%s", i == 0 ? "{" : "", aoc_char_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_UCHAR:
                printf("%s'%uc'%s", i == 0 ? "{" : "", aoc_uchar_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_POINT:
                printf("%s%s%s", i == 0 ? "{" : "",
                       point_to_string(aoc_point_array_index(array, i), buffer, 100),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_LINE:
                l = aoc_line_array_index(array, i);
                printf("%s%s -> %s%s", i == 0 ? "{" : "", point_to_string(l.p0, buffer, 100),
                       point_to_string(l.p1, buffer, 100),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            case AOC_PTR:
                printf("%s%p%s", i == 0 ? "{" : "", aoc_ptr_array_index(array, i),
                       i == aoc_array_length(array) - 1 ? "}\n" : ", ");
                break;
            default:
                printf("Print of requested array type is not implemented\n");
                return;
        }
    }
}

void *aoc_array_pop_index(AocArrayPtr array, size_t index) {
    AocGenArray *arr = (AocGenArray *)array;
    if (!arr) {
        return NULL;
    }

    if (index >= aoc_array_length(arr)) {
        return NULL;
    }

    void *result = aoc_array_index(array, index);

    if (index != aoc_array_length(arr) - 1) {
        if (array->type == AOC_PTR) {
            memmove(arr->ptr_data + index, arr->ptr_data + index + 1,
                    sizeof(void *) * (arr->length - index - 1));
        } else {
            memmove((arr->data + index * arr->element_size),
                    (arr->data + (index + 1) * arr->element_size),
                    arr->element_size * (aoc_array_length(arr) - index - 1));
        }
    }

    arr->length -= 1;

    array = aoc_array_shrink(array);

    return result;
}

AocArrayPtr aoc_array_remove_index(AocArrayPtr array, size_t index) {
    AocGenArray *arr = (AocGenArray *)array;
    if (!arr) {
        return NULL;
    }

    if (index >= aoc_array_length(arr)) {
        return NULL;
    }

    if (arr->type == AOC_STR) {
        void *ptr = aoc_str_array_index(array, index);
        free(ptr);
    }

    if (arr->type == AOC_PTR) {
        void *ptr = aoc_ptr_array_index(array, index);
        free(ptr);
    }

    if (index != aoc_array_length(arr) - 1) {
        if (arr->type == AOC_PTR) {
            memmove(arr->ptr_data + index, arr->ptr_data + index + 1,
                    sizeof(void *) * (arr->length - index - 1));
        } else {
            memmove((arr->data + index * arr->element_size),
                    (arr->data + (index + 1) * arr->element_size),
                    arr->element_size * (aoc_array_length(arr) - index - 1));
        }
    }

    arr->length -= 1;

    array = aoc_array_shrink(array);

    return array;
}

void *aoc_array_get_data(AocArrayPtr array) {
    AocGenArray *arr = (AocGenArray *)array;
    void        *data = NULL;

    if (array->type == AOC_PTR) {
        data = (void *)arr->ptr_data;
    } else {
        data = (void *)arr->data;
    }

    return data;
}

AocArrayPtr aoc_array_copy(AocArrayPtr array) {
    AocGenArray *source = (AocGenArray *)array;
    AocGenArray *destination = (AocGenArray *)aoc_array_new(source->type, source->capacity);
    if (array->type == AOC_PTR) {
        memcpy(destination->ptr_data, source->ptr_data, source->capacity * sizeof(void *));

    } else {
        memcpy(destination->data, source->data, source->capacity * source->element_size);
    }
    destination->length = source->length;
    destination->element_size = source->element_size;

    return (AocArrayPtr)destination;
}

AocArrayPtr aoc_int32_array_set_index(AocArrayPtr array, size_t index, int32_t value) {
    if (!array) {
        return NULL;
    }
    if (array->type != AOC_INT32) {
        return NULL;
    }

    AocGenArray *dst = (AocGenArray *)array;
    int32_t     *data = (int32_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_int64_array_set_index(AocArrayPtr array, size_t index, int64_t value) {
    if (!array) {
        return NULL;
    }
    if (array->type != AOC_INT64) {
        return NULL;
    }

    AocGenArray *dst = (AocGenArray *)array;
    int64_t     *data = (int64_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_uint32_array_set_index(AocArrayPtr array, size_t index, uint32_t value) {
    if (!array) {
        return NULL;
    }
    if (array->type != AOC_UINT32) {
        return NULL;
    }

    AocGenArray *dst = (AocGenArray *)array;
    uint32_t    *data = (uint32_t *)dst->data;
    data[index] = value;

    return array;
}

AocArrayPtr aoc_uint64_array_set_index(AocArrayPtr array, size_t index, uint64_t value) {
    if (!array) {
        return NULL;
    }
    if (array->type != AOC_UINT64) {
        return NULL;
    }

    AocGenArray *dst = (AocGenArray *)array;
    uint64_t    *data = (uint64_t *)dst->data;
    data[index] = value;

    return array;
}

size_t aoc_array_get_element_size(AocArrayPtr array) {
    return ((AocGenArray *)array)->element_size;
}

AocArrayPtr aoc_array_new_from_data(AocArrayType array_type, void *data, size_t length) {
    AocGenArray *arr = (AocGenArray *)aoc_array_new(array_type, length);
    memmove(arr->data, data, length * arr->element_size);
    arr->length = length;
    return (AocArrayPtr)arr;
}

void *aoc_array_last(AocArrayPtr array) {
    return aoc_array_index(array, array->length - 1);
}

double aoc_double_array_sum(AocArrayPtr array) {
    double sum = 0.0;

    for (unsigned i = 0; i < array->length; i++) {
        double *v = (double *)(((AocGenArray *)array)->data + i * sizeof(double));
        sum += *v;
    }

    return sum;
}

double aoc_double_array_mean(AocArrayPtr array) {
    return aoc_double_array_sum(array) / (double)array->length;
}

double aoc_double_array_stddev(AocArrayPtr array) {
    double mean = aoc_double_array_mean(array);
    double var = 0;

    for (unsigned i = 0; i < array->length; i++) {
        double *v = (double *)(((AocGenArray *)array)->data + i * sizeof(double));
        var += pow(*v - mean, 2);
    }

    return sqrt(var / array->length);
}

AocArrayPtr aoc_array_reverse(AocArrayPtr array) {
    AocArrayPtr reversed = aoc_array_new(array->type, array->length);
    reversed->free_segments = array->free_segments;
    for (int32_t i = array->length - 1; i >= 0; i--) {
        aoc_array_append(reversed, aoc_array_index(array, i));
    }

    return reversed;
}
