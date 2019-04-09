cmake_minimum_required(VERSION 3.12)

set(HEADERS
    graph_lib_base.h
    graph.h
    )

set(SOURCES 
    graph.cpp
    )

add_library(graphlib ${HEADERS} ${SOURCES})

target_include_directories(graphlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})