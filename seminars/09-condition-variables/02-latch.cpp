#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


class Latch {
public:
    Latch(int initial_value)
        : value_{initial_value}
    {}

    void Arrive() {
        std::lock_guard lock{mtx_};
        --value_;
        if (value_ == 0) {
            cv_.notify_all();
        }
    }

    void Wait() {
        std::unique_lock lock{mtx_};
        cv_.wait(lock, [this] {
            return value_ > 0;
        });
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    int value_ = 0;
};

int main() {
    int num_threads = 10;
    Latch latch{num_threads};

    std::vector<std::jthread> workers;
    for (int i = 0; i < num_threads; ++i) {
        workers.emplace_back([&latch] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            latch.Arrive();
        });
    }

    std::cerr << "Waiting " << num_threads << " threads...\n";
    latch.Wait();
    std::cerr << "Done!\n";
}
