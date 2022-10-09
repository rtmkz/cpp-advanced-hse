set(PARSER_TESTS
    # from tokenizer
    tests/test_tokenizer.cpp

    tests/test_parser.cpp
    tests/test_fuzzing_1.cpp)

add_catch(test_scheme_parser
    ${PARSER_TESTS})

add_library(scheme_parser
    tokenizer.cpp
    parser.cpp)

target_include_directories(scheme_parser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SCHEME_COMMON_DIR})

target_link_libraries(test_scheme_parser scheme_parser)
