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
    SharedPtr a(new std::string("aba"));
    WeakPtr b(a);
    WeakPtr<std::string> empty;
    WeakPtr c(b);
    WeakPtr d(a);

    REQUIRE(d.UseCount() == 3);

    REQUIRE(!c.Expired());
    c = empty;
    REQUIRE(c.Expired());

    b = std::move(c);
    auto locked = d.Lock();
    REQUIRE(*locked == "aba");

    WeakPtr start(a);
    {
        SharedPtr a2(a);
        WeakPtr f(a2);
        auto cur_lock = f.Lock();
        REQUIRE(cur_lock.Get() == SharedPtr(start).Get());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Weak expiration") {
    WeakPtr<std::string>* a;
    {
        SharedPtr b(new std::string("aba"));
        SharedPtr c(b);
        a = new WeakPtr(c);
        auto test = a->Lock();
        REQUIRE(*test == "aba");
        REQUIRE(!a->Expired());
    }
    REQUIRE(a->Expired());
    delete a;
}

TEST_CASE("Weak extends Shared") {
    SharedPtr<std::string>* b = new SharedPtr(new std::string("aba"));
    WeakPtr c(*b);
    auto a = c.Lock();
    delete b;
    REQUIRE(!c.Expired());
    REQUIRE(*a == "aba");
}

TEST_CASE("Shared from Weak") {
    SharedPtr<std::string>* x = new SharedPtr(new std::string("aba"));
    WeakPtr y(*x);
    delete x;
    REQUIRE(y.Expired());
    SharedPtr z(y);
    REQUIRE(z.Get() == nullptr);
}
