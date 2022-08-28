add_library(scheme_basic tokenizer.cpp parser.cpp scheme.cpp)
target_include_directories(scheme_basic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_scheme_basic scheme_basic)

add_executable(scheme_basic_repl repl/main.cpp)
target_link_libraries(scheme_basic_repl scheme_basic)
