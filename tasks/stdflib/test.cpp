#include <catch.hpp>

#include "stdflib.h"

TEST_CASE("Fib") {
    REQUIRE(Fib<0>()() == 0);
    REQUIRE(Fib<1>()() == 1);
    REQUIRE(Fib<2>()() == 1);
    REQUIRE(Fib<9>()() == 34);

    // Using higher values would produce "constexpr evaluation hit maximum step limit; possible infinite loop"
    // To solve the issue one could use explicit memoization with templated variables.
    constexpr auto res = Fib<25>()();
    REQUIRE(res == 75025);
}

TEST_CASE("Fact") {
    REQUIRE(Fact<0>()() == 1);
    REQUIRE(Fact<1>()() == 1);
    REQUIRE(Fact<2>()() == 2);
    REQUIRE(Fact<3>()() == 6);
    REQUIRE(Fact<4>()() == 24);

    constexpr auto res = Fact<15>()();
    REQUIRE(res == 1307674368000);
}

TEST_CASE("GCD") {
    REQUIRE(GCD<0, 0>()() == 0);
    REQUIRE(GCD<1, 1>()() == 1);
    REQUIRE(GCD<5, 1>()() == 1);
    REQUIRE(GCD<10, 5>()() == 5);
    REQUIRE(GCD<1000, 251>()() == 1);
    REQUIRE(GCD<1000, 3>()() == 1);

    REQUIRE(GCD<1, 5>()() == 1);
    REQUIRE(GCD<250, 1000>()() == 250);

    constexpr auto res = GCD<91231232, 12938710>()();
    REQUIRE(res == 2);
}

TEST_CASE("Prime") {
    REQUIRE(Prime<0>()() == false);
    REQUIRE(Prime<1>()() == false);
    REQUIRE(Prime<2>()() == true);
    REQUIRE(Prime<3>()() == true);
    REQUIRE(Prime<4>()() == false);

    constexpr auto res = Prime<104729>()();
    REQUIRE(res == true);
}


