
cmake_minimum_required(VERSION 3.10)
project(xrpc C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Find dependencies
find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gflags REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROTOBUF_INCLUDE_DIRS}
)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Library target
add_library(xrpc ${SOURCES})
target_link_libraries(xrpc
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROTOBUF_LIBRARIES}
    gflags
)

# Installation
install(TARGETS xrpc
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(FILES ${HEADERS}
    DESTINATION include/xrpc
)

# Build tests if enabled
if(BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Build examples if enabled
if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
