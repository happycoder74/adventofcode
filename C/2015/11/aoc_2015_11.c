#include <glib.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    return data;
}

gchar password_next_letter(gchar letter) {
    gchar next_letter;

    next_letter = ((letter + 1) - 'a') % ('z' - 'a' + 1) + 'a';
    switch(next_letter) {
        case 'i':
        case 'o':
        case 'l':
            next_letter++;
            break;
        default:
            break;
    }
    return next_letter;
}

void password_next(gchar *password) {
    guint index;

    for (index = strlen(password) - 1; index != 0; index--) {
        password[index] = password_next_letter(password[index]);
        if (password[index] != 'a')
            break;
    }
}

gboolean invalid_letters(const gchar *password) {
    guint i;
    guint length = strlen(password);

    for(i = 0; i < length; i++) {
        if ((password[i] == 'i')
                || (password[i] == 'o')
                || (password[i] == 'l')) {
            return TRUE;
        }
    }
    return FALSE;
}

gboolean has_triplets(const gchar *password) {
    guint i;
    guint length = strlen(password);

    for (i = 0; i < length - 2; i++) {
        if ((password[i + 1] == password[i] + 1) &&
            (password[i + 2] == password[i] + 2)) {
            return TRUE;
        }
    }
    return FALSE;
}

static gboolean has_doubles(const gchar *password) {
    guint i, j;
    guint length = strlen(password);
    for (i = 0; i < length - 1; i++) {
        if (password[i] == password[i + 1]) {
            for (j = i + 2; j < length - 1; j++) {
                if ((password[j] == password[j + 1]) && (password[j] != password[i])) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

gboolean password_validate(const gchar *password) {
    if (invalid_letters(password)) {
        return FALSE;
    }

    if (!has_triplets(password)) {
        return FALSE;
    }

    if(!has_doubles(password)) {
        return FALSE;
    }

    return TRUE;
}

void solve(gchar *password) {
    while (!password_validate(password)) {
        password_next(password);
    }
    return;
}

gpointer solve_part_1(AocData_t *data) {
    gchar *password = g_array_index(data->data, gchar *, 0);
    solve(password);
    return g_strdup_printf("%s", password);
}

gpointer solve_part_2(AocData_t *data) {
    gchar *password = g_array_index(data->data, gchar *, 0);

    password_next(password);
    solve(password);

    return g_strdup_printf("%s", password);
}

gpointer solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2015, 11);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
#include "aoc_utils.h"


