
set(CMAKE_C_STANDARD 11)

list(APPEND _SOURCES
     clist.h
     clist.c)


add_library(${PROJECT_NAME} ${_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)
