#include "bind_front.h"

#include <catch.hpp>
#include <functional>
#include <memory>
#include <type_traits>

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

    auto f = [](Foo&&, Foo&&) {};

    BindFront(f, Foo())(Foo());

    auto g = [](const std::string&) {};
    std::string other;
    BindFront(g, other)();
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

struct Functor {
    int operator()(int x, int y) const {
        return x + y + val;
    }

    int val = 71;
};

TEST_CASE("LvalueReferences") {
    std::function<int(int)> func;
    {
        int scoped = 55;
        func = BindFront(Functor{}, scoped);
    }
    REQUIRE(func(3) == 129);
}

TEST_CASE("MoveOnlyParams") {
    auto ptr = std::make_unique<int>(5);
    auto f = [ptr = std::move(ptr)](std::unique_ptr<int> a, std::unique_ptr<int> b) mutable {
        *ptr = *a + *b;
        return ptr.release();
    };
    auto pa = std::make_unique<int>(13);
    auto pb = std::make_unique<int>(41);
    ptr.reset(BindFront(std::move(f), std::move(pa))(std::move(pb)));
    REQUIRE(*ptr == 54);
}

TEST_CASE("DoNotMoveFunctor") {
    std::function<int()> incrementer = [count = 0]() mutable { return ++count; };

    REQUIRE(BindFront(incrementer)() == 1);
    REQUIRE(BindFront(incrementer)() == 1);
}
