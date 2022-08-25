#include <type_traits>

template <class ...> using VoidT = void;

template<class, class = void> struct HasMemberFoo
  : std::false_type { };

template<class T>
struct HasMemberFoo<T, std::void_t<decltype( std::declval<T&>().foo() )>>
  : std::true_type { };

/// Expressing same in C++20

template <class T>
concept Fooable = requires(T t) {
    t.foo();
}
