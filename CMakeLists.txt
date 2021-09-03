project(cpp-advanced-hse)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/BuildFlags.cmake)
include(cmake/TestSolution.cmake)

find_package(Catch REQUIRED)

include_directories(util)

# 0
add_subdirectory(tasks/multiplication)
add_subdirectory(tasks/harakiri)
add_subdirectory(tasks/deque)
add_subdirectory(tasks/dedup)
add_subdirectory(tasks/cow-vector)

# 1
add_subdirectory(tasks/compressed_pair)

# 3
add_subdirectory(tasks/bind_front)
add_subdirectory(tasks/curry)
add_subdirectory(tasks/stdflib)

# 7
add_subdirectory(tasks/algo_spec)
add_subdirectory(tasks/transform_tuple)
add_subdirectory(tasks/reflection)
add_subdirectory(tasks/pipes)

# bonus
add_subdirectory(tasks/brainfuck)
