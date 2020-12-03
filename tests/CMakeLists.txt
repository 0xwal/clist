
project(${PROJECT_NAME}_tests CXX)


Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME} main.cpp
               clist.test.cpp
               )

target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Catch2::Catch2)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_program(LEAKS_EXE "leaks")
    if (LEAKS_EXE)
        message(STATUS "found the required application " ${LEAKS_EXE})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                           COMMAND leaks -atExit -- ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} | grep leaks > memory-leaks.out
                           WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                           COMMENT "Running memory check"
                           )
    endif ()

endif ()
