#pragma once

#include "context.h"
#include "fiber.h"
#include "intrusive_list.h"

#include <cassert>

namespace nanofibers {

class Scheduler {
public:
    void Spawn(std::function<void()> routine) {
        Fiber* fiber = new Fiber{std::move(routine)};
        Schedule(fiber);
    }

    // Put fiber to the queue
    void Schedule(Fiber* fiber) {
        fiber->SetState(EState::Runnable);
        queue_.PushBack(fiber);
    }

    // Pause current fiber and let other fibers to run
    void Yield() {
        Schedule(current_fiber_);
        SwitchToNextFiber(current_fiber_->GetContext());
    }

    // Kill current fiber
    void TerminateFiber() {
        assert(current_fiber_->GetState() == EState::Finished);
        JumpContext(&main_context_);
        // Q: Why can't we just delete current_fiber_ here?
    }

    // Run routine and spawned fibers
    void Run(std::function<void()> routine) {
        current_scheduler = this;

        Spawn(std::move(routine));
        while (!queue_.Empty()) {
            SwitchToNextFiber(&main_context_);
        }
    }

    Fiber* GetCurrentFiber() {
        return current_fiber_;
    }

    static Scheduler* GetCurrentScheduler() {
        return current_scheduler;
    }

private:
    void SwitchToNextFiber(Context* current) {
        Fiber* fiber = queue_.PopFront();
        if (SaveContext(current) == ESaveContextResult::Saved) {
            current_fiber_ = fiber;
            JumpContext(fiber->GetContext());
        }
        if (current_fiber_->GetState() == EState::Finished) {
            delete current_fiber_;
        }
    }

private:
    inline static Scheduler* current_scheduler = nullptr;

private:
    IntrusiveList<Fiber> queue_;
    Context main_context_;
    Fiber* current_fiber_ = nullptr;
};

////////////////////////////////////////////////////////////////////////////////

namespace this_fiber {

void Yield() {
    Scheduler::GetCurrentScheduler()->Yield();
}

Fiber* Get() {
    return Scheduler::GetCurrentScheduler()->GetCurrentFiber();
}

void Terminate() {
    Scheduler::GetCurrentScheduler()->TerminateFiber();
}

} // namespace this_fiber

} // namespace nanofibers
