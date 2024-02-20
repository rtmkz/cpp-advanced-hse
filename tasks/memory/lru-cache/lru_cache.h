#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
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

    void Update(const std::string& key);

    void Pop();

    void Print() {
        for (auto it : pos) {
            std::cout << it.first << ' ' << it.second -> value << '\n';
        }
        std::cout << '\n';
    }
private:
    std::shared_ptr<Node> head, tail;
    size_t capacity;
    std::unordered_map <std::string, std::shared_ptr<Node>> pos;
};
