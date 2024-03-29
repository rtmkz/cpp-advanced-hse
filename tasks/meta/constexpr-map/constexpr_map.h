#pragma once

#include <vector>

template<class K, class V, int MaxSize = 8>
class ConstexprMap {
public:
    constexpr ConstexprMap() {
        size_ = 0;
    }

    constexpr V& operator[](const K& key) {
        for (size_t i = 0; i < size_; i++) {
            if (arr_[i].first == key) {
                return arr_[i].second;
            }
        }
        if (size_ == MaxSize) {
            throw std::runtime_error("Key not found!");
        }
        arr_[size_].first = key;
        return arr_[size_++].second;
    }

    constexpr const V& operator[](const K& key) const {
        for (size_t i = 0; i < size_; i++) {
            if (arr_[i].first == key) {
                return arr_[i].second;
            }
        }
        throw std::runtime_error("Key not found!");
    }

    constexpr bool Erase(const K& key) {
        size_t pos = size_;
        for (size_t i = 0; i < size_; i++) {
            if (arr_[i].first == key) {
                pos = i;
                break;
            }
        }
        if (pos < size_) {
            while (pos + 1 < size_) {
                std::swap(arr_[pos].first, arr_[pos + 1].first);
                std::swap(arr_[pos].second, arr_[pos + 1].second);
                pos++;
            }
            size_--;
            return true;
        }
        return false;
    }

    constexpr bool Find(const K& key) const {
        for (size_t i = 0; i < Size(); i++) {
            if (arr_[i].first == key) {
                return true;
            }
        }
        return false;
    }

    constexpr size_t Size() const {
        return size_;
    }

    constexpr std::pair<K, V>& GetByIndex(size_t pos) {
        return arr_[pos];
    }

    constexpr const std::pair<K, V>& GetByIndex(size_t pos) const {
        return arr_[pos];
    }
private:
    std::array <std::pair<K, V>, MaxSize> arr_;
    size_t size_;
};
