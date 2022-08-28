add_library(scheme_advanced tokenizer.cpp parser.cpp scheme.cpp)
target_link_libraries(test_scheme_advanced scheme_advanced)

add_executable(scheme_advanced_repl repl/main.cpp)
target_link_libraries(scheme_advanced_repl scheme_advanced)
