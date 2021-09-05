#pragma once

#include <cstddef>  // std::nullptr_t

struct Slug {};

// Primary template
template <typename T, typename Deleter = Slug>
class UniquePtr {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors, `operator=`-s, destructor

    explicit UniquePtr(T* ptr = nullptr);

    UniquePtr(UniquePtr&& other);

    UniquePtr& operator=(UniquePtr&& other);
    UniquePtr& operator=(std::nullptr_t);

    ~UniquePtr();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    T* Release();
    void Reset(T* ptr = nullptr);
    void Swap(UniquePtr& other);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const;
    Deleter& GetDeleter();
    const Deleter& GetDeleter() const;
    explicit operator bool() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Single-object dereference operators

    T& operator*() const;
    T* operator->() const;
};

// Specialization for arrays
template <typename T, typename Deleter>
class UniquePtr<T[], Deleter>;
