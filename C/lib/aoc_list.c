#include <stdlib.h>
#include "aoc_types.h"
#include "aoc_list.h"

AocSList *aoc_slist_prepend(AocSList *list, void *data) {
    AocSList *new_list = malloc(sizeof(AocSList));

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