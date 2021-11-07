#include <iostream>
#include <syncstream>
#include <thread>

void Worker(int idx) {
    std::osyncstream{std::cout} << "Thread " << idx << " (id=" << std::this_thread::get_id() << ")\n";
}

int main() {
    std::thread t1{Worker, 0};
    std::jthread t2{Worker, 1};
    t1.join();
    // No need to join t2
}
