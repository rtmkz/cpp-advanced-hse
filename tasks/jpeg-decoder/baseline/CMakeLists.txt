add_library(decoder_baseline

        # maybe your files here

        huffman.cpp
        fft.cpp
        decoder.cpp)

link_decoder_deps(decoder_baseline)
target_link_libraries(test_baseline decoder_baseline)
target_include_directories(test_baseline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
