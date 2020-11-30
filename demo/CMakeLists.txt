project(${PROJECT_NAME}_demo C)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
