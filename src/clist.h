#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

typedef struct clist clist_s;
static const int BLOCK_SIZE = 8;
struct clist
{
    int size;
    size_t capacity;
    void** values;
};

#ifdef __cplusplus
extern "C" {
#endif

clist_s* clist_init(size_t capacity);

void clist_add(clist_s* clist, void* element);

void clist_free(clist_s** clist);

#ifdef __cplusplus
}
#endif


#endif //CLIST_H
