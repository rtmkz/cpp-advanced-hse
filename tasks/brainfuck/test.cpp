#include <catch.hpp>
#include "brainfuck.h"

#define cat_nx(A, B) A ## B
#define cat_(A, B) cat_nx(A, B)
#define cat(A) cat_(A, __LINE__)

#define check(IN, OUT, CMD) \
    constexpr auto cat(in) = compile_string(IN); \
    constexpr auto cat(out) = compile_string(OUT); \
    constexpr auto cat(cmd) = compile_string(CMD); \
    using cat(eval_t) = Eval<decltype(cat(in)), \
        decltype(cat(cmd))>::Res; \
    using cat(out_t) = decltype(cat(out)); \
    REQUIRE(std::is_same_v<cat(eval_t), cat(out_t)>);

TEST_CASE("Simple") {
    check("h", "h", ",.");
    check("", "\0\0\0\0\0", ".....");
    check("0", "3", ",+++.");
}
