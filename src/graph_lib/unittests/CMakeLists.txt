set(BIN_NAME graph_lib_unittests)

set(HEADERS
    )

set(SOURCES graphtest.cpp)

set(LIBS 
    graphlib
    pthread
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${BIN_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${BIN_NAME}
                      ${GTEST_LIBRARIES}
                      ${LIBS}
                      )