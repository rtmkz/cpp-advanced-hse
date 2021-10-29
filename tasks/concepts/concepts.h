#include <type_traits>
#include <iterator>

template <class P, class T>
concept bool Predicate = requires(P p, T t) {
    ...
};


template <class T>
concept bool Indexable;