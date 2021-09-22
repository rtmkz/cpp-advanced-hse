#include "../shared.h"
#include "../weak.h"

#include <catch.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Empty weak") {
    WeakPtr<int> a;
    WeakPtr<int> b;
    a = b;
    WeakPtr c(a);
    b = std::move(c);

    auto shared = b.Lock();
    REQUIRE(shared.Get() == nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Copy/move") {
    SharedPtr<std::string> a(new std::string("aba"));
    WeakPtr<std::string> b(a);
    WeakPtr<std::string> empty;
    WeakPtr c(b);
    WeakPtr<std::string> d(a);

    REQUIRE(d.UseCount() == 1);

    REQUIRE(!c.Expired());
    c = empty;
    REQUIRE(c.Expired());

    b = std::move(c);

    WeakPtr e(std::move(d));
    REQUIRE(d.Lock().Get() == nullptr);

    auto locked = e.Lock();
    REQUIRE(*locked == "aba");

    WeakPtr<std::string> start(a);
    {
        SharedPtr a2(a);
        WeakPtr<std::string> f(a2);
        auto cur_lock = f.Lock();
        REQUIRE(cur_lock.Get() == SharedPtr(start).Get());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Weak expiration") {
    WeakPtr<std::string>* a;
    {
        SharedPtr<std::string> b(new std::string("aba"));
        SharedPtr c(b);
        a = new WeakPtr<std::string>(c);
        auto test = a->Lock();
        REQUIRE(*test == "aba");
        REQUIRE(!a->Expired());
    }
    REQUIRE(a->Expired());
    delete a;
}

TEST_CASE("Weak extends Shared") {
    SharedPtr<std::string>* b = new SharedPtr<std::string>(new std::string("aba"));
    WeakPtr<std::string> c(*b);
    auto a = c.Lock();
    delete b;
    REQUIRE(!c.Expired());
    REQUIRE(*a == "aba");
}

TEST_CASE("Shared from Weak") {
    SharedPtr<std::string>* x = new SharedPtr<std::string>(new std::string("aba"));
    WeakPtr<std::string> y(*x);
    delete x;
    REQUIRE(y.Expired());
    SharedPtr z = y.Lock();
    REQUIRE(z.Get() == nullptr);
}

TEST_CASE("Shared from invalid Weak") {
    WeakPtr<int> w_ptr;
    {
        SharedPtr<int> ptr = MakeShared<int>(42);
        w_ptr = ptr;
    }
    REQUIRE_THROWS_AS(SharedPtr<int>(w_ptr), BadWeakPtr);
}

TEST_CASE("Constness") {
    SharedPtr<int> sp(new int(42));
    WeakPtr<const int> wp(sp);
}
