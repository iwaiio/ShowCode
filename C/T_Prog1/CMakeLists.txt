cmake_minimum_required(VERSION 3.28.0)
project(T_PROG_1 VERSION 0.0.1 LANGUAGES C)

set(LIB_
    LIB/head.h
)

set(SRC_
    SRC/main.c
)

include_directories("SRC/" "LIB/")

add_executable(${PROJECT_NAME} ${LIB_} ${SRC_})