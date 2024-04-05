#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <memory>

struct Node {
    std::string key, value;
    std::shared_ptr<Node> prev, next;
    Node() : prev(nullptr), next(nullptr) {
    }
    Node(std::string key, std::string value) : key(key), value(value), prev(nullptr), next(nullptr) {
    }
};

class LruCache {
public:
    LruCache(size_t max_size);

    void Set(const std::string& key, const std::string& value);

    bool Get(const std::string& key, std::string* value);

    void Pop();

private:        
    using pss = std::pair<std::string, std::string>;

    int capacity;
    std::list<pss> list;
    std::unordered_map<std::string, std::list<pss>::iterator> pos;
};
