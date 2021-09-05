#pragma once

#include "sw_fwd.h"  // Forward declaration

// https://en.cppreference.com/w/cpp/memory/weak_ptr
template <typename T>
class WeakPtr {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors, `operator=`-s, destructor

    WeakPtr();

    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other);

    // Demote `SharedPtr`
    // #2 from https://en.cppreference.com/w/cpp/memory/weak_ptr/weak_ptr
    WeakPtr(const SharedPtr<T>& other);

    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other);

    ~WeakPtr();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    void Reset();
    void Swap(WeakPtr& other);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    size_t UseCount() const;
    bool Expired() const;
    SharedPtr<T> Lock() const;
};
