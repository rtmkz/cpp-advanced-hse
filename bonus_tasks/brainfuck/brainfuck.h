#pragma once

#include <tuple>
#include <utility>

template <char ...> struct Str {};
template <char c> struct Char {};

/// You can add template specializations if you want
template<>
struct Str</**/> {
    /// Return a Str with char appended to current Str end
    template <char h> using Produce = bool; ///1

    /// Return a pair type with a consumed Char and Str with left chars
    using Consume = bool; ///2
};

template <size_t pos, char ...chars>
struct Tape {
    using IncrementPos = bool; ///3
    using DecrementPos = bool; ///4

    /// Return a tape with pos'th char incremented
    using IncrementCell = bool; ///5

    /// Return a tape with pos'th char decremented
    using DecrementCell = bool; ///6
};


