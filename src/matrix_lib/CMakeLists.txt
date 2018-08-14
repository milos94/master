cmake_minimum_required(VERSION 3.8)

set(HEADRES
    matrix.h)

set(SOURCES
    matrix.cpp)

add_library(matrix_lib SHARED IMPORTED ${HEADERS} ${SOURCES})