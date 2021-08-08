#pragma once

template <class F, class ...Args>
using TransformResult = /** part 2 */ bool;

template <class F, class ...Types>
concept invocable_on_all_types = /** part 1 */ true;

template <class F, class ...Args>
constexpr TransformResult<F, Args...>
TransformTuple(F && functor, const std::tuple<Args...>& args)
    requires invocable_on_all_types<F, Args...>
{
    return {}; /// part 3
}
