#include <aoc_sets.h>

Set *set_new(SetType settype) {
    Set *result;

    result = g_new(Set, 1);
    result->settype = settype;

    return result;
}

Set *set_new_with_data(GArray *data, SetType settype) {
    Set *result = set_new(settype);
    result->settype = settype;

    switch (result->settype) {
        case SET_INT:
	    result->set = g_hash_table_new(g_int_hash, g_int_equal);
            for (guint i = 0; i < data->len; i++) {
                gint val = g_array_index(data, int, i);
                g_hash_table_add(result->set, GINT_TO_POINTER(val));
            }
            break;
        case SET_CHAR:
	    result->set = g_hash_table_new(g_int_hash, g_int_equal);
            for (guint i = 0; i < data->len; i++) {
                char val = g_array_index(data, char, i);
                g_hash_table_add(result->set, GINT_TO_POINTER(val));
            }
            break;
        case SET_STR:
            result->set = g_hash_table_new(g_str_hash, g_str_equal);
            for (guint i = 0; i < data->len; i++) {
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

/*Set *set_intersect(Set *set1, Set *set2) {
    Set *result;

    if (g_array_get_element_size(set1->set) != g_array_get_element_size(set2->set)) {
        return NULL;
    }

    result = set_new(set1->settype);
    switch (result->settype) {
        case SET_INT:
            result->set = g_array_new(FALSE, TRUE, sizeof(int));
            for (guint i = 0; i < set1->set->len; i++) {
                int val1 = g_array_index(set1->set, int, i);
                for (guint j = 0; j < set2->set->len; j++) {
                    int val2 = g_array_index(set2->set, int, j);
                    if ((val1) == (val2)) {
                        g_array_append_val(result->set, val1);
                    }
                }
            }
            break;
        case SET_CHAR:
            result->set = g_array_new(FALSE, TRUE, sizeof(char));
            for (guint i = 0; i < set1->set->len; i++) {
                char val1 = g_array_index(set1->set, char, i);
                for (guint j = 0; j < set2->set->len; j++) {
                    char val2 = g_array_index(set2->set, char, j);
                    if ((val1) == (val2)) {
                        g_array_append_val(result->set, val1);
                    }
                }
            }
            break;
        case SET_STR:
            result->set = g_array_new(FALSE, TRUE, sizeof(char *));
            for (guint i = 0; i < set1->set->len; i++) {
                char *val1 = g_array_index(set1->set, char *, i);
                for (guint j = 0; j < set2->set->len; j++) {
                    char *val2 = g_array_index(set2->set, char *, j);
                    if (!g_strcmp0(val1, val2)) {
                        g_array_append_val(result->set, val1);
                    }
                }
            }
            break;
        case SET_REAL:
        default:
            g_free(result);
            return NULL;

    }

    return result;
}

Set *set_difference(Set *set1, Set *set2) {
    Set *result;
    gboolean exists;

    if (g_array_get_element_size(set1->set) != g_array_get_element_size(set2->set)) {
        return NULL;
    }

    result = set_new(set1->settype);

    switch (result->settype) {
        case SET_INT:
            result->set = g_array_new(FALSE, TRUE, sizeof(int));
            for (guint i = 0; i < set1->set->len; i++) {
                exists = FALSE;
                gint val1 = g_array_index(set1->set, int, i);
                for (guint j=0; j < set2->set->len; j++) {
                    gint val2 = g_array_index(set2->set, int, j);
                    if (val1 == val2) {
                        exists = TRUE;
                        break;
                    }
                }
                if (!exists)
                    g_array_append_val(result->set, val1);
            }
            break;
        case SET_CHAR:
            result->set = g_array_new(FALSE, TRUE, sizeof(char));
            for (guint i = 0; i < set1->set->len; i++) {
                exists = FALSE;
                char val1 = g_array_index(set1->set, char, i);
                for (guint j=0; j < set2->set->len; j++) {
                    char val2 = g_array_index(set2->set, char, j);
                    if (val1 == val2) {
                        exists = TRUE;
                        break;
                    }
                }
                if (!exists)
                    g_array_append_val(result->set, val1);
            }
            break;
        case SET_STR:
            result->set = g_array_new(FALSE, TRUE, sizeof(char *));
            for (guint i = 0; i < set1->set->len; i++) {
                exists = FALSE;
                char * val1 = g_array_index(set1->set, char *, i);
                for (guint j=0; j < set2->set->len; j++) {
                    char * val2 = g_array_index(set2->set, char *, j);
                    if (!g_strcmp0(val1, val2)) {
                        exists = TRUE;
                        break;
                    }
                }
                if (!exists)
                    g_array_append_val(result->set, val1);
            }
            break;
        case SET_REAL:
        default:
            g_free(result);
            return NULL;
    }

    return result;
}

int set_add_int(Set *set, int element) {
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

Set *set_union(Set *set1, Set *set2) {
    Set *result;

    result = set_new(set1->settype);

    switch (result->settype) {
        case SET_INT:
            result->set = g_array_new(FALSE, TRUE, sizeof(int));
            for (guint i = 0; i < set1->set->len; i++) {
                int val = g_array_index(set1->set, int, i);
                g_array_append_val(result->set, val);
            }
            for (guint i = 0; i < set2->set->len; i++) {
                int val = g_array_index(set2->set, int, i);
                set_add(result, GINT_TO_POINTER(val));
            }
            break;
        case SET_CHAR:
            result->set = g_array_new(FALSE, TRUE, sizeof(char));
            for (guint i = 0; i < set1->set->len; i++) {
                char val = g_array_index(set1->set, char, i);
                g_array_append_val(result->set, val);
            }
            for (guint i = 0; i < set2->set->len; i++) {
                char val = g_array_index(set2->set, char, i);
                set_add(result, GINT_TO_POINTER(val));
            }
            break;
        default:
            g_free(result);
            return NULL;
    }
    return result;
}
*/

void set_free(Set *set) {
    if (set) {
        g_hash_table_destroy(set->set);
        g_free(set);
    }
}

