#include "clist.h"


clist_s* clist_create(size_t capacity)
{
    clist_s* list = calloc(1, sizeof(clist_s));
    list->capacity = capacity * 2;
    list->values = calloc(list->capacity, sizeof(NULL));
    return list;
}

void clist_add(clist_s* clist, void* element)
{
    if (clist->size >= clist->capacity)
    {
        size_t newSize = clist->capacity + BLOCK_SIZE;
        clist->values = realloc(clist->values, sizeof(NULL) * newSize);
        clist->capacity = newSize;
    }
    clist->values[clist->size++] = element;
}

int clist_find(clist_s* clist, predicate_t predicate)
{
    for (int i = 0; i < clist->size; ++i)
    {
        if (predicate(clist->values[i]))
        {
            return i;
        }
    }
    return -1;
}

void clist_clear(clist_s* clist)
{
    for (int i = 0; i < clist->size; ++i)
    {
        clist->values[i] = NULL;
    }
    clist->size = 0;
}

void clist_destroy(clist_s** clist)
{
    clist_s* list = *clist;

    if (list == NULL)
    {
        return;
    }

    list->size = 0;
    list->capacity = 0;

    if (list->values != NULL)
    {
        free(list->values);
        list->values = NULL;
    }

    free(list);
    *clist = NULL;
}


