#include <iostream>
#include <string>
#include <stdexcept>

class Holder {
 public:
    Holder(std::string value_) : value(std::move(value_)) {
        std::cerr << "Holder( " << value << " )\n";
    }

    ~Holder() {
        std::cerr << "~Holder( " << value << " )\n";
    }

 private:
    std::string value;
};

class ThrowHolder {
 public:
    ThrowHolder(std::string value_) : value(std::move(value_)) {
        std::cerr << "ThrowHolder( " << value << " )\n";
        throw std::runtime_error("Bad constructor");
    }

    ~ThrowHolder() {
        std::cerr << "~ThrowHolder( " << value << " )\n";
    }

 private:
    std::string value;
};

class Pair {
 public:
    Pair(std::string value) : h(value), th(value) {
        std::cerr << "Pair()\n";
    }

    ~Pair() {
        std::cerr << "~Pair()\n";
    }

 private:
    Holder h;
    ThrowHolder th;
};

int main()
{
    try {
        Pair summer{"summer"};
    } catch (std::runtime_error& e) {
        std::cerr << "Caught!\n";
    }
}
