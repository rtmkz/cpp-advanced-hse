#include <memory>
#include <type_traits>

template <class T> void Foo();

template <class T> struct Bar {
    template <class U> void Baz();

    using Type = T;

    template <class I>
    using IType = I;
};

using BarType = typename Bar<int>::Type;

using BarIType = typename Bar<int>::template IType<int>;

constexpr bool kBarIsNotInteger = !std::is_integral_v<Bar<int>>;
constexpr bool kBarIsNotIntegerOld = std::is_integral<Bar<int>>::value;


struct FD;

using FDPtr = std::unique_ptr<FD>;

struct FD {
    static FDPtr MakePtr();
};


template <auto A> using AType = decltype(A);
template <size_t I> constexpr size_t kI = I;

struct V {};
template <V v> void MakeV();

template <class T> concept integral = std::is_integral_v<T>;
template <integral T> void ITakeOnlyIntegrals();


template <class Left, class Right> struct Pair{};

template <class Left>
struct Pair<Left, int> {
    using IsIntTag = void;
}
