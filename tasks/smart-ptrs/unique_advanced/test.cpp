#include "../unique.h"

#include "deleters.h"

#include <catch.hpp>

#include <iostream>

struct MyInt {
    int v;
    static int count_alive;
    MyInt(int v_) : v(v_) {
        count_alive++;
    };
    MyInt() {
        count_alive++;
    }
    ~MyInt() {
        count_alive--;
    }
    bool operator==(const int u) const {
        return v == u;
    }
};

int MyInt::count_alive = 0;

typedef UniquePtr<MyInt> U;
typedef UniquePtr<MyInt, Deleter<MyInt>> UD;

TEST_CASE("Basics") {
    SECTION("move") {
        UniquePtr<MyInt> s1(new MyInt), s2(new MyInt);
        MyInt* p = s1.Get();
        REQUIRE(MyInt::count_alive == 2);
        s2 = std::move(s1);
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(s2.Get() == p);
        REQUIRE(s1.Get() == 0);
    }
    SECTION("move with deleter") {
        UD s1(new MyInt, Deleter<MyInt>(5));
        MyInt* p = s1.Get();
        UD s2(new MyInt);
        REQUIRE(MyInt::count_alive == 2);
        s2 = std::move(s1);
        REQUIRE(s2.Get() == p);
        REQUIRE(s1.Get() == 0);
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(s2.GetDeleter().state() == 5);
        REQUIRE(s1.GetDeleter().state() == 0);
    }
    SECTION("move deleter properly") {
        CDeleter<MyInt> d1(5);
        UniquePtr<MyInt, CDeleter<MyInt>&> s1(new MyInt, d1);
        MyInt* p = s1.Get();
        CDeleter<MyInt> d2(6);
        UniquePtr<MyInt, CDeleter<MyInt>&> s2(new MyInt, d2);
        REQUIRE(MyInt::count_alive == 2);
        s2 = std::move(s1);
        REQUIRE(s2.Get() == p);
        REQUIRE(s1.Get() == 0);
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(d1.state() == 5);
        REQUIRE(d2.state() == 5);
    }
    SECTION("self move") {
        U s(new MyInt);
        MyInt* p = s.Get();
        s = std::move(s);
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(s.Get() == p);
    }
    SECTION("null") {
        U s(new MyInt);
        REQUIRE(MyInt::count_alive == 1);
        s = NULL;
        REQUIRE(MyInt::count_alive == 0);
        REQUIRE(s.Get() == 0);
    }
    SECTION("nullptr") {
        U s(new MyInt);
        REQUIRE(MyInt::count_alive == 1);
        s = nullptr;
        REQUIRE(MyInt::count_alive == 0);
        REQUIRE(s.Get() == 0);
    }
}

TEST_CASE("Modifiers") {
    SECTION("release noexcept") {
        U u;
        ((void)u);
        REQUIRE_NOTHROW(u.Release());
    }
    SECTION("release") {
        U p(new MyInt);
        MyInt* ap = p.Get();
        MyInt* a = p.Release();
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(p.Get() == nullptr);
        REQUIRE(ap == a);
        REQUIRE(a != nullptr);
        delete a;
        REQUIRE(MyInt::count_alive == 0);
    }
    SECTION("swap noexcept") {
        U u;
        ((void)u);
        REQUIRE_NOTHROW(u.Swap(u));
    }
    SECTION("swap") {
        MyInt* p1 = new MyInt(1);
        U s1(p1);
        MyInt* p2 = new MyInt(2);
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
        REQUIRE(MyInt::count_alive == 2);
    }
    SECTION("reset noexcept") {
        U u;
        ((void)u);
        REQUIRE_NOTHROW(u.Reset());
    }
    SECTION("reset") {
        U p(new MyInt);
        REQUIRE(MyInt::count_alive == 1);
        MyInt* i = p.Get();
        REQUIRE(i != nullptr);
        MyInt* new_value = new MyInt;
        REQUIRE(MyInt::count_alive == 2);
        p.Reset(new_value);
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(p.Get() == new_value);
    }
    SECTION("reset const") {
        UniquePtr<const MyInt> p(new MyInt);
        REQUIRE(MyInt::count_alive == 1);
        const MyInt* i = p.Get();
        REQUIRE(i != nullptr);
        MyInt* new_value = new MyInt;
        REQUIRE(MyInt::count_alive == 2);
        p.Reset(new_value);
        REQUIRE(MyInt::count_alive == 1);
        REQUIRE(p.Get() == new_value);
    }
    SECTION("reset noexcept nullptr") {
        U u;
        ((void)u);
        REQUIRE_NOTHROW(u.Reset(nullptr));
    }
    SECTION("reset nullptr") {
        U p(new MyInt);
        REQUIRE(MyInt::count_alive == 1);
        MyInt* i = p.Get();
        REQUIRE(i != nullptr);
        p.Reset(nullptr);
        REQUIRE(MyInt::count_alive == 0);
        REQUIRE(p.Get() == nullptr);
    }
    SECTION("reset no arg") {
        U p(new MyInt);
        REQUIRE(MyInt::count_alive == 1);
        MyInt* i = p.Get();
        REQUIRE(i != nullptr);
        p.Reset();
        REQUIRE(p.Get() == nullptr);
    }
    SECTION("reset self pass") {
        struct A {
            UniquePtr<A> ptr_;
            A() : ptr_(this) {
            }
            void reset() {
                ptr_.Reset();
            }
        };
        (new A)->reset();
    }
}

TEST_CASE("Observers") {
    SECTION("dereference") {
        U p(new MyInt(3));
        REQUIRE(*p == 3);
    }
    SECTION("bool") {
        U p(new MyInt(1));
        U const& cp = p;
        CHECK(p);
        CHECK(cp);
        U p0;
        U const& cp0 = p0;
        CHECK(!p0);
        CHECK(!cp0);
    }
    SECTION("get") {
        MyInt* p = new MyInt(1);
        U s(p);
        U const& sc = s;
        REQUIRE(s.Get() == p);
        REQUIRE(sc.Get() == s.Get());
    }
    SECTION("get const") {
        const MyInt* p = new MyInt(1);
        UniquePtr<const MyInt> s(p);
        UniquePtr<const MyInt> const& sc = s;
        REQUIRE(s.Get() == p);
        REQUIRE(sc.Get() == s.Get());
    }
    SECTION("op_arrow") {
        struct A {
            int i_;

            A() : i_(7) {
            }
        };

        UniquePtr<A> p(new A);
        REQUIRE(p->i_ == 7);
    }
    SECTION("get deleter") {
        UniquePtr<MyInt, DeleterCheckConst> p;
        REQUIRE(p.GetDeleter().test() == 5);
    }
    SECTION("get deleter const") {
        const UniquePtr<MyInt, DeleterCheckConst> p;
        REQUIRE(p.GetDeleter().test() == 6);
    }
    SECTION("get deleter ref") {
        typedef UniquePtr<MyInt, DeleterCheckConst&> UPtr;
        DeleterCheckConst d;
        UPtr p(nullptr, d);
        const UPtr& cp = p;
        REQUIRE(p.GetDeleter().test() == 5);
        REQUIRE(cp.GetDeleter().test() == 5);
    }
    SECTION("get deleter const ref") {
        typedef UniquePtr<MyInt, const DeleterCheckConst&> UPtr;
        const DeleterCheckConst d;
        UPtr p(nullptr, d);
        const UPtr& cp = p;
        REQUIRE(p.GetDeleter().test() == 6);
        REQUIRE(cp.GetDeleter().test() == 6);
    }
}

template <typename T>
struct DefaultDelete {
    void operator()(T* ptr) const noexcept {
        static_assert(sizeof(T) > 0, "default_delete can not delete incomplete type");
        static_assert(!std::is_void<T>::value, "default_delete can not delete incomplete type");
        delete ptr;
    }
};

TEST_CASE("test_pointer_deleter_ctor") {
    SECTION("1") {
        UniquePtr<MyInt> p(0);
        REQUIRE(p.Get() == 0);
    }
    SECTION("2") {
        UniquePtr<MyInt, Deleter<MyInt>> p(0);
        REQUIRE(p.Get() == 0);
        REQUIRE(p.GetDeleter().state() == 0);
    }
    SECTION("3") {
        DefaultDelete<MyInt> d;
        UniquePtr<MyInt, DefaultDelete<MyInt>> p(new MyInt{0}, d);
        // REQUIRE(p.Get() == 0);
    }
    SECTION("4") {
        UniquePtr<MyInt, Deleter<MyInt>> p(0, Deleter<MyInt>(5));
        REQUIRE(p.Get() == 0);
        REQUIRE(p.GetDeleter().state() == 5);
    }
}

TEST_CASE("UniquePtr<void, CheckVoidPtrDeleter>") {
    SECTION("It compiles!") {
        UniquePtr<void, CheckVoidPtrDeleter> p(malloc(100));
    }
}

TEST_CASE("Array specialization") {
    SECTION("Just exists") {
        UniquePtr<MyInt[]> u(new MyInt[100]);
        REQUIRE(MyInt::count_alive == 100);
        u.Reset();
        REQUIRE(MyInt::count_alive == 0);
    }

    SECTION("Able to use custom deleters") {
        UniquePtr<MyInt[], CheckArrayDeleter<MyInt>> u(new MyInt[100], CheckArrayDeleter<MyInt>{});
        REQUIRE(MyInt::count_alive == 100);
        u.Reset();
        REQUIRE(MyInt::count_alive == 0);
    }

    SECTION("Operator []") {
        UniquePtr<int[]> u(new int[]{0, 1, 2, 3, 4});
        for (int i = 0; i < 5; ++i) {
            REQUIRE(u[i] == i);
            u[i] = -i;
            REQUIRE(u[i] == -i);
        }
    }
}

TEST_CASE("Compressed pair usage") {
    SECTION("Stateless struct deleter") {
        static_assert(sizeof(UniquePtr<int>) == 8);
        static_assert(sizeof(UniquePtr<int, CheckArrayDeleter<int>>) == 8);
    }

    SECTION("Stateful struct deleter") {
        static_assert(sizeof(UniquePtr<int, CheckArrayDeleterStateful<int>>) == 16);
    }

    SECTION("Stateless lambda deleter") {
        auto lambda_deleter = [](int* ptr) { delete ptr; };
        static_assert(sizeof(UniquePtr<int, decltype(lambda_deleter)>) == 8);
    }

    SECTION("Stateful lambda deleter") {
        int some_useless_counter = 0;
        auto lambda_deleter = [&some_useless_counter](int* ptr) {
            delete ptr;
            ++some_useless_counter;
        };
        static_assert(sizeof(UniquePtr<int, decltype(lambda_deleter)>) == 16);
    }

    SECTION("Function pointer deleter") {
        static_assert(sizeof(UniquePtr<int, decltype(&DeleteFunction<int>)>) == 16);
    }

    SECTION("std::function heavy deleter") {
        std::function<void(int*)> function = [](int* ptr) { delete ptr; };
        static_assert(sizeof(UniquePtr<int, decltype(function)>) == 64);
    }
}
