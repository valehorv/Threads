#include"queue.h"

void
ThreadSafeQueue::push(int elem)
{
    std::lock_guard<std::mutex> lk(m);
    queue.push(elem);
    cond.notify_one();
}

void
ThreadSafeQueue::wait_pop_and_accumulate(std::atomic<int>& popped)
{
    std::unique_lock<std::mutex> lk(m);
    cond.wait(lk, [this](){return !queue.empty();});
    popped += queue.front();
    queue.pop();
}
