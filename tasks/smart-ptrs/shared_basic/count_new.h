#include <new>
#include <cstdlib>
#include <cassert>

class MemCounter {
public:
    class MemCounterCtorArg_ {};
    explicit MemCounter(MemCounterCtorArg_) {
        reset();
    }

private:
    MemCounter(MemCounter const&);
    MemCounter& operator=(MemCounter const&);

public:
    int outstanding_new;
    int new_called;
    int delete_called;
    int aligned_new_called;
    int aligned_delete_called;
    std::size_t last_new_size;
    std::size_t last_new_align;
    std::size_t last_delete_align;

    int outstanding_array_new;
    int new_array_called;
    int delete_array_called;
    int aligned_new_array_called;
    int aligned_delete_array_called;
    std::size_t last_new_array_size;
    std::size_t last_new_array_align;
    std::size_t last_delete_array_align;

public:
    void newCalled(std::size_t s) {
        assert(s);
        ++new_called;
        ++outstanding_new;
        last_new_size = s;
    }

    void alignedNewCalled(std::size_t s, std::size_t a) {
        newCalled(s);
        ++aligned_new_called;
        last_new_align = a;
    }

    void deleteCalled(void* p) {
        assert(p);
        --outstanding_new;
        ++delete_called;
    }

    void alignedDeleteCalled(void* p, std::size_t a) {
        deleteCalled(p);
        ++aligned_delete_called;
        last_delete_align = a;
    }

    void newArrayCalled(std::size_t s) {
        ++outstanding_array_new;
        ++new_array_called;
        last_new_array_size = s;
    }

    void alignedNewArrayCalled(std::size_t s, std::size_t a) {
        newArrayCalled(s);
        ++aligned_new_array_called;
        last_new_array_align = a;
    }

    void deleteArrayCalled(void* p) {
        assert(p);
        --outstanding_array_new;
        ++delete_array_called;
    }

    void alignedDeleteArrayCalled(void* p, std::size_t a) {
        deleteArrayCalled(p);
        ++aligned_delete_array_called;
        last_delete_array_align = a;
    }

    void reset() {
        outstanding_new = 0;
        new_called = 0;
        delete_called = 0;
        aligned_new_called = 0;
        aligned_delete_called = 0;
        last_new_size = 0;
        last_new_align = 0;

        outstanding_array_new = 0;
        new_array_called = 0;
        delete_array_called = 0;
        aligned_new_array_called = 0;
        aligned_delete_array_called = 0;
        last_new_array_size = 0;
        last_new_array_align = 0;
    }

    bool checkOutstandingNewEq(int n) const {
        return n == outstanding_new;
    }
};

inline MemCounter* getGlobalMemCounter() {
    static MemCounter counter((MemCounter::MemCounterCtorArg_()));
    return &counter;
}

MemCounter& globalMemCounter = *getGlobalMemCounter();

void* operator new(std::size_t s) {
    getGlobalMemCounter()->newCalled(s);
    void* ret = std::malloc(s);
    return ret;
}

void operator delete(void* p) noexcept {
    getGlobalMemCounter()->deleteCalled(p);
    std::free(p);
}

void* operator new[](std::size_t s) {
    getGlobalMemCounter()->newArrayCalled(s);
    return operator new(s);
}

void operator delete[](void* p) noexcept {
    getGlobalMemCounter()->deleteArrayCalled(p);
    operator delete(p);
}

void* operator new(std::size_t s, std::align_val_t av) {
    const std::size_t a = static_cast<std::size_t>(av);
    getGlobalMemCounter()->alignedNewCalled(s, a);
    void* ret;
    posix_memalign(&ret, a, s);
    if (ret == nullptr)
        return ret;
}

void operator delete(void* p, std::align_val_t av) noexcept {
    const std::size_t a = static_cast<std::size_t>(av);
    getGlobalMemCounter()->alignedDeleteCalled(p, a);
    if (p) {
        ::free(p);
    }
}

void* operator new[](std::size_t s, std::align_val_t av) {
    const std::size_t a = static_cast<std::size_t>(av);
    getGlobalMemCounter()->alignedNewArrayCalled(s, a);
    return operator new(s, av);
}

void operator delete[](void* p, std::align_val_t av) noexcept {
    const std::size_t a = static_cast<std::size_t>(av);
    getGlobalMemCounter()->alignedDeleteArrayCalled(p, a);
    return operator delete(p, av);
}