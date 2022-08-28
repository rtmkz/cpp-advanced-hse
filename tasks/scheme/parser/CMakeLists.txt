add_library(scheme_parser tokenizer.cpp parser.cpp)
target_include_directories(scheme_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_scheme_parser scheme_parser)
