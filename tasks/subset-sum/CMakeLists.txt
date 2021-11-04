add_gtest(test_subset_sum test.cpp SOLUTION_SRCS find_subsets.cpp)
add_benchmark(bench_subset_sum run.cpp SOLUTION_SRCS find_subsets.cpp)
