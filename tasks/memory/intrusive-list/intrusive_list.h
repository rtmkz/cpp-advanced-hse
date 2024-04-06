#pragma once

#include <algorithm>
#include <iostream>
#include <cassert>

class ListHook {
public:
    ListHook() {
        prev = next = nullptr;
    }

    bool IsLinked() const {
        return next != nullptr;
    }

    void Unlink() {
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }
        prev = next = nullptr;
    }

    // Must unlink element from list
    ~ListHook() {
        Unlink();
    }

    ListHook(const ListHook&) = delete;

private:
    template <class T>
    friend class List;

    ListHook *prev, *next;
    // that helper function might be useful
    void LinkBefore(ListHook* other) {
        other->prev = prev;
        other->next = this;
        prev->next = other;
        prev = other;
    }
};

template <typename T>
class List {
public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        Iterator& operator++() {
            ptr_ = ptr_->next;
            return *this;
        }
        Iterator operator++(int) {
            ptr_ = ptr_->next;
            return ptr_->prev;
        }

        T& operator*() const {
            return *static_cast<T*>(ptr_);
        }
        T* operator->() const {
            return static_cast<T*>(ptr_);
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_ == rhs.ptr_;
        }
        bool operator!=(const Iterator& rhs) const {
            return ptr_ != rhs.ptr_;
        }

    private:
        friend class List;

        Iterator() = default;
        Iterator(ListHook* ptr_) : ptr_(ptr_) {
        }

        ListHook* ptr_;
    };

    List() {
        dummy_ = new ListHook();
        dummy_->next = dummy_->prev = dummy_;
    }
    List(const List&) = delete;
    List(List&& other) {
        std::swap(dummy_, other.dummy_);
        other.dummy_ = nullptr;
    }

    // must unlink all elements from list
    ~List() {
        while (!IsEmpty()) {
            dummy_->next->Unlink();
        }
    }

    List& operator=(const List&) = delete;
    List& operator=(List&& other) {
        std::swap(dummy_, other.dummy_);
        other.dummy_ = nullptr;
        return *this;
    }

    bool IsEmpty() const {
        return dummy_ == nullptr || dummy_->next == dummy_;
    }
    // that method is allowed to be O(n)
    size_t Size() const {
        size_t res = 0;
        ListHook* ptr = dummy_->next;
        while (ptr != dummy_) {
            res++;
            ptr = ptr->next;
        }
        return res;
    }

    // note that IntrusiveList doesn't own elements,
    // and never copies or moves T
    void PushBack(T* elem) {
        dummy_->LinkBefore(elem);
    }
    void PushFront(T* elem) {
        dummy_->next->LinkBefore(elem);
    }

    T& Front() {
        return *static_cast<T*>(dummy_->next);
    }
    const T& Front() const {
        return *static_cast<const T*>(dummy_->next);
    }

    T& Back() {
        return *static_cast<T*>(dummy_->prev);
    }
    const T& Back() const {
        return *static_cast<const T*>(dummy_->prev);
    }

    void PopBack() {
        Back().Unlink();
    }
    void PopFront() {
        Front().Unlink();
    }

    Iterator Begin() {
        return Iterator(dummy_->next);
    }
    Iterator End() {
        return Iterator(dummy_);
    }

    // complexity of this function must be O(1)
    Iterator IteratorTo(T* element) {
        return Iterator(element);
    }

private:
    ListHook* dummy_;
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}
