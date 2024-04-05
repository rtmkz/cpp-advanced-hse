#include "lru_cache.h"

LruCache::LruCache(size_t max_size) : capacity(max_size) {
}

void LruCache::Pop() {
    std::string& key = list.front().first;
    pos.erase(key);
    list.pop_front();
}

void LruCache::Set(const std::string& key, const std::string& value) {
    if (pos.count(key)) {
        list.erase(pos[key]);
    }
    list.push_back({key, value});
    pos[key] = --list.end();
    if (pos.size() > capacity) LruCache::Pop();
}

bool LruCache::Get(const std::string& key, std::string* value) {
    if (pos.count(key)) {
        *value = pos[key] -> second;
        LruCache::Set(key, *value);
        return true;
    }
    return false;
}
