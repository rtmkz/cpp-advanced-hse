#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

template <class F, class ...Args>
using Res = std::invoke_result_t<F, Args...>;

template <class F, class ...Args>
using TransformResult = std::tuple<Res<F, Args>...>; // 1

template <class F, class ...Types>
concept invocable_on_all_types = (std::is_invocable_v<F, Types> && ...); //2

template <class F, class Tuple, std::size_t...I>
constexpr auto Transform(F && functor, const Tuple& args, std::index_sequence<I...>) {
    return std::make_tuple(std::forward<F>(functor)(std::get<I>(args))...);
}

template <class F, class ...Args>
constexpr TransformResult<F, Args...>
TransformTuple(F && functor, const std::tuple<Args...>& args)
    requires invocable_on_all_types<F, Args...> {
    // 3.
    return Transform(std::forward<F>(functor), args, std::make_index_sequence<sizeof...(Args)>{});
}

template <class F, class ...Args>
constexpr auto TransformReduceTuple(F && functor, const std::tuple<Args...>& args)
    requires invocable_on_all_types<F, Args...> {
    //4
    return TransformReduce(std::forward<F>(functor), args, std::make_index_sequence<sizeof...(Args)>{});
}

template <class F, class Tuple, std::size_t FirstI, std::size_t...I>
constexpr auto TransformReduce(F && functor, const Tuple& args, std::index_sequence<FirstI, I...>) {
    if constexpr(sizeof...(I) == 0)
        return std::make_tuple(std::forward<F>(functor)(std::get<FirstI>(args)));
    else if constexpr(std::is_void_v<Res<F, std::tuple_element_t<FirstI, Tuple>>>)
        return TransformReduce(std::forward<F>(functor), args, std::index_sequence<I...>{});
    else
        return std::tuple_cat(
            std::make_tuple(std::forward<F>(functor)(std::get<FirstI>(args))),
            TransformReduce(std::forward<F>(functor), args, std::index_sequence<I...>{}));
}
