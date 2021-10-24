#include <vector>
#include <type_traits>
#include <concepts>

template <class It> void Process(It begin, It end);

void DoStuff() {
    std::vector<int> vector;
    int c_array[20];

    // Imagine we have an optimization for vector iterators...
    Process(vector.begin(), vector.end());

    // ...but we still want to process ordinary C-style arrays
    Process(c_array, c_array + 20);
}

// We know that iterators are not just pointers, they look like that:
// template <class T> struct Iter { using Type = T; T * ptr; };

// Furthermore, we don't want to take .begin() and .end() every time.
// We want to supply a range-container (something that has begin() and end())
template <class Range> void ProcessRange(Range r);


/// SFINAE solution

template <class T, typename = void>
struct IsIterable : std::false_type {};

template <class T>
struct IsIterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                  decltype(std::declval<T>().end())>>
    : std::true_type {};

template <class Range, typename = std::enable_if_t<IsIterable<Range>::value>>
void ProcessRangeSFINAE(Range r);

// sometimes used as here, equivalent to the above version
template <class Range>
std::enable_if_t<IsIterable<Range>::value, void> ProcessRangeSFINAE(Range r);

/// Concepts solution

//https://en.cppreference.com/w/cpp/ranges/range
template <class R>
concept Range = requires(const R& r) {
    std::begin(r); //same as "r has .begin()"
    std::end(r);
}

void ProcessRangeConcepts(const Range & auto r);
