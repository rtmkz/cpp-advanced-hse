#include "lru_cache.h"

LruCache::LruCache(size_t max_size) : capacity_(max_size) {
}

void LruCache::Pop() {
    std::string& key = list_.front().first;
    pos_.erase(key);
    list_.pop_front();
}

void LruCache::Set(const std::string& key, const std::string& value) {
    if (pos_.count(key)) {
        list_.erase(pos_[key]);
    }
    list_.push_back({key, value});
    pos_[key] = --list_.end();
    if (pos_.size() > capacity_) LruCache::Pop();
}

bool LruCache::Get(const std::string& key, std::string* value) {
    if (pos_.count(key)) {
        *value = pos_[key] -> second;
        LruCache::Set(key, *value);
        return true;
    }
    return false;
}
