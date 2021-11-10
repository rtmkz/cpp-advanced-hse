string(RANDOM ALPHABET "abcdefghijklmnopqrstuvwxyz" HOHOHO)
configure_file(test.inc.in algo_spec_test.inc)

add_catch(test_algo_spec test.cpp algo_spec.h)
target_include_directories(test_algo_spec PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
