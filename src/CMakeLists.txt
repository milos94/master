cmake_minimum_required(VERSION 3.8)

project(Master)

set(PROJECT_NAME Master)

#Set the correct version of c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Set correct flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-03")

set(PRIVATE_LIBRARIES 
    matrix_lib)

set(PUBLIC_LIBRARIES
    )

include_directories(matrix_lib)

set(HEADERS
    )

set(SOURCES 
    main.cpp
    )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
                      ${PRIVATE_LIBRARIES}
                      ${PUBLIC_LIBRARIES})