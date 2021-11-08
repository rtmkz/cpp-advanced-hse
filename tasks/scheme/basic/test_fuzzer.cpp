#include "../scheme.h"
#include "../test/scheme_test.h"
#include "../test/fuzzer.h"
#include "allocations_checker.h"

#include <iostream>

constexpr uint32_t kShotsCount = 100000;

TEST_CASE("Fuzzing") {
    Fuzzer fuzzer;
    Interpreter interpreter;

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

    // If falling here:
    // - if it happens on advanced task, check that you invoke GC after each command
    // - if it happens on basic task, contact us
    REQUIRE(allocations_count.load() - deallocations_count.load() <= 10'000);
}
