#pragma once

#include "fiber.h"
#include "intrusive_list.h"
#include "scheduler.h"

namespace nanofibers {

class ConditionVariable {
public:
    void Wait() {
        Fiber* self = Scheduler::GetCurrentScheduler()->GetCurrentFiber();
        self->SetState(EState::Suspended);
        queue_.PushBack(self);
        this_fiber::Yield();
    }

    bool NotifyOne() {
        if (queue_.Empty()) {
            return false;
        }
        Fiber* fiber = queue_.PopFront();
        Scheduler::GetCurrentScheduler()->Schedule(fiber);
        return true;
    }

    void NotifyAll() {
        while (NotifyOne()) {
            // pass
        }
    }

private:
    IntrusiveList<Fiber> queue_;
};

class Mutex {
public:
    void Lock() {
        while (locked_) {
            queue_.Wait();
        }
        locked_ = true;
    }

    void Unlock() {
        locked_ = false;
        queue_.NotifyOne();
    }

private:
    bool locked_ = false;
    ConditionVariable queue_;
};

} // namespace nanofibers
