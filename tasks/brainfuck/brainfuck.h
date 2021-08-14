#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

template<char...>
struct Str {};

#define compile_string(str) \
    []<size_t ...Is>  \
    (std::index_sequence<Is...>) { \
        return Str<str[Is]...>{}; \
    } (std::make_index_sequence<sizeof(str) - 1>{})

using InitialTape = Str<'0', '0'>;

template <size_t pos, char ...chars> struct Tape {};
template<class InputStr, class OutputStr, class Tape> struct State { };

template <class Tape> using IncrementPos = Tape;
template <class Tape> using DecrementPos = Tape;
template <class Tape> using IncrementCell = Tape;
template <class Tape> using DecrementCell = Tape;
template <class InputStr> using Consume = std::pair<char, InputStr>;
template <char c, class OutputStr> using Produce = OutputStr;

void foo(std::string_view exp, std::string_view input) {
    char array[30000] = {0};
    char *ptr = array;
    auto in = input.begin();

    for (auto token : exp) {
        if (token == '>') ++ptr;
        else if (token == '<') --ptr;
        else if (token == '+') ++*ptr;
        else if (token == '-') --*ptr;
        else if (token == '.') *ptr = *in++;
        else if (token == ',') *ptr = *in++;
    }
}

template <char ... chars> void Extract(Str<chars...>&);

template <class Input, class TapeStr>
struct Eval {
    using Cmd = 
    using Res = Input;
};
