

#include <catch2/catch.hpp>
#include <clist.h>

TEST_CASE("clist")
{
    SECTION("clist initialization")
    {
        clist_s* list = clist_init(5);

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

        clist_free(&list);
    }

    SECTION("clist capacity")
    {
        clist_s* list = clist_init(1);
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
        clist_free(&list);
    }

    SECTION("clist insertion")
    {
        clist_s* list = clist_init(2);

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

        clist_free(&list);
    }

    SECTION("clist destroy")
    {

        SECTION("size should be zero the list pointer")
        {
            clist_s* list = clist_init(2);
            int value = 5;
            clist_add(list, &value);

            clist_free(&list);
            REQUIRE(list == nullptr);
        }

        SECTION("fields should be set to 0")
        {
            clist_s* list = clist_init(2);
            int valaue = 5;
            clist_add(list, &valaue);

            clist_s* anotherPossiblePointerToSameList = list;
            clist_free(&list);
            REQUIRE(anotherPossiblePointerToSameList->size == 0);
            REQUIRE(anotherPossiblePointerToSameList->capacity == 0);
            REQUIRE(anotherPossiblePointerToSameList->values == NULL);
        }
    }
}
