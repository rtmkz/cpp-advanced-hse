file(GLOB SOURCES "*.cpp")
add_library(scheme ${SOURCES})

set(TOKENIZER_TESTS
        tokenizer/test.cpp)

set(PARSER_TESTS
        parser/test.cpp)

set(PARSER_FUZZING_TEST
        parser/fuzzing.cpp)

set(BASIC_TESTS
        basic/test_boolean.cpp
        basic/test_eval.cpp
        basic/test_integer.cpp
        basic/test_list.cpp
        basic/test_fuzzer.cpp)

set(ADVANCED_TESTS
        advanced/test_symbol.cpp
        advanced/test_pair_mut.cpp
        advanced/test_control_flow.cpp
        advanced/test_lambda.cpp)

set(TEST_ENV
        test/scheme_test.cpp)

add_catch(test_scheme_tokenizer
        ${TOKENIZER_TESTS})

target_link_libraries(test_scheme_tokenizer scheme)

add_catch(test_scheme_parser
        ${TOKENIZER_TESTS}
        ${PARSER_TESTS}
        ${PARSER_FUZZING_TEST})

target_link_libraries(test_scheme_parser scheme)

add_catch(test_scheme_basic
        ${TOKENIZER_TESTS}
        ${PARSER_TESTS}
        ${BASIC_TESTS}
        ${TEST_ENV})

target_link_libraries(test_scheme_basic scheme)

add_catch(test_scheme_advanced
        ${BASIC_TESTS}
        ${ADVANCED_TESTS}
        ${TEST_ENV})

target_link_libraries(test_scheme_advanced scheme)

add_executable(scheme-repl repl/main.cpp)
target_link_libraries(scheme-repl scheme)
