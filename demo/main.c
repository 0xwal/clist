

#include <clist.h>
#include <printf.h>


int main()
{
    clist_s* list = clist_create(16);

    clist_add(list, "Hello");
    clist_add(list, "World");
    clist_add(list, "clist");

    printf("%lu\n", list->size);

    for (int i = 0; i < list->size; ++i)
    {
        printf("%s ", (char*)list->values[i]);
    }

    clist_destroy(&list);

    return 0;
}
