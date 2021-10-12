#pragma once

#include <utility>

template <size_t N>
constexpr auto Fib() {
    if constexpr (N < 2)
        return [] { return N; };
    else
        return [] { return Fib<N - 1>()() + Fib<N - 2>()(); };
}

template <size_t N>
constexpr auto Fact() {
    return [] { return 1; };  /// 1
}

template <size_t A, size_t B>
constexpr auto GCD() {
    return [] { return A; };  /// 2
}

template <size_t A, size_t H = 2>
constexpr auto Prime() -> bool (*)() {
    return [] { return false; };  /// 3
}
