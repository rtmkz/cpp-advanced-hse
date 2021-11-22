#pragma once

#include "context.h"
#include "stack.h"
#include "intrusive_list.h"

#include <cassert>
#include <climits>
#include <functional>
#include <cstddef>
#include <memory>
#include <cstdio>

namespace nanofibers {

class Fiber;

namespace this_fiber {
    Fiber* Get();
    void Yield();
    void Terminate();
}

////////////////////////////////////////////////////////////////////////////////

enum class EState {
    Created,
    Runnable,
    Finished,
};

class Fiber : public IntrusiveListItem<Fiber> {
    static constexpr size_t kDefaultStackSize = 4 * 4096;

public:
    explicit Fiber(std::function<void()> routine)
        : stack_{kDefaultStackSize}
        , routine_{std::move(routine)}
    {
        context_.rsp = stack_.Top();
        context_.rip = reinterpret_cast<void*>(Trampoline);
    }

    EState GetState() const {
        return state_;
    }

    void SetState(EState state) {
        state_ = state;
    }

    Context* GetContext() {
        return &context_;
    }

    void Run() {
        assert(GetState() == EState::Runnable);
        routine_();
        SetState(EState::Finished);
        this_fiber::Terminate();
    }

private:
    // Fiber entry point
    // Should be void(void)
    static void Trampoline() {
        this_fiber::Get()->Run();
    }

private:
    EState state_ = EState::Created;
    Context context_ = {};
    Stack stack_;
    std::function<void()> routine_;
};

} // namespace nanofibers
