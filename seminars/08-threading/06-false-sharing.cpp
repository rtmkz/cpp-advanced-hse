#include "timer.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

constexpr unsigned kLimit = 10'000'000;
constexpr unsigned kNumThreads = 12;

struct Counter {
public:
    void Increment() {
        value_ = value_ + 1;
    }

    unsigned Value() {
        return value_;
    }

private:
    std::atomic<unsigned> value_ = 0;
};

void Slow() {
    timer::Timer timer;

    std::array<Counter, kNumThreads> counters{};

    std::vector<std::thread> workers;

    for (unsigned i = 0; i < kNumThreads; ++i) {
        workers.emplace_back([i, &counters] {
            for (size_t pos = 0; pos < kLimit; ++pos) {
                counters[i].Increment();
            }
        });
    }

    for (std::thread& t : workers) {
        t.join();
    }

    for (auto& counter : counters) {
        assert(counter.Value() == kLimit);
    }

    std::cout << "elapsed: " << timer.Elapsed() << std::endl;
}

template <typename T, size_t Alignment>
struct alignas(Alignment) AlignedValue : public T {
};

constexpr size_t kCacheLineSize = 64;

void Fast() {
    timer::Timer timer;

    unsigned num_threads = kNumThreads;
    std::array<AlignedValue<Counter, kCacheLineSize>, kNumThreads> counters{};

    std::vector<std::thread> workers;

    for (unsigned i = 0; i < num_threads; ++i) {
        workers.emplace_back([i, &counters] {
            for (size_t pos = 0; pos < kLimit; ++pos) {
                counters[i].Increment();
            }
        });
    }

    for (std::thread& t : workers) {
        t.join();
    }

    for (auto& counter : counters) {
        assert(counter.Value() == kLimit);
    }

    std::cout << "elapsed: " << timer.Elapsed() << std::endl;
}

int main() {
    for (int rep = 0; rep < 3; ++rep) {
        std::cout << "slow ";
        Slow();
        std::cout << "fast ";
        Fast();
    }
}
