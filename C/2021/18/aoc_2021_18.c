#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "aoc_types.h"
#include "aoc_string.h"
#include "aoc_utils.h"
#include "aoc_array.h"
#include "aoc_timer.h"

typedef struct {
    int num;
    int level;
} SFVal;

typedef struct {
    SFVal *number;
    int size;
} SFNumber;

void sf_number_free(SFNumber *sn) {
    if (sn != NULL) {
        free(sn->number);
    }
    free(sn);
}

void sf_number_print(SFNumber *sn) {
    int i;
    if (!sn)
        return;

    if (sn->size <= 0) {
        return;
    }
    printf("[\n");
    for (i = 0; i < sn->size; i++) {
        printf(" (%d, %d)\n", sn->number[i].num, sn->number[i].level);
    }
    printf("]\n");

}

SFNumber *sf_number_new(int len) {
    SFNumber *result;

    result = (SFNumber *)malloc(sizeof(SFNumber));
    result->number = (SFVal *)calloc(sizeof(SFVal), len);
    result->size = len;

    return result;
}

int sf_number_magnitude(SFNumber *sn) {
    int mag;
    SFVal *nlist;

    int level, i, j, size;

    size = sn->size;
    nlist = (SFVal *)malloc(sizeof(SFVal) * sn->size);
    for (i = 0; i < size; i++) {
        nlist[i] = sn->number[i];
    }

    for (level = 4; level > 0; level--) {
        for (i = 0; i < size; i++) {
            if (level == nlist[i].level) {
                nlist[i].num = nlist[i].num * 3 + nlist[i + 1].num * 2;
                nlist[i].level -= 1;
                for (j = i + 1; j < size - 1; j++) {
                    nlist[j] = nlist[j + 1];
                }
                size -= 1;
            }
        }
    }

    mag = nlist[0].num;
    free(nlist);

    return mag;
}

int sf_number_eq(SFNumber *sn1, SFNumber *sn2) {
    int i;

    if (sn1->size != sn2->size) {
        return 0;
    }

    for (i = 0; i < sn1->size; i++) {
        if ((sn1->number[i].num != sn2->number[i].num) ||
            (sn1->number[i].level != sn2->number[i].level)) {
            return 0;
        }
    }
    return 1;
}

SFNumber *sf_number_insert(SFNumber *sn, SFVal value, int index) {
    int j;

    sn->number = (SFVal *)realloc(sn->number, (size_t)(sn->size + 1)*sizeof(SFVal));
    sn->size += 1;
    for (j = sn->size - 1; j > index; j--) {
        sn->number[j] = sn->number[j - 1];
    }
    sn->number[index].num = value.num;
    sn->number[index].level = value.level;

    return sn;
}

SFNumber *sf_number_split(SFNumber *sn) {
    int i;
    SFVal right;

    for (i = 0; i < sn->size; i++) {
        if (sn->number[i].num >= 10) {
            right.num = (sn->number[i].num + 1) / 2;
            right.level = (sn->number[i].level + 1);
            sn->number[i].num = (sn->number[i].num / 2);
            sn->number[i].level += 1;

            sn = sf_number_insert(sn, right, i + 1);

            break;
        }
    }

    return sn;
}

SFVal sf_number_pop(SFNumber *sn, int index) {
    SFVal value;
    int j;

    assert(sn != NULL);
    assert(sn->number != NULL);
    assert(sn->size > 0);
    assert((index >= 0) && (index < sn->size));

    value = sn->number[index];

    for (j = index; j < sn->size - 1; j++) {
        sn->number[j] = sn->number[j + 1];
    }
    sn->size -= 1;
    sn->number = (SFVal *)realloc(sn->number, (size_t)sn->size*sizeof(SFVal));

    return value;
}

SFNumber *sf_number_explode(SFNumber *sn) {
    int i;
    SFVal right, left, value;

    for (i = 0; i < sn->size; i++) {
        if (sn->number[i].level >= 5) {
            value = sf_number_pop(sn, i + 1);
            if (i > 0) {
                left = sn->number[i - 1];
                sn->number[i - 1].num = left.num + sn->number[i].num;
            }
            sn->number[i].num = 0;
            sn->number[i].level -= 1;
            if (i < sn->size - 1) {
                right = sn->number[i + 1];
                sn->number[i + 1].num = value.num + right.num;
                sn->number[i + 1].level = right.level;
            }
            break;
        }
    }
    return sn;
}

SFNumber *sf_number_reduce(SFNumber *sn) {
    int size, changed;

    size = sn->size;
    changed = 1;

    while (changed) {
        sn = sf_number_explode(sn);
        if (sn->size != size) {
            size = sn->size;
            continue;
        }
        changed = 0;
        sn = sf_number_split(sn);
        if (size != sn->size) {
            changed = 1;
            size = sn->size;
        }
    }

    return sn;
}

SFNumber *sf_number_add(SFNumber *sn1, SFNumber *sn2) {
    SFNumber *result;
    int i, ptr;

    result = sf_number_new(sn1->size + sn2->size);

    ptr = 0;
    for (i = 0; i < sn1->size; i++) {
        result->number[ptr] = sn1->number[i];
        result->number[ptr].level += 1;
        ptr++;
    }
    for (i = 0; i < sn2->size; i++) {
        result->number[ptr] = sn2->number[i];
        result->number[ptr].level += 1;
        ptr++;
    }

    return result;
}

SFNumber *sf_number_from_string(char *sf_string) {
    int i;
    int size = 0;

    SFNumber *sf;
    SFVal *sfv_p;

    for (i = 0; i < (int)strlen((char *)sf_string); i++) {
        if (isdigit(sf_string[i]))
            size++;
    }
    sf = sf_number_new(size);

    int level = 0;
    sfv_p = &(sf->number[0]);
    for (i = 0; i < (int)strlen((char *)sf_string); i++) {
        level = str_count((char *)sf_string, '[', 0, i)
            - str_count((char *)sf_string, ']', 0, i);
        if (isdigit(sf_string[i])) {
            sfv_p->num = sf_string[i] - '0';
            sfv_p->level = level;
            sfv_p++;
        }
    }

    return sf;
}

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr numbers;
    unsigned int i;
    SFNumber *sn;

    numbers = aoc_array_sized_new(AOC_ARRAY_PTR, aoc_array_length(data));
    for (i = 0; i < aoc_array_length(data); i++){
        sn = sf_number_from_string((char *) aoc_str_array_index(data, i));
        aoc_ptr_array_append(numbers, sn);
    }

    return numbers;
}

void *solve_part_1(AocData_t *data) {
    unsigned int i;
    SFNumber *sn;

    sn = aoc_ptr_array_index(aoc_data_get(data), 0);
    for (i = 1; i < aoc_data_length(data); i++) {
        sn = sf_number_add(sn, aoc_ptr_array_index(aoc_data_get(data), i));
        sn = sf_number_reduce(sn);
    }
    return strdup_printf("%d", sf_number_magnitude(sn));
}

void *solve_part_2(AocData_t *data) {
    int mag_max = 0;
    int mag;
    SFNumber *sn;

    unsigned int i, j;

    for (i = 0; i < aoc_data_length(data); i++) {
        for (j = i + 1; j < aoc_data_length(data); j++) {
            sn = sf_number_add(aoc_ptr_array_index(aoc_data_get(data), i),
                               aoc_ptr_array_index(aoc_data_get(data), j));
            sn = sf_number_reduce(sn);
            mag = sf_number_magnitude(sn);
            mag_max = MAX(mag, mag_max);
            sn = sf_number_add(aoc_ptr_array_index(aoc_data_get(data), j),
                               aoc_ptr_array_index(aoc_data_get(data), i));
            sn = sf_number_reduce(sn);
            mag = sf_number_magnitude(sn);
            mag_max = MAX(mag, mag_max);
        }
    }
    return strdup_printf("%d", mag_max);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    } return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, clean_input);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
