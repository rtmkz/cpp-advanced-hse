#pragma once

#include <string>

// Should not allow reuse and yell under sanitizers.
// Fix the interface and implementation.
// AwesomeCallback should add "awesomeness".

class OneTimeCallback {
public:
    OneTimeCallback() {}
    virtual ~OneTimeCallback() = default;
    virtual std::string operator()() const && = 0;
};

// Implement ctor, operator(), maybe something else...
class AwesomeCallback : public OneTimeCallback {
public:
    AwesomeCallback(const std::string& s) : name_(s) {}
    
    virtual std::string operator()() const && override {
        std::string s = name_ + "awesomeness";
        delete this;
        return s;
    }

private:
    std::string name_;
};
