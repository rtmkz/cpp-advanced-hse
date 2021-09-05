#pragma once

#include "sw_fwd.h"  // Forward declaration

#include <cstddef>  // std::nullptr_t

// https://en.cppreference.com/w/cpp/memory/shared_ptr
template <typename T>
class SharedPtr {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors, `operator=`-s, destructor

    SharedPtr();
    SharedPtr(std::nullptr_t);
    explicit SharedPtr(T* ptr);

    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other);

    // Aliasing constructor
    // #8 from https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    SharedPtr(const SharedPtr& other, T* ptr);

    // Promote `WeakPtr`
    // #11 from https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    explicit SharedPtr(const WeakPtr<T>& other);

    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other);

    ~SharedPtr();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    void Reset();
    void Reset(T* ptr);
    void Swap(SharedPtr& other);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const;
    T& operator*() const;
    T* operator->() const;
    size_t UseCount() const;
    operator bool() const;
};

// Allocate memory only once
template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args);
