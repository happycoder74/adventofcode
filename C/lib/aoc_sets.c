#include <aoc_sets.h>

Set *set_new(SetType settype) {
    Set *result;

    result = g_new(Set, 1);
    result->settype = settype;

    return result;
}

Set *set_new_with_data(GArray *data, SetType settype) {
    guint i;
    Set *result;

    result = set_new(settype);
    result->settype = settype;

    switch (result->settype) {
        case SET_INT:
        case SET_CHAR:
            result->set = g_hash_table_new(g_direct_hash, g_direct_equal);
            for (i = 0; i < data->len; i++) {
                if (result->settype == SET_CHAR) {
                    gchar val = g_array_index(data, gchar, i);
                    g_hash_table_add(result->set, GUINT_TO_POINTER(val));
                } else {
                    gint val = g_array_index(data, gint, i);
                    g_hash_table_add(result->set, GINT_TO_POINTER(val));
                }
            }
            break;
        case SET_STR:
            result->set = g_hash_table_new(g_str_hash, g_str_equal);
            for (i = 0; i < data->len; i++) {
                char *val = g_strdup(g_array_index(data, char *, i));
                g_hash_table_add(result->set, val);
            }
            break;
        default:
            g_free(result);
            return NULL;
            break;
    }
    return result;
}

Set *set_intersect(Set *set1, Set *set2) {
    Set *result;
    gpointer *keys;
    gpointer key;
    guint length;
    guint i;

    if (!set1 || !set2) {
        g_printerr("NULL set given\n");
    }

    if (set1->settype != set2->settype) {
        g_printerr("Not matching set types\n");
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
        case SET_FLOAT:
        case SET_DOUBLE:
        case SET_LONG:
            g_print("Not yet implemented\n");
        default:
            g_free(result);
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

GArray *set_get_values(Set *set) {
    guint length;
    guint i;
    guint val;
    GArray *return_array;
    gpointer *keys;

    keys = g_hash_table_get_keys_as_array(set->set, &length);
    switch(set->settype) {
        case SET_INT:
            return_array = g_array_sized_new(FALSE, FALSE, sizeof(gint), length);
            for (i = 0; i < length; i++) {
                val = GPOINTER_TO_INT(keys[i]);
                g_array_append_val(return_array, val);
            }
            break;
        case SET_CHAR:
            return_array = g_array_sized_new(FALSE, FALSE, sizeof(guint), length);
            for (i = 0; i < length; i++) {
                val = GPOINTER_TO_INT(keys[i]);
                g_array_append_val(return_array, val);
            }
            break;
        default:
            g_print("Not yet implemented for type %s\n", set_string_type(set->settype));
            return NULL;
            break;
    }
    return return_array;
}

Set *set_difference(Set *set1, Set *set2) {
    Set *result;
    gpointer *keys;
    gpointer key;
    guint length;
    guint i;


    if (!set1 || !set2) {
        g_printerr("NULL set given\n");
    }

    if (set1->settype != set2->settype) {
        g_printerr("Not matching set types\n");
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
        case SET_FLOAT:
        case SET_DOUBLE:
        case SET_LONG:
            g_print("Not yet implemented for set type %s\n", set_string_type(result->settype));
        default:
            g_free(result);
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
    gpointer *keys;
    gpointer key;
    guint length;
    guint i;

    if (!set1 || !set2) {
        g_printerr("NULL set given\n");
    }

    if (set1->settype != set2->settype) {
        g_printerr("Not matching set types\n");
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
        case SET_FLOAT:
        case SET_DOUBLE:
        case SET_LONG:
            g_print("Not yet implemented for set type %s\n", set_string_type(result->settype));
        default:
            g_free(result);
            return NULL;
    }

    return result;
}

void set_free(Set *set) {
    if (set) {
        g_hash_table_destroy(set->set);
        g_free(set);
    }
}

