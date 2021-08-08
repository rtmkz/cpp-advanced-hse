project(cpp-advanced-hse)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD             17)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

find_package(Catch REQUIRED)

include(cmake/TestSolution.cmake)
include(cmake/BuildFlags.cmake)
include_directories(util)

add_subdirectory(multiplication)
add_subdirectory(algo_spec_with_traits)
add_subdirectory(transform_tuple)
