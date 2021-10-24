#include <type_traits>

/// Not portable among architectures
/// Not portable among compilers (MSVC)

template <class T>
std::true_type Detect(
    /// A polymorphic type must support dynamic_cast
    decltype(dynamic_cast<const volatile void*>(static_cast<T*>(nullptr)))
);

/// Ellipsis overload has lowest priority.
// Whoa, magic. We can't list here non-polymorhic types as we don't know them, 
// so we just accept all types (but for polymorhic ones the first overload will
// be invoked
template <class T> std::false_type Detect(...);
 
template <class T>
using IsPolymorphic = decltype(Detect<T>(nullptr));
