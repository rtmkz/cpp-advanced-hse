file(GLOB SOURCES "*.cpp")
add_library(libscheme ${SOURCES})

set(TOKENIZER_TESTS
        tokenizer/test.cpp)

set(PARSER_TESTS
        parser/test.cpp)

set(BASIC_TESTS
        basic/test_boolean.cpp
        basic/test_eval.cpp
        basic/test_integer.cpp
        basic/test_list.cpp)

set(ADVANCED_TESTS
        advanced/test_symbol.cpp
        advanced/test_define.cpp
        advanced/test_control_flow.cpp
        advanced/test_lambda.cpp)

set(TEST_ENV
        test/scheme_test.cpp)

add_catch(test_scheme_tokenizer
        ${TOKENIZER_TESTS}
        ${SOURCES})

add_catch(test_scheme_parser
        ${TOKENIZER_TESTS}
        ${PARSER_TESTS}
        ${SOURCES})

add_catch(test_scheme_basic
        ${TOKENIZER_TESTS}
        ${PARSER_TESTS}
        ${BASIC_TESTS}
        ${TEST_ENV})

target_link_libraries(test_scheme_basic libscheme)

add_catch(test_scheme_advanced
        ${BASIC_TESTS}
        ${ADVANCED_TESTS}
        ${TEST_ENV})

target_link_libraries(test_scheme_advanced libscheme)

add_executable(scheme-repl repl/main.cpp)
target_link_libraries(scheme-repl libscheme)

