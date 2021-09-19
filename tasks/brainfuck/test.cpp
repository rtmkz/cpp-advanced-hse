#include <catch.hpp>
#include "brainfuck.h"

TEST_CASE("Consume") {
    REQUIRE(std::is_same_v<Str<'0', '0', '0'>::Consume,
                           decltype(std::pair{Char<'0'>{}, Str<'0', '0'>{}})>);
    REQUIRE(std::is_same_v<Str<'a'>::Consume, decltype(std::pair{Char<'a'>{}, Str<>{}})>);
}

TEST_CASE("Produce") {
    REQUIRE(std::is_same_v<Str<>::Produce<'a'>, Str<'a'>>);
    REQUIRE(std::is_same_v<Str<'a'>::Produce<'b'>, Str<'a', 'b'>>);
}

TEST_CASE("IncrementPos") {
    REQUIRE(std::is_same_v<Tape<0, '0', '0'>::IncrementPos, Tape<1, '0', '0'>>);
    REQUIRE(std::is_same_v<Tape<0, '0'>::IncrementPos, Tape<1, '0'>>);
}

TEST_CASE("DecrementPos") {
    REQUIRE(std::is_same_v<Tape<1, '0', '0'>::DecrementPos, Tape<0, '0', '0'>>);
    REQUIRE(std::is_same_v<Tape<1>::DecrementPos, Tape<0>>);
}

TEST_CASE("IncrementCell") {
    REQUIRE(std::is_same_v<Tape<1, '0', '0'>::IncrementCell, Tape<0, '0', '1'>>);
    REQUIRE(std::is_same_v<Tape<0, 'a', '0'>::IncrementCell, Tape<0, 'b', '1'>>);
}

TEST_CASE("DecrementCell") {
    REQUIRE(std::is_same_v<Tape<1, '0', '9'>::DecrementCell, Tape<1, '0', '8'>>);
    REQUIRE(std::is_same_v<Tape<0, 1>::DecrementCell, Tape<0, 0>>);
}
