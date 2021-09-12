#include "../unique.h"

#include "deleters.h"
#include "../my_int.h"

#include <catch.hpp>

#include <memory>

TEST_CASE("Construction with deleters") {
    SECTION("From move-only deleter") {
        Deleter<MyInt> d;
        UniquePtr<MyInt, Deleter<MyInt>> s(new MyInt, std::move(d));
    }

    SECTION("From copyable deleter") {
        const CopyableDeleter<MyInt> cd;
        UniquePtr<MyInt, CopyableDeleter<MyInt>> s(new MyInt, cd);
    }

    SECTION("From temporary") {
        UniquePtr<MyInt, Deleter<MyInt>> s(new MyInt, Deleter<MyInt>{});
    }

    SECTION("From const reference to copy-able object") {
        CopyableDeleter<MyInt> d;
        const auto& cr = d;

        UniquePtr<MyInt, CopyableDeleter<MyInt>> s(new MyInt, cr);
    }
}

TEST_CASE("Moving deleters") {
    SECTION("Move with custom deleter") {
        UniquePtr<MyInt, Deleter<MyInt>> s1(new MyInt, Deleter<MyInt>(5));
        MyInt* p = s1.Get();
        UniquePtr<MyInt, Deleter<MyInt>> s2(new MyInt);

        REQUIRE(MyInt::AliveCount() == 2);
        REQUIRE(s1.GetDeleter().GetTag() == 5);
        REQUIRE(s2.GetDeleter().GetTag() == 0);

        s2 = std::move(s1);

        REQUIRE(s2.Get() == p);
        REQUIRE(s1.Get() == nullptr);
        REQUIRE(MyInt::AliveCount() == 1);
        REQUIRE(s2.GetDeleter().GetTag() == 5);
        REQUIRE(s1.GetDeleter().GetTag() == 0);
    }

    SECTION("Move with reference deleter type") {
        CopyableDeleter<MyInt> d1(5);
        UniquePtr<MyInt, CopyableDeleter<MyInt>&> s1(new MyInt, d1);
        MyInt* p1 = s1.Get();

        CopyableDeleter<MyInt> d2(6);
        UniquePtr<MyInt, CopyableDeleter<MyInt>&> s2(new MyInt, d2);

        REQUIRE(MyInt::AliveCount() == 2);

        s2 = std::move(s1);

        REQUIRE(s2.Get() == p1);
        REQUIRE(s1.Get() == nullptr);
        REQUIRE(MyInt::AliveCount() == 1);
        REQUIRE(d1.GetTag() == 5);
        REQUIRE(d2.GetTag() == 5);
    }
}

TEST_CASE("GetDeleter") {
    SECTION("Get deleter") {
        UniquePtr<MyInt, Deleter<MyInt>> p;

        REQUIRE(!p.GetDeleter().IsConst());
    }

    SECTION("Get deleter const") {
        const UniquePtr<MyInt, Deleter<MyInt>> p;

        REQUIRE(p.GetDeleter().IsConst());
    }

    SECTION("Get deleter reference") {
        using UDRef = UniquePtr<MyInt, Deleter<MyInt>&>;
        Deleter<MyInt> d;

        UDRef p(nullptr, d);
        const UDRef& cp = p;

        REQUIRE(!p.GetDeleter().IsConst());
        REQUIRE(!cp.GetDeleter().IsConst());
    }

    SECTION("Get deleter const reference") {
        using UDConstRef = UniquePtr<MyInt, const Deleter<MyInt>&>;
        const Deleter<MyInt> d;

        UDConstRef p(nullptr, d);
        const UDConstRef& cp = p;

        REQUIRE(p.GetDeleter().IsConst());
        REQUIRE(cp.GetDeleter().IsConst());
    }
}

struct VoidPtrDeleter {
    void operator()(void* ptr) {
        free(ptr);
    }
};

TEST_CASE("UniquePtr<void, VoidPtrDeleter>") {
    SECTION("It compiles!") {
        UniquePtr<void, VoidPtrDeleter> p(malloc(100));
    }
}

TEST_CASE("Array specialization") {
    SECTION("delete[] is called") {
        UniquePtr<MyInt[]> u(new MyInt[100]);
        REQUIRE(MyInt::AliveCount() == 100);
        u.Reset();
        REQUIRE(MyInt::AliveCount() == 0);
    }

    SECTION("Able to use custom deleters") {
        UniquePtr<MyInt[], Deleter<MyInt[]>> u(new MyInt[100]);
        REQUIRE(MyInt::AliveCount() == 100);
        u.Reset();
        REQUIRE(MyInt::AliveCount() == 0);
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

template <typename T>
void DeleteFunction(T* ptr) {
    delete ptr;
}

template <typename T>
struct StatefulDeleter {
    int some_useless_field = 0;

    void operator()(T* ptr) {
        delete ptr;
        ++some_useless_field;
    }
};

TEST_CASE("Compressed pair usage") {
    SECTION("Stateless struct deleter") {
        static_assert(sizeof(UniquePtr<int>) == 8);
        static_assert(sizeof(UniquePtr<int, std::default_delete<int>>) == 8);
    }

    SECTION("Stateful struct deleter") {
        static_assert(sizeof(UniquePtr<int, StatefulDeleter<int>>) == 16);
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
