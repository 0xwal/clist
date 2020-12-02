

#include <catch2/catch.hpp>
#include <clist.h>

size_t callCount = 0;
int arguments[8][8];
char* space[128];

TEST_CASE("clist")
{
    SECTION("create")
    {
        clist_s* list = clist_create(5);

        SECTION("return NULL when first allocator returns < 1")
        {
            clist_allocator_register([](size_t size) -> void* {
                return nullptr;
            });
            clist_s* clist = clist_create(20);
            REQUIRE(clist == nullptr);
            clist_allocator_restore();
        }

        SECTION("return NULL when second allocator returns < 1 and free first one")
        {
            //TODO: first should be freed
            callCount = 0;
            clist_allocator_register([](size_t size) -> void* {
                if (callCount++ == 0)
                {
                    return reinterpret_cast<void*>(space);
                }
                return nullptr;
            });
            clist_s* clist = clist_create(20);
            REQUIRE(clist == nullptr);
            clist_allocator_restore();
        }

        SECTION("should call allocator twice with valid arguments")
        {
            callCount = 0;
            clist_allocator_register([](size_t size) -> void* {
                arguments[callCount++][0] = size;
                return malloc(size);
            });

            clist_s* clist = clist_create(1);
            REQUIRE(callCount == 2);
            REQUIRE(arguments[0][0] == sizeof(clist_s));
            REQUIRE(arguments[1][0] == (sizeof(void*) * 2));
            clist_destroy(&clist);
        }

        SECTION("capacity should be multiplied by 2")
        {
            REQUIRE(list->capacity == 10);
        }

        SECTION("size should be 0")
        {
            REQUIRE(list->size == 0);
        }

        SECTION("data should be zero")
        {
            REQUIRE(list->values[0] == 0);
            REQUIRE(list->values[1] == 0);
            REQUIRE(list->values[2] == 0);
            REQUIRE(list->values[3] == 0);
            REQUIRE(list->values[4] == 0);
        }

        clist_destroy(&list);
        clist_allocator_restore();
    }

    SECTION("register allocator")
    {
        SECTION("providing a custom allocator")
        {
            allocator_t allocator = [](size_t size) -> void* {
                return reinterpret_cast<void*>(0x66);
            };

            clist_allocator_register(allocator);
            auto alloc = clist_allocator_current();
            REQUIRE(alloc == allocator);
            REQUIRE(alloc(16) == reinterpret_cast<void*>(0x66));
        }

        SECTION("reset allocator to default")
        {
            clist_allocator_register(reinterpret_cast<allocator_t>(0x20));
            REQUIRE(clist_allocator_current() == reinterpret_cast<allocator_t>(0x20));
            clist_allocator_restore();
            REQUIRE(clist_allocator_current() == &clist_allocator_default);
        }

        SECTION("allocator should point to default allocator")
        {
            auto alloc = clist_allocator_current();
            REQUIRE(alloc == &clist_allocator_default);
        }
        clist_allocator_restore();
    }

    SECTION("capacity")
    {
        clist_s* list = clist_create(1);
        SECTION("capacity will be doubled when we add more than the current capacity")
        {
            REQUIRE(list->capacity == 2);
            int value = 2;
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            REQUIRE(list->capacity == 10);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            REQUIRE(list->capacity == 18);
        }
        clist_destroy(&list);
    }

    SECTION("add")
    {
        clist_s* list = clist_create(2);

        SECTION("the used should be incremented by 1 when add a new element")
        {
            int value = 5;
            clist_add(list, &value);
            REQUIRE(list->size == 1);
            clist_add(list, &value);
            REQUIRE(list->size == 2);
        }

        SECTION("able to insert less than the size")
        {
            int values[] = { 5, 6 };
            clist_add(list, &values[0]);
            clist_add(list, &values[1]);
            REQUIRE(*reinterpret_cast<int*>(list->values[0]) == 5);
            REQUIRE(*reinterpret_cast<int*>(list->values[1]) == 6);
        }

        SECTION("able to insert and size will be increased dynamically")
        {
            int value = 5;
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);
            clist_add(list, &value);

            REQUIRE(*reinterpret_cast<int*>(list->values[0]) == 5);
            REQUIRE(*reinterpret_cast<int*>(list->values[1]) == 5);
            REQUIRE(*reinterpret_cast<int*>(list->values[2]) == 5);
            REQUIRE(*reinterpret_cast<int*>(list->values[3]) == 5);
            REQUIRE(*reinterpret_cast<int*>(list->values[4]) == 5);

            REQUIRE(list->size == 5);
        }

        clist_destroy(&list);
    }

    SECTION("find")
    {
        clist_s* list = clist_create(2);
        int values[] = { 2, 4, 6 };

        clist_add(list, &values[0]);
        clist_add(list, &values[1]);
        clist_add(list, &values[2]);

        SECTION("return index of existent value")
        {
            int index = clist_find(list, [](void* value) -> bool {
                return *reinterpret_cast<int*>(value) == 4;
            });

            REQUIRE(index == 1);
        }

        SECTION("return -1 for value that not exist")
        {
            int index = clist_find(list, [](void* value) -> bool {
                return *reinterpret_cast<int*>(value) == 100;
            });

            REQUIRE(index == -1);
        }

        clist_destroy(&list);
    }

    SECTION("clear")
    {
        clist_s* list = clist_create(2);
        int value = 5;
        clist_add(list, &value);
        clist_add(list, &value);
        clist_add(list, &value);

        SECTION("size should be 0")
        {
            clist_clear(list);
            REQUIRE(list->size == 0);
        }

        SECTION("all values should be nullptr")
        {
            clist_clear(list);
            REQUIRE(list->values[0] == nullptr);
            REQUIRE(list->values[1] == nullptr);
            REQUIRE(list->values[2] == nullptr);
        }

        clist_destroy(&list);
    }

    SECTION("destroy")
    {

        SECTION("size should be zero the list pointer")
        {
            clist_s* list = clist_create(2);
            int value = 5;
            clist_add(list, &value);

            clist_destroy(&list);
            REQUIRE(list == nullptr);
        }

        SECTION("fields should be set to 0")
        {
            clist_s* list = clist_create(2);
            int value = 5;
            clist_add(list, &value);

            clist_s* anotherPossiblePointerToSameList = list;
            clist_destroy(&list);
            REQUIRE(anotherPossiblePointerToSameList->size == 0);
            REQUIRE(anotherPossiblePointerToSameList->capacity == 0);
            REQUIRE(anotherPossiblePointerToSameList->values == NULL);
        }
    }
}
