#include <vector>
#include <functional>
#include <span>
#include <type_traits>
#include <concepts>

/// Initial C++11-C++17 version: our very own std::transform.
template <class Functor, class T>
auto Transform(Functor && functor, const std::vector<T> & container) {
    // What if T isn't default constructible ?
    using ResultType = decltype(functor(T{}));

    std::vector<ResultType> out;
    out.reserve(container.size());

    for (const auto& elem : container) {
        out.emplace_back(functor(elem));
    }

    return out;
};

void DoSomeBusinessStuff() {
    /// Oops, hundreds of lines of messy template messages deep in stdlib
    /// Hard to determine what caused the error
    //Transform([] (std::string) { }, std::vector<int>{});
}

// We need to constrain our Transform so non-compiling code would produce a clear
// and concise error.

// Idea 1: use std::span over const std::vector&
// 1. We can pass std::array& or even C-style arrays T[] without allocations.
// 2. Better semantics: we just view the original data, not own it.

// Idea 2: use Ret as template parameter so we can determine the result type.

template <class Ret, class T> // Disallows stateful lambdas
std::vector<Ret> Transform2(Ret(*functor)(const T&), std::span<const T>);

template <class Ret, class T> // Runtime cost if passed functor is "big"
std::vector<Ret> Transform3(std::function<Ret(const T&)>, std::span<const T>);

// So, we want a solution that has no runtime cost and can produce readable errors.

template <class F, class T,
    typename = std::enable_if_t<std::is_invocable_v<F, T>>>
auto TransformSFINAE(F && functor, std::span<const T>);

template <class T>
auto TransformConcepts(std::invocable<T> auto && functor, std::span<const T>);
