#pragma once

class Task
{
public:
    enum class Priority { VeryHigh, High, Normal, Low, VeryLow };
    Task(std::chrono::steady_clock::duration duration, Priority priority)
        :mDuration(duration), mPriority(priority) {}
    auto remainingTime(std::chrono::steady_clock::time_point tp)
    {
        return mLastCall + mDuration - tp;
    }
    void call()
    {
        mLastCall = std::chrono::steady_clock::now();
        this->execute();
    }
    virtual ~Task() = default;
    virtual void execute() = 0;
private:
    std::chrono::steady_clock::duration mDuration;
    std::chrono::steady_clock::time_point mLastCall;
    Priority mPriority;
};

class FunctionTask : public Task
{
public:
    FunctionTask(std::chrono::steady_clock::duration duration, Priority priority,
        const std::function<void()>& callable) :
        mCallable(callable), Task(duration, priority) {}
    virtual void execute() override { mCallable(); }
private:
    std::function<void()> mCallable;
};

class TaskManager
{
public:
    using TaskPointer = std::unique_ptr<Task>;
    void callNext()
    {
        auto time = std::chrono::steady_clock::now();
        auto next = mTasks.front().get();
        for (auto&& x : mTasks)
            if (next->remainingTime(time) > x->remainingTime(time))
                next = x.get();
        std::this_thread::sleep_for(next->remainingTime(time));
        next->call();
    }
    void addTask(TaskPointer&& tsk)
    {
        mTasks.push_back(std::move(tsk));
    }
    void start()
    {
        while (mRunning)
            callNext();
    }
    void stop()
    {
        mRunning.store(false);
    }
private:
    std::atomic_bool mRunning;
    std::vector<TaskPointer> mTasks;
};
