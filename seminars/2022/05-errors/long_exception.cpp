#include <iostream>
#include <string>
#include <stdexcept>

class Holder {
 public:
    Holder(std::string value_) : value(std::move(value_)) {
        std::cout << "Holder( " << value << " )\n";
    }

    ~Holder() {
        std::cout << "~IntHolder( " << value << " )\n";
    }

 private:
    std::string value;
};

void Foo()
{
    Holder foo{"Foo"};
    throw std::runtime_error("Catch me");
}


void Bar()
{
    Holder bar{"Bar"};
    Foo();
}

void Invisible()
{
    Bar();

    // Will never be constructed.
    Holder invisible{"invisible"};
}

int main()
{
    try {
        Invisible();
    } catch (...) {
        std::cout << "Caught something\n";
    }
}
