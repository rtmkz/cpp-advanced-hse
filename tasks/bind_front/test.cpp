#include <catch.hpp>
#include <type_traits>
#include "bind_front.h"

TEST_CASE("Simple") {
    auto f = [](int, char c) { return c; };
    REQUIRE(BindFront(f, 0)('a') == 'a');

    const auto f_const = [](int, char c) { return c; };
    REQUIRE(BindFront(f_const, 0)('a') == 'a');

    auto f_move = [](int, char c) { return c; };
    REQUIRE(BindFront(std::move(f_move), 0)('a') == 'a');
}

TEST_CASE("Fix all arguments") {
    auto f = [](bool, const std::string& target) { return target; };
    REQUIRE(BindFront(f, false, "hello world")() == "hello world");
}

TEST_CASE("Check for forwarding") {
    struct Foo {};

    auto f = [](bool, Foo &&) {};

    Foo foo;
    BindFront(f, false)(std::move(foo));
}

TEST_CASE("No arguments") {
    auto f = [](bool, char) { return 0; };
    REQUIRE(BindFront(f, true, 1)() == 0);

    auto g = []() { return false; };
    REQUIRE(BindFront(g)() == false);
}

TEST_CASE("Func as arg") {
    auto f = [](auto&& f, char c) { return f(c); };
    auto g = [](char c) { return c; };

    REQUIRE(BindFront(f, g)('a') == 'a');
    REQUIRE(BindFront(f, g, 'a')() == 'a');
}

TEST_CASE("Variadic") {
    auto f = []<class A1, class... A>(A1 && a1, A && ...) {
        return a1;
    };

    REQUIRE(BindFront(f, false, 0, "hello world", 1337)("hello", true, 0.0f) == false);
    REQUIRE(BindFront(f, 84, 0, "hello world", 1337)("hello", true, 0.0f) == 84);
}
