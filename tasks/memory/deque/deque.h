#pragma once

#include <initializer_list>
#include <algorithm>
#include <deque>

#include <iostream>


class Block {
public:
    static const int kSize = 128;

    bool isFull() const {
        return size_ == kSize;
    }
    int size() const {
        return size_;
    }
    void clear() {
        front_ = end_ = size_ = 0;
    }
    void push_front(int val) {
        size_++;
        assert(size_ <= kSize);
        front_ = (front_ - 1 + kSize) % kSize;
        arr_[front_] = val;
    }
    void push_back(int val) {
        size_++;
        assert(size_ <= kSize);
        arr_[end_] = val;
        end_ = (end_ + 1) % kSize;
    }
    void pop_front() {
        size_--;
        front_ = (front_ + 1) % kSize;
    }
    void pop_back() {
        size_--;
        end_ = (end_ - 1 + kSize) % kSize;
    }
    int operator[](int i) const {
        return arr_[(front_ + i) % kSize];
    }
    int& operator[](int i) {
        return arr_[(front_ + i) % kSize];
    }

private:
    int front_{0}, end_{0}, size_{0};
    int arr_[kSize];
};

class Deque {
public:
    Deque() = default;
    Deque(const Deque& rhs) {
        data_ = rhs.data_;
        front_ = rhs.front_;
        end_ = rhs.end_;
        blocks_ = rhs.blocks_;
        cnt_ = rhs.cnt_;
        capacity_ = rhs.capacity_;
    }
    Deque(Deque&& rhs) {
        Swap(rhs);
        rhs.Clear();
    }
    explicit Deque(size_t size) {
        for (size_t i = 0; i < size; i++) {
            PushBack(0);
        }
    }

    Deque(std::initializer_list<int> list) {
        for (auto it : list) {
            PushBack(it);
        }
    }

    Deque& operator=(Deque rhs) {
        Swap(rhs);
        return *this;
    }

    int next(int id) {
        return (id + 1) % capacity_;
    }
    int prev(int id) {
        return (id - 1 + capacity_) % capacity_;
    }
    int pos(int id) const {
        return (id % capacity_ + capacity_) % capacity_;
    }

    void Swap(Deque& rhs) {
        std::swap(data_, rhs.data_);
        std::swap(front_, rhs.front_);
        std::swap(end_, rhs.end_);
        std::swap(blocks_, rhs.blocks_); 
        std::swap(cnt_, rhs.cnt_);
        std::swap(capacity_, rhs.capacity_);
    }

    void PushBack(int value) {
        cnt_++;
        if (!capacity_ || (data_[pos(end_)]->isFull() && blocks_ == capacity_)) { // capacity = 0 or deque is full
            Reallocate();
        }
        if (data_[pos(end_)]->isFull()) {
            end_++;
        }
        blocks_ += (data_[pos(end_)]->size() == 0);
        data_[pos(end_)]->push_back(value);
    }   

    void PopBack() {
        cnt_--;
        data_[pos(end_)]->pop_back();
        if (!data_[pos(end_)]->size()) {
            end_--;
            blocks_--;
        }
    }

    void PushFront(int value) {
        cnt_++;
        bool f = 0;
        if (!capacity_ || (data_[pos(front_)]->isFull() && blocks_ == capacity_)) { // capacity = 0 or deque is full
            Reallocate();
            f = 1;
        }
        if (data_[pos(front_)]->isFull()) {
            front_--;
        }
        blocks_ += (data_[pos(front_)]->size() == 0);
        data_[pos(front_)]->push_front(value);
    }

    void PopFront() {
        cnt_--;
        data_[pos(front_)]->pop_front();
        if (!data_[pos(front_)]->size()) {
            front_++;
            blocks_--;
        }
    }

    int& operator[](size_t ind) {
        if (ind < data_[pos(front_)]->size()) {
            return (*data_[pos(front_)])[ind];
        }
        ind -= data_[pos(front_)]->size();
        return (*data_[pos(front_ + 1 + ind / Block::kSize)])[ind % Block::kSize];
    }

    int operator[](size_t ind) const {
        if (ind < data_[pos(front_)]->size()) {
            return (*data_[pos(front_)])[ind];
        }
        ind -= data_[pos(front_)]->size();
        return (*data_[pos(front_ + 1 + ind / Block::kSize)])[ind % Block::kSize];
    }

    size_t Size() const {
        return cnt_;
    }

    void Clear() {
        for (int i = 0; i < capacity_; i++) {
            delete data_[i];
        }
        delete[] data_;
        front_ = end_ = blocks_ = cnt_ = capacity_ = 0;
    }

    void Reallocate() {
        if (!capacity_) {
            capacity_ = 1;
            Block *blocks = new Block[capacity_];
            data_ = new Block*[capacity_];
            for (int i = 0; i < capacity_; i++) {
                data_[i] = &blocks[i];
            }
        }
        else {
            Block** ptrs = new Block*[capacity_ * 2];
            Block* blocks = new Block[capacity_];
            std::swap(data_, ptrs);
            for (int i = 0; i < capacity_; i++) {
                std::swap(data_[i], ptrs[pos(front_ + i)]);
            }
            front_ = 0;
            end_ = capacity_ - 1;
            for (int i = capacity_; i < capacity_ * 2; i++) {
                data_[i] = &blocks[i - capacity_];
            }
            delete[] ptrs;
            capacity_ *= 2;
        }
    }

private:
    int front_{0};
    int end_{0};
    int blocks_{0}; // number of blocks
    int cnt_{0};
    int capacity_{0};
    Block** data_{nullptr};
};
