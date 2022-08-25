Goals:

- How to read stdlib and pre C++11 code.
- How to design better APIs by restricting template code usage.
- How not to make your compiler boil.
- How to design containers with help of metaprogramming.

Plan:

- Talk about SFINAE, its motivation and cost.
- Show how various traits are implemented (and why they're implemented that way).
- Talk about rule of Chiel.
- Talk about decltype(), declval(), and void-t.
- Talk about transparent hashing.
- Talk about NTTP (non-type template parameters).
- Talk about lambdas in unevaluated contexts.
- Talk about type-lists and why they're needed

If have time: codegen & reflection

- vk.com kPHP -- translating a subset of PHP into C++ (Legacy)
- Generating entities definitions from schema (one-to-many)
- Filtering container by predefined states (Less boilerplate)
- Simplifying generic code.
- magic_enum (reflection for enums, using compiler macro PRETTY-FUNCTION)
- boost.pfr (reflection for aggregates)
- Applications in other languages -- Rust serde

https://habr.com/ru/company/vk/blog/527420
https://en.cppreference.com/w/cpp/keyword/reflexpr


If have time: macro:

- Why macro preprocessor in C/C++ operates on text and not on tokens like in Rust.
- Why macros were not Turing-complete until C++20 and what changed (recursive macros) https://www.scs.stanford.edu/~dm/blog/va-opt.html
- Modern usage of macros (scoped guards wrappers etc). Why constexpr/consteval is better than using macros.


Tasks for students:

- Implement is-nothrow-move-constructible
- Implement multi-hasher
