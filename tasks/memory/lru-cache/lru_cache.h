#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <memory>


class LruCache {
public:
    LruCache(size_t max_size);

    void Set(const std::string& key, const std::string& value);

    bool Get(const std::string& key, std::string* value);

    void Pop();

private:        
    using List = std::list<std::pair<std::string, std::string>>;

    int capacity_;
    List list_;
    std::unordered_map<std::string, List::iterator> pos_;
};
