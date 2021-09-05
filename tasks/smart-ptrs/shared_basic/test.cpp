#include "../shared_ptr.h"

#include <catch.hpp>

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
