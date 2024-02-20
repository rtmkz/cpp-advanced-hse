#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

using std::string;

std::vector<std::unique_ptr<string>> Duplicate(const std::vector<std::shared_ptr<string>>& items) {
    std::vector<std::unique_ptr<string>> out;
    out.reserve(items.size());
    for (auto& it : items) {
        out.emplace_back(std::make_unique<string>(*it));
    }
    return out;
}

std::vector<std::shared_ptr<string>> DeDuplicate(
    const std::vector<std::unique_ptr<string>>& items) {
    std::vector<std::shared_ptr<string>> out;
    std::unordered_map<string, std::shared_ptr<string>> seen;
    for (auto& it : items) {
        if (!seen.count(*it))
            seen[*it] = std::make_shared<string>(*it);
        out.emplace_back(seen[*it]);
    }
    return out;
}
