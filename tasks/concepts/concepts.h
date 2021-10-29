#include <type_traits>
#include <iterator>

template <class P, class T>
concept Predicate = requires(P p, T t) {
    ...
};


template <class T>
concept Indexable;