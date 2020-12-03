cmake_minimum_required(VERSION 3.17)

project(clist C)
find_program(LEAKS_EXE "leaks")

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(demo)
