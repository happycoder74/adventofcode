#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Passport {
    char line[1000];
};

struct Input {
    struct Passport passports[1000];
    size_t          count;
};

static char *str_trim_trailing(char *str) {
    char *ptr = str + strlen(str) - 1;
    while (!isgraph((unsigned char)*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    return str;
}

static unsigned short int is_valid(struct Passport *passport) {
    char *required_keys[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", NULL};
    for (char **ptr = required_keys; *ptr != NULL; ptr++) {
        if (!strstr(passport->line, *ptr))
            return 0;
    }
    return 1;
}

static unsigned short int is_valid_2(struct Passport *passport) {
    char              *required_keys[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", NULL};
    char              *key;
    unsigned short int valid = 1;
    for (char **ptr = required_keys; *ptr != NULL; ptr++) {
        key = strstr(passport->line, *ptr);
        char *start = key + 4;
        char *end = strchr(key, ' ');
        if (!end)
            end = key + strlen(key);
        if (!strncmp(key, "byr", 3)) {
            int int_val = atoi(start);
            if ((int_val < 1920) || (2002 < int_val)) {
                return 0;
            }
        } else if (!strncmp(key, "iyr", 3)) {
            int int_val = atoi(start);
            if ((int_val < 2010) || (2020 < int_val)) {
                return 0;
            }
        } else if (!strncmp(key, "eyr", 3)) {
            int int_val = atoi(start);
            if ((int_val < 2020) || (2030 < int_val)) {
                return 0;
            }
        } else if (!strncmp(key, "hcl", 3)) {
            if (((start[0]) != '#') || ((end - start) < 7)) {
                return 0;
            }
            for (char *c = start + 1; c != end; c++) {
                if (!isdigit(*c) && ((*c < 'a') || (*c > 'f'))) {
                    return 0;
                }
            }
        } else if (!strncmp(key, "ecl", 3)) {
            char *valid_colors[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth", NULL};
            unsigned short int color_valid = 0;
            for (char **col = valid_colors; *col != NULL; col++) {
                if (!strncmp(start, *col, 3)) {
                    color_valid = 1;
                    break;
                }
            }
            if (!color_valid) {
                return 0;
            }
        } else if (!strncmp(key, "pid", 3)) {
            if ((end - start) != 9) {
                return 0;
            }
            for (char *c = start; c != end; c++) {
                if (!isdigit(*c)) {
                    return 0;
                    break;
                }
            }
        } else if (!strncmp(key, "hgt", 3)) {
            int int_val = 0;
            if (((*(end - 2) == 'c') && (*(end - 1) == 'm'))) {
                int_val = atoi(start);
                if ((int_val < 150) || (int_val > 193)) {
                    return 0;
                }
            } else if ((*(end - 2) == 'i' && (*(end - 1) == 'n'))) {
                int_val = atoi(start);
                if ((int_val < 59) || (int_val > 76)) {
                    return 0;
                }
            } else {
                return 0;
            }
        }
    }
    return valid;
}

int solve_part_1(void *inp) {
    struct Input *input = (struct Input *)inp;
    int           count = 0;
    for (unsigned pp_index = 0; pp_index < input->count; pp_index++) {
        if (is_valid(input->passports + pp_index))
            count++;
    }
    return count;
}

int solve_part_2(void *inp) {
    struct Input    *input = (struct Input *)inp;
    int              count = 0;
    struct Passport *passport = NULL;
    for (unsigned pp_index = 0; pp_index < input->count; pp_index++) {
        passport = input->passports + pp_index;
        if (is_valid(passport)) {
            if (is_valid_2(input->passports + pp_index))
                count++;
        }
    }
    return count;
}

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char  line[255];
    char  filepath[255];
    char  filename[40];

    const unsigned int year = 2020;
    const unsigned int day = 4;

    struct Input input = {0};
    AocTimer_t  *timer = NULL;

    if ((argc > 1)) {
        if (!strcmp(argv[1], "--test")) {
            snprintf(filename, 40, "test_input.txt");
        } else {
            snprintf(filename, 40, "%s", argv[1]);
        }
    } else {
        snprintf(filename, 40, "input.txt");
    }

    snprintf(filepath, 254, "%s/%d/%02d/%s", getenv("AOC_DATA_LOCATION"), year, day, filename);

    timer = aoc_timer_new();
    aoc_timer_start(timer);
    if (!(fp = fopen(filepath, "r"))) {
        fprintf(stderr, "Unable to open file:\n%s\n", filepath);
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    while (fgets(line, 254, fp) != NULL) {
        struct Passport *passport = &input.passports[index];
        char            *str = str_trim_trailing(line);
        if (!line[0]) {
            str_trim_trailing(passport->line);
            index++;
            continue;
        }
        if (strlen(passport->line) == 0) {
            memmove(passport->line, str, strlen(str) * sizeof(str[0]));
        } else {
            memmove(passport->line + strlen(passport->line), str, strlen(str) * sizeof(str[0]));
        }
        passport->line[strlen(passport->line)] = ' ';
    }
    str_trim_trailing(input.passports[index].line);
    input.count = index + 1;
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func_new(1, solve_part_1, &input, 1);
    timer_func_new(2, solve_part_2, &input, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    return 0;
}
