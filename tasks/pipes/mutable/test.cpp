#include <catch.hpp>
#include "pipes.h"
#include "counted.h"

TEST_CASE("mutable") {
    SECTION("encapsulated lambda arguments") {
        auto inc = [i = 0](int) mutable { return i++; };
        auto pl = Pipeline() | inc;

        CHECK(inc(0) == 0);
        CHECK(inc(0) == 1);
        CHECK(inc(0) == 2);

        CHECK(pl(0) == 0);
        CHECK(pl(0) == 1);
        CHECK(pl(0) == 2);
    }

    SECTION("explicit references in capture list") {
        int i = 0;
        auto inc = [&i](int) mutable { return i++; };
        auto pl = Pipeline() | inc;

        CHECK(inc(0) == 0);
        CHECK(inc(0) == 1);
        CHECK(inc(0) == 2);
        CHECK(i == 3);

        CHECK(pl(0) == 3);
        CHECK(pl(0) == 4);
        CHECK(pl(0) == 5);
        CHECK(i == 6);
    }

    SECTION("moving mutable lambda") {
        auto inc = [i = 0](int) mutable { return i++; };
        auto pl = Pipeline() | std::move(inc);

        CHECK(pl(0) == 0);
        CHECK(pl(0) == 1);
        CHECK(pl(0) == 2);
    }

    SECTION("multiple invocations") {
        auto inc = [i = 0](int) mutable { return i++; };
        auto pl = Pipeline() | inc | inc | inc | inc;

        CHECK(pl(0) == 0);
        CHECK(pl(0) == 1);
        CHECK(pl(0) == 2);
    }

    SECTION("multiple invocations, explicit references") {
        int i = 0;
        auto inc = [&i](int) mutable { return i++; };
        auto pl = Pipeline() | inc | inc | inc | inc;

        CHECK(pl(0) == 3);
        CHECK(pl(0) == 7);
        CHECK(pl(0) == 11);
    }

    SECTION("unexpected copy semantics") {
        int i = 0;
        auto inc = [&i](int) mutable { return i++; };

        auto pl = Pipeline() | inc;
        auto pl2 = pl | inc; // expected copying

        CHECK(pl(0) == 0);
        CHECK(pl2(0) == 2);
        CHECK(pl(0) == 3);
        CHECK(pl2(0) == 5);
    }
}
