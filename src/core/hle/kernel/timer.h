// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "core/hle/kernel/kernel.h"

namespace Kernel {

class Timer final : public WaitObject {
public:
    /**
     * Creates a timer
     * @param reset_type ResetType describing how to create the timer
     * @param name Optional name of timer
     * @return The created Timer
     */
    static SharedPtr<Timer> Create(ResetType reset_type, std::string name = "Unknown");

    std::string GetTypeName() const override {
        return "Timer";
    }
    std::string GetName() const override {
        return name;
    }

    static const HandleType HANDLE_TYPE = HandleType::Timer;
    HandleType GetHandleType() const override {
        return HANDLE_TYPE;
    }

    ResetType reset_type; ///< The ResetType of this timer

    bool signaled;    ///< Whether the timer has been signaled or not
    std::string name; ///< Name of timer (optional)

    u64 initial_delay;  ///< The delay until the timer fires for the first time
    u64 interval_delay; ///< The delay until the timer fires after the first time

    bool ShouldWait(Thread* thread) const override;
    void Acquire(Thread* thread) override;

    void WakeupAllWaitingThreads() override;

    /**
     * Starts the timer, with the specified initial delay and interval.
     * @param initial Delay until the timer is first fired
     * @param interval Delay until the timer is fired after the first time
     */
    void Set(s64 initial, s64 interval);

    void Cancel();
    void Clear();

    /**
     * Signals the timer, waking up any waiting threads and rescheduling it
     * for the next interval.
     * This method should not be called from outside the timer callback handler,
     * lest multiple callback events get scheduled.
     */
    void Signal(int cycles_late);

private:
    Timer();
    ~Timer() override;

    /// Handle used as userdata to reference this object when inserting into the CoreTiming queue.
    Handle callback_handle;
};

/// Initializes the required variables for timers
void TimersInit();
/// Tears down the timer variables
void TimersShutdown();

} // namespace
