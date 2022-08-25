/// Idea: want to write a compile-time
/// switch-like statement

#include <type_traits>
#include <utility>

template <auto V> using Constant = std::integral_constant<decltype(V), V>;

template <class T, T Begin, T... Is>
constexpr bool StaticFor(auto && f, std::integer_sequence<decltype(Begin), Is...>)
{
    return (f(Constant<Begin + Is>()) || ...);
}

template <auto Begin, decltype(Begin) End>
constexpr bool StaticFor(auto && f)
{
    using T = decltype(Begin);

    return StaticFor<T, Begin>(
        std::forward<decltype(f)>(f),
        std::make_integer_sequence<T, End - Begin>{});
}

template <int I> void Foo() { };

void DoStuff() {
    StaticFor<0, 20>([](auto i) {
        // Although i looks like a normal variable, it's a Constant so
        // it can be used in template context
        Foo<i>();
    });
}
