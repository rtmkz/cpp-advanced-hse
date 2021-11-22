#include "fiber.h"
#include "scheduler.h"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <functional>
#include <memory>

int main() {
    nanofibers::Scheduler scheduler;
    scheduler.Run([&] {
        scheduler.Spawn([&] {
            for (int i = 0; i < 10; ++i) {
                printf("Fiber #1 \n");
                scheduler.Yield();
            }
        });
        scheduler.Spawn([&] {
            for (int i = 0; i < 10; ++i) {
                printf("Fiber #2\n");
                scheduler.Yield();
            }
        });
        printf("Spawned 2 children\n");
    });
}
