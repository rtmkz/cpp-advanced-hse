#pragma once

#include <string>
#include <algorithm>
#include <cstring>

class StringView {

public:
    StringView(const std::string& s, size_t start = 0, size_t len = std::string::npos) {
        head = &s.c_str()[start];
        size_ = std::min(len, s.size() - start);
    }
    StringView(const char* s) {
        head = s;
        size_ = strlen(s);
    }
    StringView(const char* s, size_t len) {
        head = s;
        size_ = len;
    }
    char operator[](int i) const {
        return *(head + i);
    }
    size_t Size() const {
        return size_;
    }

private:
    const char* head;
    size_t size_;
};
