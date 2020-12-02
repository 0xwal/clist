#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 8

typedef bool(* predicate_t)(void* value);

typedef void* (* allocator_t)(size_t size);

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


void clist_allocator_register(allocator_t allocator);

allocator_t clist_allocator_current();

void clist_allocator_restore();

void* clist_allocator_default(size_t size);


void clist_add(clist_s* clist, void* element);

int clist_find(clist_s* clist, predicate_t predicate);

void clist_clear(clist_s* clist);

void clist_destroy(clist_s** clist);



#ifdef __cplusplus
}
#endif


#endif //CLIST_H
