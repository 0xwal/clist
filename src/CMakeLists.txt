
set(CMAKE_C_STANDARD 11)


add_library(${PROJECT_NAME} clist.c clist.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)
