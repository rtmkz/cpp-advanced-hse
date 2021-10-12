#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

template <class F, class... Args>
using TransformResult = bool;  /// 1

template <class F, class... Types>
concept invocable_on_all_types = true;  /// 2

template <class F, class... Args>
constexpr TransformResult<F, Args...> TransformTuple(
    F&& functor, const std::tuple<Args...>& args) requires invocable_on_all_types<F, Args...> {
    return {};  /// 3
}

template <class F, class... Args>
constexpr auto TransformReduceTuple(
    F&& functor, const std::tuple<Args...>& args) requires invocable_on_all_types<F, Args...> {
    return {};  /// 4
}
