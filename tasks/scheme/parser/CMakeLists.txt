add_library(scheme_parser tokenizer.cpp parser.cpp)
target_link_libraries(test_scheme_parser scheme_parser)
