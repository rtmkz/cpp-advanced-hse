#include <catch.hpp>
#include <chrono>

#include "../utils/test_commons.hpp"

TEST_CASE("huge", "[jpg]") {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    CheckImage("huge.jpg");
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    REQUIRE(std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() < 30);
}
