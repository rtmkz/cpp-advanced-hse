#include <iostream>
#include <string>
#include <stdexcept>

class Holder {
 public:
    Holder(std::string value_) : value(std::move(value_)) {
        std::cout << "Holder( " << value << " )\n";
    }

    ~Holder() {
        std::cout << "~Holder( " << value << " )\n";
        throw std::runtime_error("Try to catch me");
    }

 private:
    std::string value;
};


void Foo()
{
    Holder foo{"Foo"};
}


int main()
{
    try {
        Foo();
    } catch (std::runtime_error& e) {
        std::cout << "Caught!\n";
    }
}

