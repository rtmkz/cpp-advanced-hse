#include <catch.hpp>
#include <type_traits>
#include "curry.h"

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

    auto sum = []<class ...Ints>(Ints ...ints) { return (ints + ...); };

    REQUIRE(Uncurry(sum)(std::make_tuple(1, 2, 3, 4, 5, 6)) == sum(1, 2, 3, 4, 5, 6));
}
