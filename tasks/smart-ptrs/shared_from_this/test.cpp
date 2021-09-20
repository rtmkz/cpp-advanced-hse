#include "../shared.h"
#include "../weak.h"

#include <catch.hpp>

#include <atomic>

struct T : public EnableSharedFromThis<T> {};

struct Y : T {};

struct Z : Y {};

void NullDeleter(void*) {
}

struct Foo : virtual public EnableSharedFromThis<Foo> {
    virtual ~Foo() {
    }
};

struct Bar : public Foo {
    Bar(int) {
    }
};

std::atomic<int32_t> outstanding_new{0};

void* operator new(size_t size) {
    void* p = malloc(size);
    outstanding_new.fetch_add(1);
    return p;
}

void* operator new(size_t size, const std::nothrow_t&) noexcept {
    void* p = malloc(size);
    outstanding_new.fetch_add(1);
    return p;
}

void operator delete(void* p) noexcept {
    outstanding_new.fetch_sub(1);
    free(p);
}

void operator delete(void* p, size_t) noexcept {
    outstanding_new.fetch_sub(1);
    free(p);
}

TEST_CASE("SharedFromThis") {
    outstanding_new.store(0);
    {
        SharedPtr<T> t1(new T);
        SharedPtr<T> t2(MakeShared<T>());
    }
    REQUIRE(outstanding_new.load() == 0);

    {
        int x = 42;
        SharedPtr<Bar> t1(new Bar(42));
        REQUIRE(t1->SharedFromThis() == t1);
        SharedPtr<Bar> t2(MakeShared<Bar>(x));
        REQUIRE(t2->SharedFromThis() == t2);
    }
    REQUIRE(outstanding_new.load() == 0);

    {
        SharedPtr<Y> p(new Z);
        SharedPtr<T> q = p->SharedFromThis();
        REQUIRE(p == q);
    }
    REQUIRE(outstanding_new.load() == 0);

    {
        T* ptr = new T;
        SharedPtr<T> s(ptr);
        REQUIRE(!ptr->WeakFromThis().Expired());
        {
            try {
                SharedPtr<T> new_s = ptr->SharedFromThis();
                REQUIRE(new_s == s);
            } catch (...) {
                REQUIRE(false);
            }
        }
        s.Reset();
        REQUIRE(outstanding_new.load() == 0);
    }

    {
        T* ptr = new T;
        WeakPtr<T> weak;
        {
            SharedPtr<T> s(ptr);
            REQUIRE(ptr->SharedFromThis() == s);
            weak = s;
            REQUIRE(!weak.Expired());
        }
        REQUIRE(weak.Expired());
        weak.Reset();

        REQUIRE(outstanding_new.load() == 0);
    }
}

TEST_CASE("WeakFromThis") {
    T* ptr = new T;
    const T* cptr = ptr;

    static_assert(noexcept(ptr->WeakFromThis()), "Operation must be noexcept");
    static_assert(noexcept(cptr->WeakFromThis()), "Operation must be noexcept");

    WeakPtr<T> weak = ptr->WeakFromThis();
    REQUIRE(weak.Expired());

    WeakPtr<const T> my_const_weak = cptr->WeakFromThis();
    REQUIRE(my_const_weak.Expired());

    SharedPtr<T> sptr(ptr);
    weak = ptr->WeakFromThis();
    REQUIRE(!weak.Expired());
    REQUIRE(weak.Lock().Get() == ptr);
}
