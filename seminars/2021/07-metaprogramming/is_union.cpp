/// > Anything you can do with a class, you can do with a union
/// No way to express some traits in pure C++ without compiler support

// libc++
template <class _Tp> /* */ is_union
    : public __libcpp_union<typename remove_cv<_Tp>::type> {};

TYPE_TRAIT_1(__is_union, IsUnion, KEYCXX) // AST/Decl.h

bool isUnion () const { return getTagKind() == TTK_Union; } //AST/APValue.h

//https://github.com/Quuxplusone/from-scratch/blob/master/include/scratch/bits/type-traits/compiler-magic.md
