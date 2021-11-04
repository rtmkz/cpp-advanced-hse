add_gtest(test_isprime test.cpp SOLUTION_SRCS is_prime.cpp)

add_benchmark(bench_isprime run.cpp SOLUTION_SRCS is_prime.cpp)
