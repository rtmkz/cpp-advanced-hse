add_gtest(test_call_private test_call_private.cpp)
add_gtest(test_polymorphism test_polymorphism.cpp)

target_compile_options(test_polymorphism PRIVATE -O0 -Wno-delete-non-abstract-non-virtual-dtor -fno-sanitize=vptr)
set_tests_properties(test_polymorphism PROPERTIES ENVIRONMENT LSAN_OPTIONS=detect_leaks=0)
