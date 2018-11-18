cmake_minimum_required(VERSION 3.8)

set(HEADERS
    graph_lib.h
    graph.h
    )

set(SOURCES 
    graph.cpp
    )

add_library(graph_lib SHARED ${HEADERS} ${SOURCES})