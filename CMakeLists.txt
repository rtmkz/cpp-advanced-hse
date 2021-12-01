cmake_minimum_required(VERSION 3.13)

project(cpp-advanced-hse)

option(ENABLE_SEMINARS OFF)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/BuildFlags.cmake)
include(cmake/TestSolution.cmake)
include(cmake/SeminarUtils.cmake)

include(FetchContent)
include(cmake/FindGlog.cmake)

find_package(PNG)
find_package(JPEG)
find_package(FFTW)

find_package(Catch REQUIRED)
find_package(Benchmark REQUIRED)
find_package(GTest REQUIRED)

include_directories(util)

add_subdirectory(allocations_checker)

# 0
add_subdirectory(tasks/multiplication)

# 1
add_subdirectory(tasks/harakiri)
add_subdirectory(tasks/deque)
add_subdirectory(tasks/dedup)
add_subdirectory(tasks/cow-vector)

# 2
add_subdirectory(tasks/compressed_pair)
add_subdirectory(tasks/lru-cache)
add_subdirectory(tasks/string-operations)
add_subdirectory(tasks/intrusive-list)
add_subdirectory(tasks/list)
add_subdirectory(tasks/string-view)

# 3
add_subdirectory(tasks/bind_front)
add_subdirectory(tasks/curry)
add_subdirectory(tasks/stdflib)
add_subdirectory(tasks/dungeon)
add_subdirectory(tasks/fold)

# 5
add_subdirectory(tasks/grep)
add_subdirectory(tasks/safe-transform)
add_subdirectory(tasks/tryhard)
add_subdirectory(tasks/defer)

# 6
add_subdirectory(tasks/pimpl)
add_subdirectory(tasks/small-test-framework)
add_subdirectory(tasks/editor)
add_subdirectory(tasks/any)
add_subdirectory(tasks/scala-vector)

# 7
add_subdirectory(tasks/algo_spec)
add_subdirectory(tasks/transform_tuple)
#add_subdirectory(tasks/reflection)
add_subdirectory(tasks/constexpr-map)
add_subdirectory(tasks/pipes)
add_subdirectory(tasks/compile-eval)

# 8
add_subdirectory(tasks/is-prime)
add_subdirectory(tasks/reduce)
add_subdirectory(tasks/subset-sum)
add_subdirectory(tasks/hash-table)

# 9
add_subdirectory(tasks/timerqueue)
add_subdirectory(tasks/semaphore)
add_subdirectory(tasks/rw-lock)
add_subdirectory(tasks/buffered-channel)
add_subdirectory(tasks/unbuffered-channel)

# 10
add_subdirectory(tasks/futex)
add_subdirectory(tasks/mpsc-stack)
add_subdirectory(tasks/fast-queue)
add_subdirectory(tasks/rw-spinlock)

# 11
add_subdirectory(tasks/coroutine)
add_subdirectory(tasks/generator)

# Homeworks
# 1
add_subdirectory(tasks/smart-ptrs)
# 2
add_subdirectory(tasks/scheme)
# 3
add_subdirectory(tasks/jpeg-decoder)

# Bonuses
add_subdirectory(tasks/brainfuck)
add_subdirectory(tasks/solve_or_die)
add_subdirectory(tasks/matrix-2.0)
add_subdirectory(tasks/concepts)
add_subdirectory(tasks/simple_defer)
add_subdirectory(tasks/executors)

# ctf
add_subdirectory(tasks/gcd)
add_subdirectory(tasks/rule-of-5)
add_subdirectory(tasks/reallol)
add_subdirectory(tasks/bad-hash)

# Seminars
if (${ENABLE_SEMINARS})
  add_subdirectory(seminars)
endif()
