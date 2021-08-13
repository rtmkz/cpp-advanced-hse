project(cpp-advanced-hse)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

find_package(Catch REQUIRED)

include(cmake/TestSolution.cmake)
include(cmake/BuildFlags.cmake)
include_directories(util)

# 0
add_subdirectory(tasks/multiplication)

# 3
add_subdirectory(tasks/bind_front)
add_subdirectory(tasks/curry)
add_subdirectory(tasks/stdflib)

# 7
add_subdirectory(tasks/algo_spec)
add_subdirectory(tasks/transform_tuple)
add_subdirectory(tasks/reflection)
add_subdirectory(tasks/pipes)
#add_subdirectory(tasks/brainfuck)
