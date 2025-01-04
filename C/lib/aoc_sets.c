#include "aoc_sets.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_string.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocSet *aoc_set_new(AocSetType settype) {
    AocSet *result;

    result = (AocSet *)calloc(1, sizeof(AocSet));
    if (result) {
        result->settype = settype;
        result->set = aoc_hash_table_create(result->settype);
    }
    return result;
}

AocSet *aoc_set_new_with_data(AocArrayPtr data, AocSetType settype) {
    uint32_t i;
    AocSet  *result;

    result = aoc_set_new(settype);
    result->settype = settype;
    result->set = aoc_hash_table_create(result->settype);

    for (i = 0; i < data->length; i++) {
        void *val = aoc_array_index(data, i);
        aoc_hash_table_add(result->set, val);
    }

    return result;
}

AocSet *aoc_set_intersect(AocSet *set1, AocSet *set2) {
    AocSet *result;
    void   *key;

    if (!set1 || !set2) {
        fprintf(stderr, "NULL set given\n");
    }

    if (set1->settype != set2->settype) {
        fprintf(stderr, "Not matching set types\n");
        return NULL;
    }

    result = aoc_set_new(set1->settype);
    AocHashIterator iter;
    aoc_hash_table_iter_init(&iter, set1->set);

    result->set = aoc_hash_table_create(AOC_PTR);
    while (aoc_hash_table_iter_next(&iter, &key, NULL)) {
        if (aoc_hash_table_contains(set2->set, key)) {
            aoc_hash_table_add(result->set, key);
        }
    }

    return result;
}

/* static char *set_string_type(AocSetType settype) { */
/*     char *settypes[] = { */
/*         "int32", */
/*         "int64", */
/*         "uint32", */
/*         "uint64", */
/*         "char", */
/*         "string", */
/*         "float", */
/*         "double", */
/*         "pointer" */
/*     }; */
/*     return settypes[settype]; */
/* } */

AocArrayPtr aoc_set_get_values(AocSet *set) {
    AocArrayPtr return_array;
    void       *key;

    return_array = aoc_array_new((AocArrayType)set->settype, aoc_hash_table_count(set->set));
    AocHashIterator iter;
    aoc_hash_table_iter_init(&iter, set->set);
    while (aoc_hash_table_iter_next(&iter, &key, NULL)) {
        switch (set->settype) {
            case AOC_INT32:
                aoc_int32_array_append(return_array, *(int32_t *)key);
                break;
            case AOC_INT64:
                aoc_int64_array_append(return_array, *(int64_t *)key);
                break;
            case AOC_UINT32:
                aoc_uint32_array_append(return_array, *(uint32_t *)key);
                break;
            case AOC_UINT64:
                aoc_uint64_array_append(return_array, *(uint64_t *)key);
                break;
            case AOC_CHAR:
                aoc_char_array_append(return_array, *(char *)key);
                break;
            default:
                fprintf(stderr, "Not yet implemented");
                break;
        }
    }
    return return_array;
}

AocSet *aoc_set_difference(AocSet *set1, AocSet *set2) {
    AocSet *result;
    void   *key;

    if (!set1 || !set2) {
        fprintf(stderr, "NULL set given\n");
    }

    if (set1->settype != set2->settype) {
        fprintf(stderr, "Not matching set types\n");
        return NULL;
    }

    result = aoc_set_new(set1->settype);
    AocHashIterator iter;
    aoc_hash_table_iter_init(&iter, set1->set);

    result->set = aoc_hash_table_create(AOC_PTR);
    while (aoc_hash_table_iter_next(&iter, &key, NULL)) {
        if (!aoc_hash_table_contains(set2->set, key)) {
            aoc_hash_table_add(result->set, key);
        }
    }

    return result;
}

int aoc_set_add(AocSet *set, const void *value) {
    return aoc_hash_table_add(set->set, value);
}

AocSet *aoc_set_union(AocSet *set1, AocSet *set2) {
    AocSet *result;
    void   *key;

    if (!set1 || !set2) {
        fprintf(stderr, "Set is not initialized\n");
    }

    if (set1->settype != set2->settype) {
        fprintf(stderr, "Not matching set types\n");
        return NULL;
    }

    result = aoc_set_new(set1->settype);

    AocHashIterator iter;
    aoc_hash_table_iter_init(&iter, set1->set);

    result->set = aoc_hash_table_create(AOC_PTR);
    while (aoc_hash_table_iter_next(&iter, &key, NULL)) {
        aoc_hash_table_add(result->set, key);
    }
    aoc_hash_table_iter_init(&iter, set2->set);
    while (aoc_hash_table_iter_next(&iter, &key, NULL)) {
        aoc_hash_table_add(result->set, key);
    }

    return result;
}

void aoc_set_free(AocSet *set) {
    if (set) {
        aoc_hash_table_destroy(&set->set);
    }
}

void set_print(AocSet *set) {
    AocArrayPtr values;
    if (set == NULL) {
        fprintf(stderr, "Set is not initialized\n");
        return;
    }

    values = aoc_set_get_values(set);
    if (aoc_hash_table_count(set->set) == 0) {
        printf("Set is empty\n");
        return;
    }
    switch (set->settype) {
        case AOC_INT32:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                printf("%s %d", i == 0 ? "{" : ", ", aoc_int32_array_index(values, i));
            }
            printf("}\n");
            break;
        case AOC_UINT32:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                printf("%s %u", i == 0 ? "{" : ", ", aoc_uint32_array_index(values, i));
            }
            printf("}\n");
            break;
        case AOC_INT64:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                printf("%s %" PRId64, i == 0 ? "{" : ", ", aoc_int64_array_index(values, i));
            }
            printf("}\n");
            break;
        case AOC_UINT64:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                printf("%s %" PRIu64, i == 0 ? "{" : ", ", aoc_uint64_array_index(values, i));
            }
            printf("}\n");
            break;
        case AOC_CHAR:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                printf("%s'%c'", i == 0 ? "{" : ", ", aoc_char_array_index(values, i));
            }
            printf("}\n");
            break;
        case AOC_STR:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                printf("%s'%s'", i == 0 ? "{" : ", ", aoc_str_array_index(values, i));
            }
            printf("}\n");
            break;
        default:
            fprintf(stderr, "Print functionality not implemented for given set-type\n");
            exit(EXIT_FAILURE);
            break;
    }
}

bool aoc_set_in(AocSet *set, const void *value) {
    return aoc_hash_table_contains(set->set, value);
}
