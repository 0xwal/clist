#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

#define BLOCK_SIZE 8

typedef struct clist clist_s;
struct clist
{
    size_t size;
    size_t capacity;
    void** values;
};

#ifdef __cplusplus
extern "C" {
#endif

clist_s* clist_create(size_t capacity);

void clist_add(clist_s* clist, void* element);

void clist_clear(clist_s* clist);

void clist_destroy(clist_s** clist);

#ifdef __cplusplus
}
#endif


#endif //CLIST_H
