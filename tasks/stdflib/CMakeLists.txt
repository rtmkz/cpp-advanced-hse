add_catch(test_stdflib test.cpp stdflib.h)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(test_stdflib PRIVATE "-fconstexpr-steps=2271242")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(test_stdflib PRIVATE "-fconstexpr-depth=2024")
endif()
