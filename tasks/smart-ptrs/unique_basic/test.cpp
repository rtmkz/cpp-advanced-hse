#include "../unique_ptr.h"

#include <catch.hpp>

using U = UniquePtr<int>;

TEST_CASE("Basics") {
    SECTION("Move") {
        U s1(new int);
        U s2(new int);
        int* p = s1.Get();
        s2 = std::move(s1);
        REQUIRE(s2.Get() == p);
        REQUIRE(s1.Get() == 0);
    }
    SECTION("Move itself") {
        U s(new int);
        int* p = s.Get();
        s = std::move(s);
        REQUIRE(s.Get() == p);
    }
    SECTION("NULL") {
        U s(new int);
        s = NULL;
        REQUIRE(s.Get() == 0);
    }
    SECTION("nullptr") {
        U s(new int);
        s = nullptr;
        REQUIRE(s.Get() == 0);
    }
}

TEST_CASE("Modifiers") {
    SECTION("Release") {
        U p(new int);
        int* ap = p.Get();
        int* a = p.Release();
        REQUIRE(p.Get() == nullptr);
        REQUIRE(ap == a);
        REQUIRE(a != nullptr);
        delete a;
    }
    SECTION("Swap") {
        int* p1 = new int(1);
        U s1(p1);
        int* p2 = new int(2);
        U s2(p2);

        REQUIRE(s1.Get() == p1);
        REQUIRE(*s1.Get() == 1);
        REQUIRE(s2.Get() == p2);
        REQUIRE(*s2.Get() == 2);
        s1.Swap(s2);
        REQUIRE(s1.Get() == p2);
        REQUIRE(*s1.Get() == 2);
        REQUIRE(s2.Get() == p1);
        REQUIRE(*s2.Get() == 1);
    }
    SECTION("Reset") {
        U p(new int);
        int* i = p.Get();
        REQUIRE(i != nullptr);
        int* new_value = new int;
        p.Reset(new_value);
        REQUIRE(p.Get() == new_value);
    }
    SECTION("Reset const") {
        UniquePtr<const int> p(new int);
        const int* i = p.Get();
        REQUIRE(i != nullptr);
        int* new_value = new int;
        p.Reset(new_value);
        REQUIRE(p.Get() == new_value);
    }
    SECTION("Reset nullptr") {
        U p(new int);
        int* i = p.Get();
        REQUIRE(i != nullptr);
        p.Reset(nullptr);
        REQUIRE(p.Get() == nullptr);
    }
    SECTION("Reset empty") {
        U p(new int);
        int* i = p.Get();
        REQUIRE(i != nullptr);
        p.Reset();
        REQUIRE(p.Get() == nullptr);
    }
    SECTION("Reset self pass") {
        struct A {
            UniquePtr<A> ptr_;
            A() : ptr_(this) {}
            void Reset() { ptr_.Reset(); }
        };
        (new A)->Reset();
    }
}

TEST_CASE("Observers") {
    SECTION("Dereference") {
        U p(new int(3));
        REQUIRE(*p == 3);
    }
    SECTION("operator bool") {
        U p(new int(1));
        U const& cp = p;
        CHECK(p);
        CHECK(cp);
        U p0;
        U const& cp0 = p0;
        CHECK(!p0);
        CHECK(!cp0);
    }
    SECTION("Get") {
        int* p = new int(1);
        U s(p);
        U const& sc = s;
        REQUIRE(s.Get() == p);
        REQUIRE(sc.Get() == s.Get());
    }
    SECTION("Get const") {
        const int* p = new int(1);
        UniquePtr<const int> s(p);
        UniquePtr<const int> const& sc = s;
        REQUIRE(s.Get() == p);
        REQUIRE(sc.Get() == s.Get());
    }
    SECTION("operator->") {
        struct A {
            int i_{7};
        };

        UniquePtr<A> p(new A);
        REQUIRE(p->i_ == 7);
    }
}
