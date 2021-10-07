#include <catch.hpp>
#include <limits>
#include "brainfuck.h"

TEST_CASE("Consume") {
    REQUIRE(std::is_same_v<Consume<Tape<0, 0, 'a'>>, decltype(std::pair<Char<0>, Tape<0, 'a'>>{})>);
    REQUIRE(std::is_same_v<Consume<Tape<0, 'a'>>, decltype(std::pair<Char<'a'>, Tape<0>>{})>);
    REQUIRE(std::is_same_v<Consume<Tape<0>>, Error>);
}

TEST_CASE("Produce") {
    REQUIRE(std::is_same_v<Produce<'a', Tape<0>>, Tape<0, 'a'>>);
    REQUIRE(std::is_same_v<Produce<'a', Tape<0, 'b'>>, Tape<0, 'b', 'a'>>);
}

TEST_CASE("IncrementPos") {
    REQUIRE(std::is_same_v<IncrementPos<Tape<0, '0', '0'>>, Tape<1, '0', '0'>>);
    REQUIRE(std::is_same_v<IncrementPos<Tape<1, '0', '0'>>, Error>);
    REQUIRE(std::is_same_v<IncrementPos<Tape<0, '0'>>, Error>);
    REQUIRE(std::is_same_v<IncrementPos<Tape<0>>, Error>);
}

TEST_CASE("DecrementPos") {
    REQUIRE(std::is_same_v<DecrementPos<Tape<1, '0', '0'>>, Tape<0, '0', '0'>>);
    REQUIRE(std::is_same_v<DecrementPos<Tape<0, 'a', 'b'>>, Error>);
    REQUIRE(std::is_same_v<DecrementPos<Tape<0>>, Error>);
}

TEST_CASE("IncrementCell") {
    REQUIRE(std::is_same_v<IncrementCell<Tape<1, '0', '0'>>, Tape<1, '0', '1'>>);
    REQUIRE(std::is_same_v<IncrementCell<Tape<0, 'a', '0'>>, Tape<0, 'b', '0'>>);
    REQUIRE(std::is_same_v<IncrementCell<Tape<0, std::numeric_limits<char>::max()>>, Error>);
}

TEST_CASE("DecrementCell") {
    REQUIRE(std::is_same_v<DecrementCell<Tape<1, '0', '9'>>, Tape<1, '0', '8'>>);
    REQUIRE(std::is_same_v<DecrementCell<Tape<0, '\1'>>, Tape<0, '\0'>>);
    REQUIRE(std::is_same_v<DecrementCell<Tape<0, std::numeric_limits<char>::min()>>, Error>);
}
