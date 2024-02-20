#include "lru_cache.h"

LruCache::LruCache(size_t max_size) : capacity(max_size) {
}

void LruCache::Update(const std::string& key) {
    std::shared_ptr<Node> cur = pos[key];
    if (cur == tail) return;
    if (cur == head) {
        head = head -> next;
        tail -> next = cur;
        tail -> next -> prev = tail;
        tail = tail -> next;
    }
    else {
        cur -> prev -> next = cur -> next;
        cur -> next -> prev = cur -> prev;
        tail -> next = cur;
        tail -> next -> prev = tail;
        tail = tail -> next;
    }
}
void LruCache::Pop() {
    pos.erase(head -> key);
    head = head -> next;
}
void LruCache::Set(const std::string& key, const std::string& value) {
    if (pos.count(key)) {
        pos[key] -> value = value;
        LruCache::Update(key);
        return;
    }
    if (pos.size() == 0) {
        head = tail = std::make_shared<Node>(key, value);
    }
    else {
        tail -> next = std::make_shared<Node>(key, value);
        tail -> next -> prev = tail;
        tail = tail -> next;
    }
    pos[key] = tail;
    if (pos.size() > capacity) LruCache::Pop();
}

bool LruCache::Get(const std::string& key, std::string* value) {
    if (pos.count(key)) {
        *value = pos[key] -> value;
        LruCache::Update(key);
        return true;
    }
    return false;
}
