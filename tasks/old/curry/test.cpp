#include "curry.h"

#include <catch.hpp>

#include <memory>

TEST_CASE("Curry") {
    auto f = [](const std::tuple<int, char>& t) { return std::get<0>(t); };
    REQUIRE(Curry(f)(89, 'a') == f({89, 'a'}));
    REQUIRE(Curry(f)(0, 'a') == f({0, 'a'}));

    auto sum = [](const std::tuple<int, int, int, int>& t) {
        return std::get<0>(t) + std::get<1>(t) + std::get<2>(t) + std::get<3>(t);
    };

    REQUIRE(Curry(sum)(1, 2, 3, 4) == sum({1, 2, 3, 4}));
}

TEST_CASE("Uncurry") {
    auto f = [](int, char c) { return c; };
    REQUIRE(Uncurry(f)(std::make_tuple(89, 'a')) == f(89, 'a'));
    REQUIRE(Uncurry(f)(std::make_tuple(0, 'a')) == f(0, 'a'));

    auto sum = []<class... Ints>(Ints... ints) {
        return (ints + ...);
    };

    REQUIRE(Uncurry(sum)(std::make_tuple(1, 2, 3, 4, 5, 6)) == sum(1, 2, 3, 4, 5, 6));
}

TEST_CASE("MoveOnlyAndMutableUncurry") {
    auto ptr = std::make_unique<int>(5);
    auto f = [ptr = std::move(ptr)](int x, int y) mutable {
        *ptr = x * y;
        return ptr.release();
    };
    ptr.reset(Uncurry(std::move(f))(std::make_tuple(2, 3)));
    REQUIRE(*ptr == 6);
}

TEST_CASE("MoveOnlyAndMutableCurry") {
    auto ptr = std::make_unique<int>(5);
    auto f = [ptr = std::move(ptr)](const std::tuple<int, int>& args) mutable {
        *ptr = std::get<0>(args) * std::get<1>(args);
        return ptr.release();
    };
    ptr.reset(Curry(std::move(f))(2, 3));
    REQUIRE(*ptr == 6);
}

struct Functor {
    int operator()(int x, int y) const {
        return x + y + val;
    }

    int operator()(const std::tuple<int, int>& args) const {
        return std::get<0>(args) + std::get<1>(args) + val;
    }

    int val = 7;
};

TEST_CASE("LvalueReferencesUncurry") {
    std::function<int(std::tuple<int, int>)> func;
    { func = Uncurry(Functor{}); }
    REQUIRE(func(std::make_tuple(2, 3)) == 12);
}

TEST_CASE("LvalueReferencesCurry") {
    std::function<int(int, int)> func;
    { func = Curry(Functor{}); }
    REQUIRE(func(2, 3) == 12);
}

TEST_CASE("MoveOnlyParamsUncurry") {
    auto f = [](const std::unique_ptr<int>& a, const std::unique_ptr<int>& b) { return *a + *b; };
    auto ptr1 = std::make_unique<int>(6);
    auto ptr2 = std::make_unique<int>(23);
    REQUIRE(Uncurry(f)(std::make_tuple(std::move(ptr1), std::move(ptr2))) == 29);
}

TEST_CASE("MoveOnlyParamsCurry") {
    auto f = [](const std::tuple<std::unique_ptr<int>, std::unique_ptr<int>>& args) {
        return *std::get<0>(args) + *std::get<1>(args);
    };
    auto ptr1 = std::make_unique<int>(6);
    auto ptr2 = std::make_unique<int>(23);
    REQUIRE(Curry(f)(std::move(ptr1), std::move(ptr2)) == 29);
}
