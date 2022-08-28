add_library(scheme_advanced tokenizer.cpp parser.cpp scheme.cpp)
target_include_directories(scheme_advanced PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_scheme_advanced scheme_advanced)

add_executable(scheme_advanced_repl repl/main.cpp)
target_link_libraries(scheme_advanced_repl scheme_advanced)
