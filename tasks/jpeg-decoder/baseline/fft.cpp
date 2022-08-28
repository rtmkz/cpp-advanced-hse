#include "fft.h"

#include <fftw3.h>

DctCalculator::DctCalculator(size_t width, std::vector<double> *input,
                             std::vector<double> *output) {
    (void)width;
    (void)input;
    (void)output;
}

void DctCalculator::Inverse() {
}
