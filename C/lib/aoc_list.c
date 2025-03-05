#include "aoc_list.h"
#include "aoc_types.h"
#include <stdlib.h>

AocSList *aoc_slist_append(AocSList *list, void *data) {
    AocSList *new_list = (AocSList *)malloc(sizeof(AocSList));
    new_list->next = NULL;
    new_list->data = data;

    if (list) {
        while (list->next) {
            list = list->next;
        }
        list->next = new_list;
        return list;
    }

    return new_list;
}

AocSList *aoc_slist_prepend(AocSList *list, void *data) {
    AocSList *new_list = (AocSList *)malloc(sizeof(AocSList));

    new_list->next = list;
    new_list->data = data;

    return new_list;
}

AocSList *aoc_slist_reverse(AocSList *list) {
    AocSList *prev = NULL;
    while (list) {
        AocSList *next = list->next;
        list->next = prev;

        prev = list;
        list = next;
    }

    return prev;
}
