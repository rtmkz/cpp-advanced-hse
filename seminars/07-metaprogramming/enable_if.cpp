#include <type_traits>

/// enable_if_t as in libc++ (clang)

template <bool Cond, class T = void>
struct EnableIf {};

template <class T>
struct EnableIf<true, T>{ using Type = T; };

template <bool Cond, class T = void>
using EnableIfT = typename EnableIf<Cond, T>::Type;

// However, we need to instantiate EnableIf<> for every condition (true/false)
// for every type T, so we get a lot of instantiations.
// SFINAE is slow (refer to "rule of Chiel"), so we can optimize instantiations.

/// enable_if as in libstdc++ (gcc).
// The hack: we get only two instantiations of EnableIfGCC (true/false).
// Instantiating an alias template<> using Type = T is way cheaper than
// instantiating a struct.
template <bool Cond>
struct EnableIfGCC {};

template<>
struct EnableIfGCC<true>{ template<class T> using Type = T; };

/// Usage

template <class T, typename = EnableIfT<sizeof(T) < sizeof(long)>>
T Transform(const T&);

void DoStuff() {
    /// typename = std::enable_if_t<true> = void
    Transform(int(25));

    /// typename = std::enable_if_t<false>. No type in enable_if_t,
    /// overload is banned ("ill-formed")
    //Transform(13.37);
}

/// Conditional overloads (pre C++11, without if constexpr)

template <class Integer>
EnableIfT<std::is_integral<Integer>::value>
Foo(Integer) {};

/// error: redefinition
///> Default template arguments are not accounted for in function template equivalence
///> https://en.cppreference.com/w/cpp/language/function_template#Function_template_overloading
//template <class Floating,
//EnableIfT<std::is_floating_point<Floating>::value, void>
//Foo(Floating) {}; // error: redefinition

/// Conditional overloads: the right version

template <class Integer,
    EnableIfT<std::is_integral<Integer>::value, bool> = true>
void Bar(Integer) {};
 
template <class Floating,
    EnableIfT<std::is_floating_point<Floating>::value, bool> = true>
void Bar(Floating);

/// Conditional overloads: modern

template <class T>
auto Baz(T t) {
    if constexpr(std::is_same_v<T, int>)
        return t + 10;
    if constexpr(std::is_same_v<T, float>)
        return t + 13.37;
}

