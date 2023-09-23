#include <stdbool.h>
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <libgen.h>

GArray *clean_input(GArray *data) {
    return data;
}

char password_next_letter(char letter) {
    char next_letter;

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

void password_next(char *password) {
    uint32_t index;

    for (index = strlen(password) - 1; index != 0; index--) {
        password[index] = password_next_letter(password[index]);
        if (password[index] != 'a')
            break;
    }
}

bool invalid_letters(const char *password) {
    size_t i;
    size_t length = strlen(password);

    for(i = 0; i < length; i++) {
        if ((password[i] == 'i')
                || (password[i] == 'o')
                || (password[i] == 'l')) {
            return TRUE;
        }
    }
    return FALSE;
}

bool has_triplets(const char *password) {
    size_t i;
    size_t length = strlen(password);

    for (i = 0; i < length - 2; i++) {
        if ((password[i + 1] == password[i] + 1) &&
            (password[i + 2] == password[i] + 2)) {
            return TRUE;
        }
    }
    return FALSE;
}

static bool has_doubles(const char *password) {
    size_t i, j;
    size_t length = strlen(password);
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

bool password_validate(const char *password) {
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

void solve(char *password) {
    while (!password_validate(password)) {
        password_next(password);
    }
    return;
}

void *solve_part_1(AocData_t *data) {
    char *password = aoc_str_array_index(data->data, 0);
    solve(password);
    return strdup_printf("%s", password);
}

void *solve_part_2(AocData_t *data) {
    char *password = aoc_str_array_index(data->data, 0);

    password_next(password);
    solve(password);

    return strdup_printf("%s", password);
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[100];
    int year, day;

    strcpy(sourcefile, basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, NULL);
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}

