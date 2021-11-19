#include <mpsc_queue.h>

#include <benchmark/benchmark.h>

#include <thread>

static void BenchmarkPushPop(benchmark::State& state) {
    MPSCQueue<int> queue;

    for (auto _ : state) {
        queue.Push(42);
        queue.Pop();
    }
}

BENCHMARK(BenchmarkPushPop)->Unit(benchmark::kNanosecond);

BENCHMARK_MAIN();
