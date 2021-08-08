#include <catch.hpp>
#include <cstring>

#include "transform_tuple.h"

using namespace std::literals::string_literals;

TEST_CASE("Trait check") {
    auto f = [] (int) -> double { return {}; };
    REQUIRE(std::is_same_v<std::tuple<double>, TransformResult<decltype(f), int>>);
}

TEST_CASE("To integral") {
    auto functor = [] (auto num) { return int(num); };
    auto tuple = std::make_tuple(25, 30u, 0.12f);
    auto result = TransformTuple(functor, tuple);

    REQUIRE(std::is_same_v<decltype(result), std::tuple<int, int, int>>);
    REQUIRE(result == std::make_tuple(25, 30, 0));
}

TEST_CASE("Heterogeneous return types in functor") {
    auto functor = []<class T>(const T& item) { 
        if constexpr(std::is_same_v<T, std::string>)
            return item.size();
        else
            return int(strlen(item));
    };

    auto tuple = std::make_tuple("string literal", "string"s, "another literal");
    auto result = TransformTuple(functor, tuple);

    REQUIRE(std::is_same_v<decltype(result), std::tuple<int, size_t, int>>);
    REQUIRE(result == std::make_tuple(14, 6, 15));
}
