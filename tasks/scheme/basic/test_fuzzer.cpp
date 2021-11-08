#include "../scheme.h"
#include "../test/scheme_test.h"
#include "../test/fuzzer.h"
// #include "allocations_checker.h"

#include <iostream>

constexpr uint32_t kShotsCount = 100000;

TEST_CASE("Fuzzing") {
    Fuzzer fuzzer;
    Interpreter interpreter;

    // allocations_count.store(0);
    // deallocations_count.store(0);

    for (uint32_t i = 0; i < kShotsCount; ++i) {
        try {
            auto req = fuzzer.Next();
            // std::cerr << req << std::endl;  // uncomment to debug, random is deterministic
            interpreter.Run(req);
        } catch (const SyntaxError&) {
        } catch (const RuntimeError&) {
        } catch (const NameError&) {
        }
    }

    // int alloc_count = allocations_count.load(), dealloc_count = deallocations_count.load();

    // std::cerr << "Allocations: " << alloc_count << "\n";
    // std::cerr << "Deallocations: " << dealloc_count << "\n";

    // If falling here:
    // - if it happens on advanced task, check that you invoke GC after each command
    // - if it happens on basic task, contact us
    // REQUIRE(alloc_count - dealloc_count <= 10'000);
}
