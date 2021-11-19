#include <gtest/gtest.h>

#include <mpsc_queue.h>

#include <algorithm>
#include <unordered_set>
#include <thread>

TEST(TestMPSCQueue, PushPop) {
    MPSCQueue<int> queue;

    queue.Push(1);
    queue.Push(2);

    auto [value, ok] = queue.Pop();
    EXPECT_TRUE(ok);
    EXPECT_EQ(2, value);

    std::tie(value, ok) = queue.Pop();
    EXPECT_TRUE(ok);
    EXPECT_EQ(1, value);

    std::tie(value, ok) = queue.Pop();
    EXPECT_FALSE(ok);
}

TEST(TestMPSCQueue, SingleThread) {
    MPSCQueue<int> queue;

    std::vector<int> result;
    for (int i = 0; i < 1024; i++) {
        result.push_back(i);
        queue.Push(i);
    }

    std::vector<int> dequeued;
    queue.DequeueAll([&](int j) { dequeued.push_back(j); });

    std::reverse(dequeued.begin(), dequeued.end());
    EXPECT_EQ(dequeued, result);
}

TEST(TestMPSCQueue, Destructor) {
    MPSCQueue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
}

TEST(TestMPSCQueue, Threaded) {
    std::unordered_set<int> all_dequeued;
    MPSCQueue<int> queue;

    std::atomic<bool> stop = false;
    std::thread dequeuer([&] {
        auto save = [&](int value) {
            auto [it, ok] = all_dequeued.emplace(value);
            EXPECT_TRUE(ok);
        };

        while (!stop) {
            queue.DequeueAll(save);
        }

        queue.DequeueAll(save);
    });

    constexpr int kN = 100000;
    for (int i = 0; i < kN; i++) {
        queue.Push(i);
    }

    stop = true;
    dequeuer.join();
    EXPECT_EQ(kN, all_dequeued.size());
}
