/// Before C++11, there were no variadic templates, so one needed to define
/// type lists as macros:
// TL_2(t1, t2) /* some pair meta-struct */
// TL_3(t1, t2, t3) TL_2(t1, TL_2(t2, t3))
// TL_4(t1, t2, t3, t4) TL_2(t1, TL_3(t2, t3, t4))
/// See LOKI

/// C++11 clean version
template <class ...> struct TypeList {};

// How to concat two type lists:
// No recursion, single instantiation
template <class ...A1, class ...A2>
TypeList<A1..., A2...> Concat(TypeList<A1...>, TypeList<A2...>) { return {}; }

/// Alias for type-only calculation
template <class TL1, class TL2>
using TConcat = decltype(Concat(TL1{}, TL2{}));
