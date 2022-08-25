#include <array>
#include <type_traits>

/// Not supported in clang as for now
//Idea: do not write trait noodle code

struct IntegralReader {};

template <class T> struct ArrayReader {};

struct DReader { DReader() = delete; };

template <class T> // Better than writing traits
using Type = decltype([] {
    if constexpr(std::is_integral_v<T>) {
        return IntegralReader();
    } else if constexpr (std::is_array_v<T>) {
        return DReader();
    } else {
        using Underlying = typename T::underlying;
        using Decayed = std::decay_t<Underlying>;
        return ArrayReader<Decayed>();
    }
}()); //IILE

using a = Type<int>;
using b = Type<std::array<int, 20>>;

