#pragma once

#include <utility>

template <class F>
constexpr auto Curry(F&& f) {
    return f;  /// 1
}

template <class F>
constexpr auto Uncurry(F&& f) {
    return f;  /// 2
}
