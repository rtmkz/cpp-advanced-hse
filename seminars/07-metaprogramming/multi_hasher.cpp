#include <string_view>
#include <string>

template <class HashType, class ...Types>
struct multi_hasher {
    using is_transparent = void;
    // TODO
};

void DoStuff() {
    using mh = multi_hasher<std::string_view, const std::string&, const char *>;

    std::string_view sv = "string view";
    const std::string s = "string";
    const char * l = "literal";

    mh{}(sv);
    mh{}(s);
    mh{}(l);
}

// Solution:
//template <class HashType, class Arg>
//struct Overload {
//    size_t operator()(Arg a) const { return std::hash<HashType>{}(a); }
//};
//
//template <class HashType, class ...Types>
//struct multi_hasher : Overload<HashType, HashType>, Overload<HashType, Types>... {
//    using is_transparent = void;
//};
