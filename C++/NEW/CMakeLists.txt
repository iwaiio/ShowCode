cmake_minimum_required(VERSION 3.28.0)
project(PROG1 VERSION 0.0.1)

set(SRC_
    prog.cpp
)

set(LIB_
    prog.h
)

#include_directories("")

add_executable(${PROJECT_NAME} ${SRC_} ${LIB_})