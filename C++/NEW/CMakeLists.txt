cmake_minimum_required(VERSION 3.28.0)
project(PROG1 VERSION 0.1.0 LANGUAGES CPP)

set(FILES_LIST
    prog.cpp
    prog.h
)

#include_directories("")

add_executable(${PROJECT_NAME} ${FILES_LIST})