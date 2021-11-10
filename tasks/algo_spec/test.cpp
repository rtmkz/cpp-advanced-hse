#include <catch.hpp>
#include <cmath>

#include "algo_spec.h"

template <class T>
bool Check(T value, AlgoRes (*target)(T)) {
    return Run(value) == target(value);
}

TEST_CASE("Integral") {
    REQUIRE(Check(-200, ComputeIntegral));
    REQUIRE(Check(40, ComputeIntegral));
    REQUIRE(Check(0, ComputeIntegral));
    REQUIRE(Check(50ll, ComputeIntegral));
    REQUIRE(Check(50l, ComputeIntegral));
    REQUIRE(Check(static_cast<char>(2), ComputeIntegral));
    REQUIRE(Check(static_cast<short int>(2), ComputeIntegral));
}

TEST_CASE("Unsigned integral") {
    REQUIRE(Check(0u, ComputeUnsignedIntegral));
    REQUIRE(Check(50u, ComputeUnsignedIntegral));
    REQUIRE(Check(-1u, ComputeUnsignedIntegral));
    REQUIRE(Check(50ull, ComputeUnsignedIntegral));
    REQUIRE(Check(50ul, ComputeUnsignedIntegral));
    REQUIRE(Check(static_cast<unsigned char>(2), ComputeUnsignedIntegral));
    REQUIRE(Check(static_cast<unsigned short int>(2), ComputeUnsignedIntegral));
}

TEST_CASE("Floating point") {
    REQUIRE(Check(0.0f, ComputeFloat));
    REQUIRE(Check(-3.1415926, ComputeFloat));
    REQUIRE(Check(NAN, ComputeFloat));
    REQUIRE(Check(static_cast<double>(1.0), ComputeFloat));
    REQUIRE(Check(static_cast<long double>(1.0), ComputeFloat));
}

TEST_CASE("General algo") {
    REQUIRE(Check(Int128{25, 36}, ComputeGeneral));
    REQUIRE(Check(Int256{{1, 2}, {3, 4}}, ComputeGeneral));
}
