#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>

#include "polymorphism.h"

void Trap() {
    std::cout << "Trap" << std::endl;
}

int TrapInt() {
    return 100;
}

int Sum(int a, int b) {
    return a + b;
}

class Base {
public:
    virtual void Test() {
        std::cout << "Base" << std::endl;
    }
    static constexpr size_t N = 1;
};

class Triple {
public:
    virtual void First() {
        std::cout << "First" << std::endl;
    }
    virtual void Second() {
        std::cout << "Second" << std::endl;
    }
    virtual void Third() {
        std::cout << "Third" << std::endl;
    }
    static constexpr size_t N = 3;
};

class GuardedTriple {
public:
    static constexpr size_t N = 3;
        void CallAll() {
            Public();
            Protected();
            Private();
        }

public:
    virtual void Public() {
        std::cout << "Public" << std::endl;
    }
protected:
    virtual void Protected() {
        std::cout << "Protected" << std::endl;
    }
private:
    virtual void Private() {
        std::cout << "Private" << std::endl;
    }
};

class ValueReturning {
public:
    virtual int ReturnValue() {
        return 42;
    }
    static constexpr size_t N = 1;
};

#define __STRINGIFY__(X) #X
#define STRINGIFY(X) __STRINGIFY__(X)
#define __CONCAT__(X, Y) X##Y
#define CONCAT(X, Y) __CONCAT__(X, Y)
#define ADD_CNT(X) CONCAT(X, __COUNTER__)
#define FIX(FUNC) virtual void ADD_CNT(FUNC)() { std::cout << std::to_string(call_id++) << std::endl; }
#define HUNDRED(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \
    FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) FIX(X) \


class Huge {
public:
    HUNDRED(Func)
    static constexpr size_t N = 100;
private:
    size_t call_id = 0;
};

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

class TestPolymorphism : public ::testing::Test {
public:
    // These two functions override stdout
    // If you want to disable it and check the output youself, just comment them out
    void SetUp() override {
        old = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(old);
    }
protected:
    std::stringstream buffer;
    std::streambuf* old;
};

TEST_F(TestPolymorphism, Single) {
    Base* base = new Base();

    base->Test();
    TrapObject<Base::N>(*base, &Trap);
    base->Test();

    ASSERT_EQ(buffer.str(), std::string("Base\nTrap\n"));
}

TEST_F(TestPolymorphism, ExampleToThinkAbout) {
    Base base;

    (&base)->Test(); // Base
    base.Test();     // Base

    TrapObject<Base::N>(base, &Trap);

    (&base)->Test(); // Trap
    base.Test();     // Base *** Why? ***

    ASSERT_EQ(buffer.str(), std::string("Base\nBase\nTrap\nBase\n"));
}

TEST_F(TestPolymorphism, Triple) {
    Triple* triple = new Triple();

    triple->First();
    triple->Second();
    triple->Third();

    TrapObject<Triple::N>(*triple, &Trap);

    triple->First();
    triple->Second();
    triple->Third();

    ASSERT_EQ(buffer.str(), std::string("First\nSecond\nThird\nTrap\nTrap\nTrap\n"));
}

TEST_F(TestPolymorphism, TripleNotWhole) {
    Triple* triple = new Triple();

    triple->First();
    triple->Second();
    triple->Third();

    TrapObject<2>(*triple, &Trap);

    triple->First();
    triple->Second();
    // triple->Third(); // SEGFAULT

    ASSERT_EQ(buffer.str(), std::string("First\nSecond\nThird\nTrap\nTrap\n"));
}

TEST_F(TestPolymorphism, GuardedTriple) {
    GuardedTriple* triple = new GuardedTriple();

    triple->CallAll();
    TrapObject<GuardedTriple::N>(*triple, &Trap);
    triple->CallAll();

    ASSERT_EQ(buffer.str(), std::string("Public\nProtected\nPrivate\nTrap\nTrap\nTrap\n"));
}

TEST_F(TestPolymorphism, NonVoidReturn) {
    ValueReturning* returning = new ValueReturning();

    ASSERT_EQ(returning->ReturnValue(), 42);
    TrapObject<ValueReturning::N>(*returning, &TrapInt);
    ASSERT_EQ(returning->ReturnValue(), TrapInt());
}

TEST_F(TestPolymorphism, TypeSlaughter1) {
    ValueReturning* returning = new ValueReturning();

    ASSERT_EQ(returning->ReturnValue(), 42);
    TrapObject<ValueReturning::N>(*returning, &Trap);
    ASSERT_NE(returning->ReturnValue(), 42);
    ASSERT_EQ(buffer.str(), std::string("Trap\n"));
}


TEST_F(TestPolymorphism, TypeSlaughter2) {
    ValueReturning* returning = new ValueReturning();

    ASSERT_EQ(returning->ReturnValue(), 42);
    TrapObject<ValueReturning::N>(*returning, &Sum);
    ASSERT_NE(returning->ReturnValue(), 42);
}

#define CALL(I) huge->Func##I()
#define CALL_ALL() \
    CALL(0); CALL(1); CALL(2); CALL(3); CALL(4); CALL(5); CALL(6); CALL(7); CALL(8); CALL(9); \
    CALL(10); CALL(11); CALL(12); CALL(13); CALL(14); CALL(15); CALL(16); CALL(17); CALL(18); CALL(19); \
    CALL(20); CALL(21); CALL(22); CALL(23); CALL(24); CALL(25); CALL(26); CALL(27); CALL(28); CALL(29); \
    CALL(30); CALL(31); CALL(32); CALL(33); CALL(34); CALL(35); CALL(36); CALL(37); CALL(38); CALL(39); \
    CALL(40); CALL(41); CALL(42); CALL(43); CALL(44); CALL(45); CALL(46); CALL(47); CALL(48); CALL(49); \
    CALL(50); CALL(51); CALL(52); CALL(53); CALL(54); CALL(55); CALL(56); CALL(57); CALL(58); CALL(59); \
    CALL(60); CALL(61); CALL(62); CALL(53); CALL(64); CALL(65); CALL(66); CALL(67); CALL(68); CALL(69); \
    CALL(70); CALL(71); CALL(72); CALL(63); CALL(74); CALL(75); CALL(76); CALL(77); CALL(78); CALL(79); \
    CALL(80); CALL(81); CALL(82); CALL(73); CALL(84); CALL(85); CALL(86); CALL(87); CALL(88); CALL(89); \
    CALL(90); CALL(91); CALL(92); CALL(83); CALL(94); CALL(95); CALL(96); CALL(97); CALL(98); CALL(99)

TEST_F(TestPolymorphism, Huge) {
    Huge* huge = new Huge();
    std::string result;
    
    CALL_ALL();
    for (size_t i = 0; i < Huge::N; ++i) {
        result += (std::to_string(i) + '\n');
    }

    TrapObject<Huge::N>(*huge, &Trap);

    CALL_ALL();
    for (size_t i = 0; i < Huge::N; ++i) {
        result += "Trap\n";
    }

    ASSERT_EQ(buffer.str(), result);
}
