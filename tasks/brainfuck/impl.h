#pragma once

#include <cstddef>

template <char c>
struct Char {};
template <size_t pos, char... chars>
struct Tape {};
struct Error {};
