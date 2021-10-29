#include <catch.hpp>
#include <cstring>
#include "pipes.h"

TEST_CASE("Simple pipeline") {
    auto f = [](int a) { return a + 2; };
    auto g = [](int a) { return std::make_pair(a, a > 3); };
    auto pipe = kEmptyPl | f | g;

    REQUIRE(pipe(0) == std::make_pair(2, false));
    REQUIRE(pipe(2) == std::make_pair(4, true));
}

TEST_CASE("Inline pipeline") {
    auto pipeline = kEmptyPl | [](bool should_pass) {
        return std::make_tuple(should_pass, "hello world", nullptr);
    } | [](const auto& t) {
        return std::get<0>(t) ? std::get<1>(t) : std::get<2>(t);
    } | [](const char* ptr) { return ptr ? strlen(ptr) : 0; };

    REQUIRE(pipeline(true) == 11);
    REQUIRE(pipeline(false) == 0);
}
