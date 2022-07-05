#include <catch.hpp>
#include <cstring>
#include "pipes.h"
#include "counted.h"

TEST_CASE("Empty") {
    const auto pl = Pipeline();
    CHECK(!std::is_invocable_v<decltype(pl)>);
    CHECK(!std::is_invocable_v<decltype(pl), int>);
}

int AddOne(int a) {
    return a + 1;
}

auto AddOneGeneric(auto a) {
    return a + 1;
}

TEST_CASE("Simple") {
    const auto stateless_lambda = [](int a) { return a + 1; };
    const auto moved_stateless_lambda = [](int a) { return a + 1; };

    int one = 1;
    const auto stateful_lambda = [&one](int a) { return a + one; };

    const auto curried_binary_lambda = std::bind_front(std::plus{}, 1);

    const auto pipe = Pipeline() | AddOne | stateless_lambda | std::move(moved_stateless_lambda) |
                      stateful_lambda | curried_binary_lambda | AddOneGeneric<int> |
                      [](int a) { return std::make_pair(a, a > 6); };

    CHECK(pipe(0) == std::make_pair(6, false));
    CHECK(pipe(1) == std::make_pair(7, true));
}

TEST_CASE("Inline composition") {
    const auto pipeline = Pipeline() | [](bool should_pass) {
        return std::make_tuple(should_pass, "hello world", nullptr);
    } | [](const auto& t) {
        return std::get<0>(t) ? std::get<1>(t) : std::get<2>(t);
    } | [](const char* t) { return t ? strlen(t) : 0; };

    CHECK(pipeline(true) == 11);
    CHECK(pipeline(false) == 0);
}

TEST_CASE("Composing pipelines") {
    const auto base = Pipeline() | AddOne | AddOne;
    auto pl1 = base | AddOne;
    auto pl2 = std::move(pl1) | AddOne;

    (pl2 | AddOne)(5);

    base(1);
    pl2(1);
}

TEST_CASE("Saving return value qualifiers") {
    std::string test = "hello";

    auto pipeline = Pipeline() | [&test](int) -> std::string& {
        return test;
    } | [](std::string& ref) -> std::string& { return ref; };

    pipeline(1)[0] = 'd';

    CHECK(test == "dello");
}
