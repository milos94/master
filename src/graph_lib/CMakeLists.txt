set(HEADERS
    graph_lib_base.hpp
    graph.hpp
    graph_algorithms.hpp
    )

set(SOURCES
    )

add_subdirectory(unittests)

add_library(graphlib ${HEADERS} ${SOURCES})

target_include_directories(graphlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(graphlib PROPERTIES LINKER_LANGUAGE CXX)
