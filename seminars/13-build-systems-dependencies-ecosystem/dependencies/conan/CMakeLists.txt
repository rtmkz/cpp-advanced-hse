cmake_minimum_required(VERSION 3.18)

project(woodpecker)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(example example.cpp)
target_link_libraries(example ${CONAN_LIBS})
