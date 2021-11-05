#include "simple_defer.h"

#include <catch.hpp>

TEST_CASE("Basic") {
    int set_value1 = 12;
    int checker_num1 = 0;

    {
        defer {
            checker_num1 = set_value1;
        };
        ++set_value1;
        REQUIRE(checker_num1 == 0);
    }

    REQUIRE(checker_num1 == 13);

    int set_value2 = 12;
    int checker_num2 = 0;
    {
        defer {
            checker_num2 = set_value2;
        };
        defer {
            checker_num2 *= 2;
        };
        REQUIRE(checker_num2 == 0);
    }
    REQUIRE(checker_num2 == 12);

    int set_value3 = 12;
    int checker_num3 = 0;
    {
        defer {
            checker_num3 *= 2;
        };
        defer {
            checker_num3 = set_value3;
        };
        REQUIRE(checker_num3 == 0);
    }
    REQUIRE(checker_num3 == 24);
}

TEST_CASE("Nested") {
    int x = 0;

    {
        defer {
            defer {
                x += 10;
            };
            defer {
                x *= 2;
            };
        };

        ++x;
        REQUIRE(x == 1);
    }

    REQUIRE(x == 12);
}

constexpr int Foo(int x) {
    defer {
        x *= 2;
    };
    return x;
}

TEST_CASE("Constexpr") {
    constexpr int kX = 1;
    constexpr int kRes = Foo(kX);  // NOLINT
    REQUIRE(kRes == 1);
}

TEST_CASE("Multiline nested") {
    int x = 0;

    {
        // clang-format off
        defer { defer { x += 10; }; };
        // clang-format on

        ++x;
        REQUIRE(x == 1);
    }

    REQUIRE(x == 11);
}
