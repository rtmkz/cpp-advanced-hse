#include <type_traits>
#include <utility>

const int get_const_int(); //NOLINT
const volatile int& get_const_volatile_lvalue_int(); //NOLINT

void DoStuff() {
    int a;

    //static_assert(std::is_same_v<int, decltype(a)>);

    auto b = get_const_int(); // b = int
    auto c = get_const_volatile_lvalue_int(); // c = int

    decltype(auto) d = get_const_int(); // d = const int
    decltype(auto) e = get_const_volatile_lvalue_int(); // e = const volatile int &
}

// For use in unevaluated contexts. Real implementation is more complicated
template <class T> auto Declval() -> T&&;

void DoDeclval() {
    struct Default { int Foo() const; };
    struct NonDefault { NonDefault() = delete; int Foo() const; };
     
    decltype(Default().Foo()) n1 = 1;
    //decltype(NonDefault().foo()) n2 = n1; // error: no default constructor
    decltype(Declval<NonDefault>().Foo()) n2 = n1;
}

template <class T> T Foo(T);
template <class T, class F> void Transform(T*, T*, F&&) {}

/// Special case: decltype(auto) in lambdas

void DecltypeInLambdas() {
    int * first = nullptr;
    int * last = nullptr;

    // not returning reference if needed, extra copy
    Transform(first, last, []<class T>(T&& x) {
        return Foo(std::forward<T>(x));
    });

    Transform(first, last, []<class T>(T&& x) -> decltype(auto) {
        return Foo(std::forward<T>(x));
    });

    /// And what if Foo was overloaded?
    // We'd have to do something like that
    // Invoke([](auto&& x) -> decltype(Foo(std::forward<decltype(x)>(x)))
    //{
    //    return Foo(std::forward<decltype(x)>(x));
    //});

    /// http://open-std.org/JTC1/SC22/WG21/docs/papers/2017/p0573r0.html
}
