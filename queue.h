#ifndef QUEUE_H
#define QUEUE_H

#include<queue>
#include<condition_variable>
#include<atomic>

class ThreadSafeQueue
{
private:
    std::queue<int> queue;
    std::condition_variable cond;
    std::mutex m;
public:
    ThreadSafeQueue(){}
    void push( int );
    void front(  );
    void wait_pop_and_accumulate( std::atomic<int>& );
};

#endif // QUEUE_H
