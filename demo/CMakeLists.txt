project(${PROJECT_NAME}_demo C)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})


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
