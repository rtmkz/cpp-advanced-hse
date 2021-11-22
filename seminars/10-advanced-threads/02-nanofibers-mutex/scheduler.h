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

    // Pause current fiber and switch to scheduler
    void Yield() {
        Switch(current_fiber_->GetContext(), &main_context_);
    }

    // Kill current fiber
    void Terminate() {
        // Q: Why can't we just delete current_fiber_ here?
        current_fiber_->SetState(EState::Finished);
        Switch(current_fiber_->GetContext(), &main_context_);
    }

    // Run routine and spawned fibers
    void Run(std::function<void()> routine) {
        current_scheduler = this;

        Spawn(std::move(routine));
        while (!queue_.Empty()) {
            Fiber* fiber = queue_.PopFront();

            current_fiber_ = fiber;
            Switch(&main_context_, fiber->GetContext());

            switch (fiber->GetState()) {
            case EState::Runnable:
                Schedule(fiber);
                break;
            case EState::Suspended:
                break;
            case EState::Finished:
                delete fiber;
                break;
            }
        }
    }

    Fiber* GetCurrentFiber() {
        return current_fiber_;
    }

    static Scheduler* GetCurrentScheduler() {
        return current_scheduler;
    }

private:
    void Switch(Context* from, Context* to) {
        if (SaveContext(from) == ESaveContextResult::Saved) {
            JumpContext(to);
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
    Scheduler::GetCurrentScheduler()->Terminate();
}

} // namespace this_fiber

} // namespace nanofibers
