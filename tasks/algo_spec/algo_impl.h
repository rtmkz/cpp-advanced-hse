#pragma once

#include <cstdint>

using AlgoRes = int;

struct Int128 {
    int64_t lo, hi;
};
struct Int256 {
    Int128 lo, hi;
};

AlgoRes ComputeUnsignedIntegral(auto) {
    return 1 << 3;
}
AlgoRes ComputeIntegral(auto) {
    return 1 << 2;
}
AlgoRes ComputeFloat(auto) {
    return 1 << 1;
}
AlgoRes ComputeGeneral(auto) {
    return 1 << 0;
}
