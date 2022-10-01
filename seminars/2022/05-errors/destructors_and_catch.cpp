#include <iostream>
#include <stdexcept>

class IntHolder {
 public:
    IntHolder(int value) : ptr(new int{value}) {
        std::cerr << "IntHolder(" << value << ")\n";
    }
    ~IntHolder() {
        std::cerr << "~IntHolder()\n";
        delete ptr;
    }

 private:
    int* ptr;
};

void MakeHolder(int input)
{
    IntHolder holder{input};
    throw std::runtime_error("Let's try memory leaks");
}

void wrapper()
{
    try {
        MakeHolder(42);
    } catch (std::bad_exception& e) { }
}

int main()
{
    int input{0};
    try {
        MakeHolder(input);
    } catch (std::logic_error& e) {
        // another exception type
    }
    // no destructor call without catching an exception, just terminates right now
    // memory leaks

    // uncomment the lines below to show the destructor call
//    catch (std::runtime_error& r) {
//        std::cerr << "caught the runtime_error\n";
//    }

    // nested catch
    try {
        wrapper();
    } catch (std::runtime_error& e) {
        std::cerr << "Caught!\n";
    }
}
