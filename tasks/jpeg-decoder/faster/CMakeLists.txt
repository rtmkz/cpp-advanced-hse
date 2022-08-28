add_library(decoder_faster

        # maybe your files here

        huffman.cpp
        fft.cpp
        decoder.cpp)

link_decoder_deps(decoder_faster)
target_link_libraries(test_faster decoder_faster)
target_include_directories(test_faster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
