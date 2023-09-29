#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "aoc_sets.h"
#include "aoc_types.h"
#include "aoc_array.h"

Set *set_new(SetType settype) {
    Set *result;

    result = (Set *)malloc(sizeof(Set));
    result->settype = settype;

    return result;
}

Set *set_new_with_data(AocArrayPtr data, SetType settype) {
    uint32_t i;
    Set *result;

    result = set_new(settype);
    result->settype = settype;

    switch (result->settype) {
        case SET_INT:
        case SET_CHAR:
            result->set = g_hash_table_new(g_direct_hash, g_direct_equal);
            for (i = 0; i < aoc_array_length(data); i++) {
                if (result->settype == SET_CHAR) {
                    char val = aoc_char_array_index(data, i);
                    g_hash_table_add(result->set, (void *)(int64_t)(val));
                } else {
                    int val = aoc_int_array_index(data, i);
                    g_hash_table_add(result->set, (void *)(int64_t)(val));
                }
            }
            break;
        case SET_STR:
            result->set = g_hash_table_new(g_str_hash, g_str_equal);
            for (i = 0; i < aoc_array_length(data); i++) {
                char *val = strdup(aoc_str_array_index(data, i));
                g_hash_table_add(result->set, val);
            }
            break;
        default:
            free(result);
            return NULL;
            break;
    }
    return result;
}

Set *set_intersect(Set *set1, Set *set2) {
    Set *result;
    void **keys;
    void *key;
    uint32_t length;
    uint32_t i;

    if (!set1 || !set2) {
        fprintf(stderr, "NULL set given\n");
        return NULL;
    }

    if (set1->settype != set2->settype) {
        fprintf(stderr, "Not matching set types\n");
        return NULL;
    }

    result = set_new(set1->settype);

    switch (result->settype) {
        case SET_INT:
        case SET_CHAR:
            result->set = g_hash_table_new(g_direct_hash, g_direct_equal);
            keys = g_hash_table_get_keys_as_array(set1->set, &length);
            for (i = 0; i < length; i++) {
                key = keys[i];
                if(g_hash_table_contains(set2->set, key)) {
                    g_hash_table_add(result->set, key);
                }
            }
            break;
        case SET_STR:
            result->set = g_hash_table_new(g_str_hash, g_str_equal);
            keys = g_hash_table_get_keys_as_array(set1->set, &length);
            for (i = 0; i < length; i++) {
                key = keys[i];
                if(g_hash_table_contains(set2->set, key)) {
                    g_hash_table_add(result->set, key);
                }
            }
            break;
        default:
            fprintf(stderr, "Not yet implemented\n");
            free(result);
            return NULL;
    }

    return result;
}

static gchar *set_string_type(SetType settype) {
    gchar *settypes[] = {
        "int",
        "long",
        "char",
        "string",
        "float",
        "double"
    };
    return settypes[settype];
}

AocArrayPtr set_get_values(Set *set) {
    uint32_t length;
    uint32_t i;
    AocArrayPtr return_array;
    void **keys;

    keys = g_hash_table_get_keys_as_array(set->set, &length);
    switch(set->settype) {
        case SET_INT:
            return_array = aoc_array_sized_new(sizeof(int), length);
            for (i = 0; i < length; i++) {
                int val = (int)(int64_t)(keys[i]);
                aoc_int_array_append(return_array, val);
            }
            break;
        case SET_CHAR:
            return_array = aoc_array_sized_new(sizeof(char), length);
            for (i = 0; i < length; i++) {
                char val = (char)(int64_t)(keys[i]);
                aoc_char_array_append(return_array, val);
            }
            break;
        case SET_STR:
            return_array = aoc_array_sized_new(sizeof(char *), length);
            for (i = 0; i < length; i++) {
                char *val = (char *)(keys[i]);
                aoc_str_array_append(return_array, val);
            }
            break;
        default:
            fprintf(stderr, "Not yet implemented for type %s\n", set_string_type(set->settype));
            return NULL;
            break;
    }
    return return_array;
}

Set *set_difference(Set *set1, Set *set2) {
    Set *result;
    void **keys;
    void *key;
    uint32_t length;
    uint32_t i;


    if (!set1 || !set2) {
        fprintf(stderr, "NULL set given\n");
        return NULL;
    }

    if (set1->settype != set2->settype) {
        fprintf(stderr, "Not matching set types\n");
        return NULL;
    }

    result = set_new(set1->settype);

    switch (result->settype) {
        case SET_CHAR:
        case SET_INT:
            result->set = g_hash_table_new(g_direct_hash, g_direct_equal);
            keys = g_hash_table_get_keys_as_array(set1->set, &length);
            for (i = 0; i < length; i++) {
                key = keys[i];
                if(!g_hash_table_contains(set2->set, key)) {
                    g_hash_table_add(result->set, key);
                }
            }
            break;
        case SET_STR:
            result->set = g_hash_table_new(g_str_hash, g_str_equal);
            keys = g_hash_table_get_keys_as_array(set1->set, &length);
            for (i = 0; i < length; i++) {
                key = keys[i];
                if(!g_hash_table_contains(set2->set, key)) {
                    g_hash_table_add(result->set, key);
                }
            }
            break;
        default:
            fprintf(stderr, "Not yet implemented for set type %s\n", set_string_type(result->settype));
            free(result);
            return NULL;
    }

    return result;
}

/* int set_add_int(Set *set, int element) {
    int val;

    for (guint i = 0; i < set->set->len; i++) {
        val = g_array_index(set->set, int, i);
        if (val == element) {
            return 0;
        }
    }
    g_array_append_val(set->set, element);

    return 1;
}

int set_add_char(Set *set, char element) {
    char val;

    for (guint i = 0; i < set->set->len; i++) {
        val = g_array_index(set->set, char, i);
        if (val == element) {
            return 0;
        }
    }
    g_array_append_val(set->set, element);

    return 1;
}

int set_add(Set *set, gconstpointer v) {
    switch (set->settype) {
        case SET_INT:
            return set_add_int(set, (int) (long)v);
            break;
        case SET_CHAR:
            return set_add_char(set, (char) (long)v);
            break;
        default:
            return 0;
            break;
    }

}
*/

Set *set_union(Set *set1, Set *set2) {
    Set *result;
    void **keys;
    void *key;
    uint32_t length;
    uint32_t i;

    if (!set1 || !set2) {
        fprintf(stderr, "NULL set given\n");
        return NULL;
    }

    if (set1->settype != set2->settype) {
        fprintf(stderr, "Not matching set types\n");
        return NULL;
    }

    result = set_new(set1->settype);

    switch (result->settype) {
        case SET_CHAR:
        case SET_INT:
            result->set = g_hash_table_new(g_direct_hash, g_direct_equal);
            keys = g_hash_table_get_keys_as_array(set1->set, &length);
            for (i = 0; i < length; i++) {
                key = keys[i];
                g_hash_table_add(result->set, key);
            }
            keys = g_hash_table_get_keys_as_array(set2->set, &length);
            for (i = 0; i < length; i++) {
                if (!g_hash_table_contains(set1->set, keys[i])) {
                    g_hash_table_add(result->set, keys[i]);
                }
            }
            break;
        case SET_STR:
            result->set = g_hash_table_new(g_str_hash, g_str_equal);
            keys = g_hash_table_get_keys_as_array(set1->set, &length);
            for (i = 0; i < length; i++) {
                key = keys[i];
                g_hash_table_add(result->set, key);
            }
            keys = g_hash_table_get_keys_as_array(set2->set, &length);
            for (i = 0; i < length; i++) {
                if (!g_hash_table_contains(set1->set, keys[i])) {
                    g_hash_table_add(result->set, keys[i]);
                }
            }
            break;
        default:
            fprintf(stderr, "Not yet implemented for set type %s\n", set_string_type(result->settype));
            free(result);
            return NULL;
    }

    return result;
}

void set_free(Set *set) {
    if (set) {
        g_hash_table_destroy(set->set);
        free(set);
    }
}

void set_print(Set *set) {
    AocArrayPtr values;
    if (set == NULL) {
        fprintf(stderr, "Set is undefined\n");
        return;
    }

    values = set_get_values(set);
    if (aoc_array_length(values) == 0) {
        printf("Set is empty\n");
        return;
    }
    switch(set->settype) {
        case SET_INT:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                g_print("%s%d", i == 0 ? "{":", ", aoc_int_array_index(values, i));
            }
            g_print("}\n");
            break;
        case SET_CHAR:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                g_print("%s'%c'", i == 0 ? "{":", ", aoc_char_array_index(values, i));
            }
            g_print("}\n");
            break;
        case SET_STR:
            for (size_t i = 0; i < aoc_array_length(values); i++) {
                g_print("%s'%s'", i == 0 ? "{":", ", aoc_str_array_index(values, i));
            }
            g_print("}\n");
            break;
        default:
            break;
    }
}
