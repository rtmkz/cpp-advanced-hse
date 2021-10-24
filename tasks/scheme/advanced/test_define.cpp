#include "../test/scheme_test.h"

TEST_CASE_METHOD(SchemeTest, "PairMutations") {
    ExpectNoError("(define x '(1 . 2))");

    ExpectNoError("(set-car! x 5)");
    ExpectEq("(car x)", "5");

    ExpectNoError("(set-cdr! x 6)");
    ExpectEq("(cdr x)", "6");
}
