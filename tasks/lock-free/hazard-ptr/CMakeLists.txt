add_library(libhazard_ptr hazard_ptr.cpp)

add_gtest(test_hazard_ptr 
    hazard_ptr_test.cpp)

target_link_libraries(test_hazard_ptr libhazard_ptr)

add_benchmark(bench_hazard_ptr
    hazard_ptr_bench.cpp)

target_link_libraries(bench_hazard_ptr libhazard_ptr)
