#include "../shared.h"
#include "count_new.h"

#include <catch.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Empty") {
    SharedPtr<int> a;
    SharedPtr<int> b;
    b = a;
    SharedPtr c(a);
    b = std::move(c);
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Copy/move") {
    SharedPtr a(new std::string("aba"));
    std::string* ptr;
    {
        SharedPtr b(a);
        SharedPtr c(a);
        ptr = c.Get();
    }
    REQUIRE(ptr == a.Get());
    REQUIRE(*ptr == "aba");

    SharedPtr b(new std::string("caba"));
    {
        SharedPtr c(b);
        SharedPtr d(b);
        d = std::move(a);
        REQUIRE(*c == "caba");
        REQUIRE(*d == "aba");
        b.Reset(new std::string("test"));
        REQUIRE(*c == "caba");
    }
    REQUIRE(*b == "test");

    SharedPtr<std::string> end;
    {
        SharedPtr d(new std::string("delete"));
        d = b;
        SharedPtr c(std::move(b));
        REQUIRE(*d == "test");
        REQUIRE(*c == "test");
        d = d;
        c = end;
        d.Reset(new std::string("delete"));
        end = d;
    }

    REQUIRE(*end == "delete");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

struct ModifiersB {
    static int count;

    ModifiersB() {
        ++count;
    }
    ModifiersB(const ModifiersB&) {
        ++count;
    }
    virtual ~ModifiersB() {
        --count;
    }
};

int ModifiersB::count = 0;

struct ModifiersA : public ModifiersB {
    static int count;

    ModifiersA() {
        ++count;
    }
    ModifiersA(const ModifiersA& other) : ModifiersB(other) {
        ++count;
    }
    ~ModifiersA() {
        --count;
    }
};

int ModifiersA::count = 0;

struct ModifiersC {
    static int count;

    ModifiersC() {
        ++count;
    }
    ModifiersC(const ModifiersC&) {
        ++count;
    }
    ~ModifiersC() {
        --count;
    }
};

int ModifiersC::count = 0;

TEST_CASE("Modifiers") {
    SECTION("Reset") {
        {
            SharedPtr p(new ModifiersB);
            p.Reset();
            REQUIRE(ModifiersA::count == 0);
            REQUIRE(ModifiersB::count == 0);
            REQUIRE(p.UseCount() == 0);
            REQUIRE(p.Get() == nullptr);
        }
        REQUIRE(ModifiersA::count == 0);
        {
            SharedPtr<ModifiersB> p;
            p.Reset();
            REQUIRE(ModifiersA::count == 0);
            REQUIRE(ModifiersB::count == 0);
            REQUIRE(p.UseCount() == 0);
            REQUIRE(p.Get() == 0);
        }
        REQUIRE(ModifiersA::count == 0);
    }

    SECTION("Reset ptr") {
        {
            SharedPtr p(new ModifiersB);
            ModifiersA* ptr = new ModifiersA;
            p.Reset(ptr);
            REQUIRE(ModifiersA::count == 1);
            REQUIRE(ModifiersB::count == 1);
            REQUIRE(p.UseCount() == 1);
            REQUIRE(p.Get() == ptr);
        }
        REQUIRE(ModifiersA::count == 0);
        {
            SharedPtr<ModifiersB> p;
            ModifiersA* ptr = new ModifiersA;
            p.Reset(ptr);
            REQUIRE(ModifiersA::count == 1);
            REQUIRE(ModifiersB::count == 1);
            REQUIRE(p.UseCount() == 1);
            REQUIRE(p.Get() == ptr);
        }
        REQUIRE(ModifiersA::count == 0);
    }

    SECTION("Swap") {
        {
            ModifiersC* ptr1 = new ModifiersC;
            ModifiersC* ptr2 = new ModifiersC;
            SharedPtr p1(ptr1);
            {
                SharedPtr p2(ptr2);
                p1.Swap(p2);
                REQUIRE(p1.UseCount() == 1);
                REQUIRE(p1.Get() == ptr2);
                REQUIRE(p2.UseCount() == 1);
                REQUIRE(p2.Get() == ptr1);
                REQUIRE(ModifiersC::count == 2);
            }
            REQUIRE(p1.UseCount() == 1);
            REQUIRE(p1.Get() == ptr2);
            REQUIRE(ModifiersC::count == 1);
        }
        REQUIRE(ModifiersC::count == 0);
        {
            ModifiersC* ptr1 = new ModifiersC;
            ModifiersC* ptr2 = 0;
            SharedPtr<ModifiersC> p1(ptr1);
            {
                SharedPtr<ModifiersC> p2;
                p1.Swap(p2);
                REQUIRE(p1.UseCount() == 0);
                REQUIRE(p1.Get() == ptr2);
                REQUIRE(p2.UseCount() == 1);
                REQUIRE(p2.Get() == ptr1);
                REQUIRE(ModifiersC::count == 1);
            }
            REQUIRE(p1.UseCount() == 0);
            REQUIRE(p1.Get() == ptr2);
            REQUIRE(ModifiersC::count == 0);
        }
        REQUIRE(ModifiersC::count == 0);
        {
            ModifiersC* ptr1 = 0;
            ModifiersC* ptr2 = new ModifiersC;
            SharedPtr<ModifiersC> p1;
            {
                SharedPtr<ModifiersC> p2(ptr2);
                p1.Swap(p2);
                REQUIRE(p1.UseCount() == 1);
                REQUIRE(p1.Get() == ptr2);
                REQUIRE(p2.UseCount() == 0);
                REQUIRE(p2.Get() == ptr1);
                REQUIRE(ModifiersC::count == 1);
            }
            REQUIRE(p1.UseCount() == 1);
            REQUIRE(p1.Get() == ptr2);
            REQUIRE(ModifiersC::count == 1);
        }
        REQUIRE(ModifiersC::count == 0);
        {
            ModifiersC* ptr1 = 0;
            ModifiersC* ptr2 = 0;
            SharedPtr<ModifiersC> p1;
            {
                SharedPtr<ModifiersC> p2;
                p1.Swap(p2);
                REQUIRE(p1.UseCount() == 0);
                REQUIRE(p1.Get() == ptr2);
                REQUIRE(p2.UseCount() == 0);
                REQUIRE(p2.Get() == ptr1);
                REQUIRE(ModifiersC::count == 0);
            }
            REQUIRE(p1.UseCount() == 0);
            REQUIRE(p1.Get() == ptr2);
            REQUIRE(ModifiersC::count == 0);
        }
        REQUIRE(ModifiersC::count == 0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

struct OperatorBoolA {
    int a;
    virtual ~OperatorBoolA(){};
};

TEST_CASE("Observers") {
    SECTION("operator->") {
        const SharedPtr<std::pair<int, int>> p(new std::pair<int, int>(3, 4));
        REQUIRE(p->first == 3);
        REQUIRE(p->second == 4);
        p->first = 5;
        p->second = 6;
        REQUIRE(p->first == 5);
        REQUIRE(p->second == 6);
    }

    SECTION("Dereference") {
        const SharedPtr<int> p(new int(32));
        REQUIRE(*p == 32);
        *p = 3;
        REQUIRE(*p == 3);
    }

    SECTION("operator bool") {
        static_assert(std::is_constructible<bool, SharedPtr<OperatorBoolA>>::value, "");
        static_assert(!std::is_convertible<SharedPtr<OperatorBoolA>, bool>::value, "");
        {
            const SharedPtr<int> p(new int(32));
            REQUIRE(p);
        }
        {
            const SharedPtr<int> p;
            REQUIRE(!p);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

struct A {
    static int count;

    A(int i, char c) : int_(i), char_(c) {
        ++count;
    }
    A(const A& a) : int_(a.int_), char_(a.char_) {
        ++count;
    }
    ~A() {
        --count;
    }

    int get_int() const {
        return int_;
    }
    char get_char() const {
        return char_;
    }

    A* operator&() = delete;

private:
    int int_;
    char char_;
};

int A::count = 0;

TEST_CASE("MakeShared one allocation") {
    int nc = globalMemCounter.outstanding_new;
    {
        int i = 67;
        char c = 'e';
        SharedPtr<A> p = MakeShared<A>(i, c);
        REQUIRE(globalMemCounter.checkOutstandingNewEq(nc+1));
        REQUIRE(A::count == 1);
        REQUIRE(p->get_int() == 67);
        REQUIRE(p->get_char() == 'e');
    }

    nc = globalMemCounter.outstanding_new;
    {
        char c = 'e';
        SharedPtr<A> p = MakeShared<A>(67, c);
        REQUIRE(globalMemCounter.checkOutstandingNewEq(nc+1));
        REQUIRE(A::count == 1);
        REQUIRE(p->get_int() == 67);
        REQUIRE(p->get_char() == 'e');
    }
    REQUIRE(A::count == 0);
}
