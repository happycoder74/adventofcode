#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include "aoc_utils.h"

typedef struct {
    gint num;
    gint level;
} SFVal;

typedef struct {
    SFVal *number;
    gint size;
} SFNumber;

void sf_number_free(SFNumber *sn) {
    if (sn != NULL) {
        g_free(sn->number);
    }
    g_free(sn);
}

void sf_number_print(SFNumber *sn) {
    int i;
    g_assert(sn != NULL);
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

    result = malloc(sizeof(SFNumber));
    result->number = calloc(sizeof(SFVal), len);
    result->size = len;

    return result;
}

int sf_number_magnitude(SFNumber *sn) {
    int mag;
    SFVal *nlist;

    int level, i, j, size;

    size = sn->size;
    nlist = malloc(sizeof(SFVal) * sn->size);
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

    sn->number = realloc(sn->number, (size_t)(sn->size + 1)*sizeof(SFVal));
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
    sn->number = realloc(sn->number, (size_t)sn->size*sizeof(SFVal));

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

SFNumber *sf_number_from_string(unsigned char *sf_string) {
    int i;
    int size = 0;

    SFNumber *sf;
    SFVal *sfv_p;

    for (i = 0; i < (int)strlen((char *)sf_string); i++) {
        if (isdigit(sf_string[i]))
            size++;
    }
    sf = sf_number_new(size);

    gint level = 0;
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

GArray *clean_data(GArray *data) {
    GArray *numbers;
    guint i;
    SFNumber *sn;

    numbers = g_array_sized_new(FALSE, FALSE, sizeof(SFNumber *), data->len);
    for (i = 0; i < data->len; i++){
        sn = sf_number_from_string((guchar *) g_array_index(data, char *, i));
        g_array_append_val(numbers, sn);
    }

    return numbers;
}

int solve_part_1(GArray *data) {
    guint i;
    SFNumber *sn;

    sn = g_array_index(data, SFNumber *, 0);
    for (i = 1; i < data->len; i++) {
        sn = sf_number_add(sn, g_array_index(data, SFNumber *, i));
        sn = sf_number_reduce(sn);
    }
    return sf_number_magnitude(sn);
}

int solve_part_2(GArray *data) {
    gint mag_max = 0;
    gint mag;
    SFNumber *sn;

    guint i, j;

    for (i = 0; i < data->len; i++) {
        for (j = i + 1; j < data->len; j++) {
            sn = sf_number_add(g_array_index(data, SFNumber *, i),
                               g_array_index(data, SFNumber *, j));
            sn = sf_number_reduce(sn);
            mag = sf_number_magnitude(sn);
            mag_max = MAX(mag, mag_max);
            sn = sf_number_add(g_array_index(data, SFNumber *, j),
                               g_array_index(data, SFNumber *, i));
            sn = sf_number_reduce(sn);
            mag = sf_number_magnitude(sn);
            mag_max = MAX(mag, mag_max);
        }
    }
    return mag_max;
}

int main(int argc, char **argv) {
    GArray *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = clean_data(get_input(filename, 2021, 18));

    if (data) {
        TIMER_INT(1, solve_part_1(data));
        TIMER_INT(2, solve_part_2(data));

        g_array_free(data, TRUE);
    }
    g_free(filename);
}


