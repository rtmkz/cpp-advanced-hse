add_library(decoder_progressive

        # maybe your files here

        huffman.cpp
        fft.cpp
        decoder.cpp)

link_decoder_deps(decoder_progressive)
target_link_libraries(test_progressive decoder_progressive)
target_include_directories(test_progressive PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
