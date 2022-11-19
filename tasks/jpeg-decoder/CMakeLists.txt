find_package(PNG)
find_package(JPEG)
find_package(FFTW)

add_catch(test_decoder_huffman 
    huffman/tests/test_huffman.cpp
    utils/logger_init.cpp
)

add_catch(test_decoder_fftw
    fftw/tests/test_fft.cpp
    utils/logger_init.cpp
)

add_catch(test_decoder_baseline
    huffman/tests/test_huffman.cpp
    fftw/tests/test_fft.cpp
    baseline/tests/test_baseline.cpp
    utils/logger_init.cpp
)

add_catch(test_decoder_faster
    huffman/tests/test_huffman.cpp
    fftw/tests/test_fft.cpp
    baseline/tests/test_baseline.cpp
    faster/tests/test_faster.cpp
    utils/logger_init.cpp
)

if (NOT TEST_SOLUTION)
    add_catch(test_decoder_progressive 
        huffman/tests/test_huffman.cpp
        fftw/tests/test_fft.cpp
        baseline/tests/test_baseline.cpp
        faster/tests/test_faster.cpp
        progressive/tests/test_progressive.cpp
        utils/logger_init.cpp
    )
endif ()

target_compile_definitions(test_decoder_baseline PUBLIC HSE_TASK_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
target_compile_definitions(test_decoder_faster PUBLIC HSE_TASK_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
if (NOT TEST_SOLUTION)
    target_compile_definitions(test_decoder_progressive PUBLIC HSE_TASK_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")
endif ()

if (GRADER)
    target_compile_definitions(test_decoder_baseline PUBLIC HSE_ARTIFACTS_DIR="/tmp/artifacts")
    if (NOT TEST_SOLUTION)
        target_compile_definitions(test_decoder_progressive PUBLIC HSE_ARTIFACTS_DIR="/tmp/artifacts")
    endif ()
endif ()

set(DECODER_UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils)
set(DECODER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(link_decoder_deps TARGET)
    target_include_directories(${TARGET} PUBLIC
            ${PNG_INCLUDE_DIRS}
            ${FFTW_INCLUDES}
            ${JPEG_INCLUDE_DIRS}
            ${DECODER_UTILS_DIR}
            ${DECODER_INCLUDE_DIR})

    target_link_libraries(${TARGET} PUBLIC
            ${FFTW_LIBRARIES}
            ${PNG_LIBRARY}
            ${JPEG_LIBRARIES}
            glog::glog)

    get_target_property(GLOG_INCLUDES glog::glog INCLUDE_DIRECTORIES)
    target_include_directories(${TARGET} SYSTEM PUBLIC ${GLOG_INCLUDES})

endfunction()

add_subdirectory(huffman)
add_subdirectory(fftw)
add_subdirectory(baseline)
add_subdirectory(faster)

if (NOT TEST_SOLUTION)
    add_subdirectory(progressive)
endif ()

# if (NOT CMAKE_CXX_COMPILER_ID MATCHES "^Clang$")
#     message(WARNING "Clang is required for fuzzing tests")
# else()
#     add_executable(fuzz_huffman huffman/fuzz_huffman.cpp)
#     add_executable(fuzz_fft fftw/fuzz_fft.cpp)
#     add_executable(fuzz_jpeg jpeg-fuzz/fuzz_jpeg.cpp)
#     set_property(TARGET fuzz_huffman APPEND PROPERTY COMPILE_OPTIONS "-fsanitize=fuzzer-no-link")
#     set_property(TARGET fuzz_fft APPEND PROPERTY COMPILE_OPTIONS "-fsanitize=fuzzer-no-link")
#     set_property(TARGET fuzz_jpeg APPEND PROPERTY COMPILE_OPTIONS "-fsanitize=fuzzer-no-link")
#     target_link_libraries(fuzz_huffman decoder "-fsanitize=fuzzer")
#     target_link_libraries(fuzz_fft decoder ${FFTW_LIBRARIES} "-fsanitize=fuzzer")
#     target_link_libraries(fuzz_jpeg decoder ${FFTW_LIBRARIES} "-fsanitize=fuzzer")
# endif ()
