add_library(decoder

        # maybe your files here

        huffman.cpp
        fft.cpp
        decoder.cpp)

target_include_directories(decoder PUBLIC
        ${PNG_INCLUDE_DIRS}
        ${FFTW_INCLUDES}
        ${JPEG_INCLUDE_DIRS})

target_link_libraries(decoder PUBLIC
        ${FFTW_LIBRARIES}
        ${PNG_LIBRARY}
        ${JPEG_LIBRARIES}
        glog::glog
        )

add_catch(test_huffman huffman/test_huffman.cpp)
add_catch(test_fft fftw/test_fft.cpp)
add_catch(test_baseline baseline/test_baseline.cpp)
if (NOT TEST_SOLUTION)
    add_catch(test_progressive progressive/test_progressive.cpp)
endif ()
add_catch(test_faster faster/test_faster.cpp)

target_compile_definitions(test_baseline PUBLIC HSE_TASK_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
target_compile_definitions(test_faster PUBLIC HSE_TASK_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
if (NOT TEST_SOLUTION)
    target_compile_definitions(test_progressive PUBLIC HSE_TASK_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
endif ()

if (GRADER)
    target_compile_definitions(test_baseline PUBLIC HSE_ARTIFACTS_DIR="/tmp/artifacts")
    target_compile_definitions(test_faster PUBLIC HSE_ARTIFACTS_DIR="/tmp/artifacts")
    if (NOT TEST_SOLUTION)
        target_compile_definitions(test_progressive PUBLIC HSE_ARTIFACTS_DIR="/tmp/artifacts")
    endif ()
endif ()

target_link_libraries(test_baseline decoder)
target_link_libraries(test_faster decoder)
if (NOT TEST_SOLUTION)
    target_link_libraries(test_progressive decoder)
endif ()
target_link_libraries(test_huffman decoder)
target_link_libraries(test_fft decoder)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_GCC 1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    set(COMPILER_CLANG 1) # Safe to treat AppleClang as a regular Clang, in general.
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(COMPILER_CLANG 1)
endif ()

if (COMPILER_GCC)
    message(WARNING "Fuzzing is not support with GCC backend")
endif ()

if (COMPILER_CLANG)
    add_executable(fuzz_huffman huffman/fuzz_huffman.cpp)
    add_executable(fuzz_fft fftw/fuzz_fft.cpp)
    add_executable(fuzz_jpeg jpeg-fuzz/fuzz_jpeg.cpp)
    set_property(TARGET fuzz_huffman APPEND PROPERTY COMPILE_OPTIONS "-fsanitize=fuzzer-no-link")
    set_property(TARGET fuzz_fft APPEND PROPERTY COMPILE_OPTIONS "-fsanitize=fuzzer-no-link")
    set_property(TARGET fuzz_jpeg APPEND PROPERTY COMPILE_OPTIONS "-fsanitize=fuzzer-no-link")
    target_link_libraries(fuzz_huffman decoder "-fsanitize=fuzzer")
    target_link_libraries(fuzz_fft decoder ${FFTW_LIBRARIES} "-fsanitize=fuzzer")
    target_link_libraries(fuzz_jpeg decoder ${FFTW_LIBRARIES} "-fsanitize=fuzzer")
endif ()
