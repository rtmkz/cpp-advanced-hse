add_gtest(test_executors
  test_executors.cpp
  test_future.cpp
  SOLUTION_SRCS executors/executors.cpp)

add_benchmark(bench_executors
  run.cpp
  SOLUTION_SRCS executors/executors.cpp)