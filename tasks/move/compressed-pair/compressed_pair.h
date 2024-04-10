#include <type_traits>
#include <utility>

template <typename T, size_t I, bool enableEBO = std::is_empty_v<T> && !std::is_final_v<T>>
struct CompressedPairElement : private T {
    using base_type = T;

    CompressedPairElement() = default;
    CompressedPairElement(const T& value) {}
    CompressedPairElement(T&& value) noexcept {std::move(value);}

    T& get() {
        return static_cast<T&>(*this);
    }

    const T& get() const {
        return static_cast<const T&>(*this);
    }
};

template <typename T, size_t I>
struct CompressedPairElement<T, I, false> {
    CompressedPairElement() = default;
    CompressedPairElement(const T& value) : value(value) {}
    CompressedPairElement(T&& value) noexcept : value(std::move(value)) {}

    T& get() {
        return value;
    }

    const T& get() const {
        return value;
    }

    T value{};
};

template <typename F, typename S>
class CompressedPair : private CompressedPairElement<F, 0>, private CompressedPairElement<S, 1> {
public:
    using First = CompressedPairElement<F, 0>;
    using Second = CompressedPairElement<S, 1>;

    CompressedPair() = default;

    template <typename T1, typename T2>
    CompressedPair(T1&& first, T2&& second)
        : First(std::forward<T1>(first)), Second(std::forward<T2>(second)) {}

    F& GetFirst() {
        return First::get();
    }
    const F& GetFirst() const {
        return First::get();
    }
    S& GetSecond() {
        return Second::get();
    }
    const S& GetSecond() const {
        return Second::get();
    }
};
