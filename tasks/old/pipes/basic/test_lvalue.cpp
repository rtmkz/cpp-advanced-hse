#include <catch.hpp>
#include "counted.h"
#include "pipes.h"

TEST_CASE("lvalue handling without moves") {
    Counted f1;
    Info i1 = (Pipeline() | f1 | Id | Id | Id)(0);

    CHECK(i1.copy == 4);

    const Counted f2;
    Info i2 = (Pipeline() | f2 | Id | Id | Id)(0);

    CHECK(i2.copy == 4);

    const Counted f3;
    Info i3 = (Pipeline() | [](int) { return 0; } | f3 | Id | Id | Id)(0);

    CHECK(i3.copy == 4);
}
