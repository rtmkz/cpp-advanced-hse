#pragma once

#include <limits>
#include <utility>
#include "impl.h"

/// Return a Tape with h appended to Tape.
template <char h, class Tape>
using Produce = void;

/// Return a pair type (Char<c>, Tape) with first (leftmost) char popped from Tape.
/// If Tape was empty, return Error.
template <class Tape>
using Consume = void;

/// Return Tape with incremented pos.
/// If pos falls out of bounds, return Error.
template <class Tape>
using IncrementPos = void;

/// Return Tape with decremented pos.
/// Is pos falls out of bounds, return Error.
template <class Tape>
using DecrementPos = void;

/// Return Tape with pos'th char incremented.
/// If pos'th char would overflow, return Error.
/// Keep in mind that "char" needn't be signed on all platforms.
template <class Tape>
using IncrementCell = void;

/// Return Tape with pos'th char decremented.
/// If pos'th char would underflow, return Error.
template <class Tape>
using DecrementCell = void;
