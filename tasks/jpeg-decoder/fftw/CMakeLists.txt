add_library(decoder_fftw fft.cpp)

link_decoder_deps(decoder_fftw)
target_link_libraries(test_fft decoder_fftw)
