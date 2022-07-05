#include <catch.hpp>
#include "pipes.h"
#include "counted.h"

TEST_CASE("lvalue handling with moves") {
    SECTION("rvalue base, lvalue next (first)") {
        Counted f;
        Info info = (Pipeline() | f | Id | Id | Id)(0);

        CHECK(info.copy == 1);  // first operator |
        CHECK(info.move == 3);  // rest operator |
    }

    SECTION("rvalue base, const lvalue next (first)") {
        const Counted f;
        Info info = (Pipeline() | f | Id | Id | Id)(0);

        CHECK(info.copy == 1);
        CHECK(info.move == 3);
    }

    SECTION("lvalue base, const lvalue next (first)") {
        const Counted f;
        auto pl = Pipeline();
        Info info = (pl | f | Id | Id | Id)(0);

        CHECK(info.copy == 1);
        CHECK(info.move == 3);
    }

    SECTION("rvalue base, const lvalue next (not first)") {
        const Counted f;
        Info info = (Pipeline() | [](int) { return 0; } | f | Id | Id | Id)(0);

        CHECK(info.copy == 1);
        CHECK(info.move == 3);
    }

    SECTION("lvalue base, const lvalue next (not first)") {
        const Counted f;
        auto pl2 = Pipeline();
        Info info2 = (pl2 | [](int) { return 0; } | f | Id | Id | Id)(0);

        CHECK(info2.copy == 1);
        CHECK(info2.move == 3);

        auto pl3 = Pipeline() | [](int) { return 0; };
        Info info3 = (pl3 | f | Id | Id | Id)(0);

        CHECK(info3.copy == 1);
        CHECK(info3.move == 3);
    }
}

TEST_CASE("rvalue handling with moves") {
    SECTION("rvalue base, rvalue next, invocation as lvalue") {
        auto pl = Pipeline() | Counted{} | Id;
        auto [copy, move, rvalue] = pl(0);

        CHECK(copy == 0);
        CHECK(move == 2);
        CHECK_FALSE(rvalue);
    }

    SECTION("rvalue base, rvalue next, invocation as rvalue") {
        auto pl = Pipeline() | Counted{} | Id;
        auto [copy, move, rvalue] = std::move(pl)(0);

        CHECK(copy == 0);
        CHECK(move == 2);
        CHECK(rvalue);
    }

    SECTION("lvalue base, rvalue next, invocation as lvalue") {
        auto base = Pipeline();
        auto pl = base | Counted{} | Id;
        auto [copy, move, rvalue] = pl(0);

        CHECK(copy == 0);
        CHECK(move == 2);
        CHECK_FALSE(rvalue);
    }

    SECTION("lvalue base, rvalue next, invocation as rvalue") {
        auto base = Pipeline();
        auto pl = base | Counted{} | Id;
        auto [copy, move, rvalue] = std::move(pl)(0);

        CHECK(copy == 0);
        CHECK(move == 2);
        CHECK(rvalue);
    }
}

TEST_CASE("Move only") {
    struct MoveOnly {
        MoveOnly() = default;
        MoveOnly(MoveOnly&&) = default;
        MoveOnly(const MoveOnly&) = delete;

        int operator()(int) && {
            return 0;
        }
    };

    (Pipeline() | MoveOnly{})(0);

    auto pl = Pipeline() | [](int) { return 0; };
    auto pl2 = pl | MoveOnly{};
    std::move(pl2)(0);
}
