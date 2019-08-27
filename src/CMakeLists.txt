cmake_minimum_required(VERSION 3.12)

project(Master)

set(PROJECT_NAME Master)

set(DEFAULT_BUILD_TYPE "Release")

#Set export compile commands on so that VSCode can use JASON file for intellisence
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Set the correct version of c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Set correct flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast \
                     -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic \
                     -Wconversion -Wsign-conversion -Wnull-dereference \
                     -Wdouble-promotion -Wformat=2 -Wduplicated-cond \
                     -Wduplicated-branches -Wlogical-op -Wuseless-cast -Wattributes \
                     -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-02")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(graph_lib)

set(LIBS 
    graphlib
    )

set(HEADERS
    )

set(SOURCES 
    main.cpp
    )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
                      ${LIBS})