

#include <clist.h>
#include <stdio.h>
#include <string.h>

bool worldPredicate(void* value)
{
    return !strcmp(value, "World");
}

char g_memory_space[512];
size_t reserved = 0;

void* custom_allocator(size_t size)
{
    char* mem = g_memory_space + reserved;
    reserved += size;
    return mem;
}

int main()
{
    clist_allocator_register(custom_allocator);

    clist_s* list = clist_create(1);

    clist_add(list, "Hello");
    clist_add(list, "World");
    clist_add(list, "clist");

    int worldIndex = clist_find(list, worldPredicate);

    printf("World index: %d\n", worldIndex);

    printf("%lu\n", list->size);

    for (int i = 0; i < list->size; ++i)
    {
        printf("%s ", (char*)list->values[i]);
    }

//    clist_destroy(&list);

    return 0;
}
