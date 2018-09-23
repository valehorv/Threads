#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <thread>
#include "stack.h"
#include "queue.h"
#include <atomic>

#include "dispatcher.h"
#include "request.h"

#include "deadlock.h"

#include <csignal>
#include <thread>
#include <chrono>

using namespace std;

struct block_acumulate
{
    void operator()(std::vector<int>::iterator start, std::vector<int>::iterator end, int& result)
    {
        result = std::accumulate(start, end, result);
    }
};

void parallel_accumulate( )
{
    block_acumulate block;
    std::vector<int> elements{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout<< "Threads: " << std::thread::hardware_concurrency() << std::endl;

    const int block_size = 3;
    const int number_of_threads = elements.size()/block_size;

    std::vector<thread> threads(number_of_threads);
    std::vector<int> results(number_of_threads);

    std::vector<int>::iterator start = elements.begin();

    std::vector<int>::iterator next = start;

    for(int i=0; i<number_of_threads; i++)
    {
        std::advance(next, block_size );

        threads[i] = thread( block, start, next, std::ref(results[i]) );

        start = next;
    }
    for(int i=0; i<number_of_threads; i++)
    {
        threads[i].join();
    }

    int total=0;

    block(results.begin(), results.end(), total);

    std::cout<< "Total: " << total << std::endl;
}

void stack_func()
{
    threadsafe_stack stack;

    std::vector<thread> threads(6);

    for(int i=0; i<3; i++)
    {
        threads[i] = thread( &threadsafe_stack::push, &stack, i );
    }
    int popped = 0;

    for(int i=3; i<6; i++)
    {
        threads[i] = thread( &threadsafe_stack::pop, &stack, std::ref(popped) );
        std::cout << "Pop: " << popped << std::endl;
    }
    for(int i=0; i<6; i++)
    {
        threads[i].join();
    }
}

void
queue_func()
{
    ThreadSafeQueue queue;
    std::vector<thread> threads(20);
    std::mutex mut;

    std::atomic<int> result;

    for( int i=0; i< 5; i++)
    {
        threads[i] = thread( &ThreadSafeQueue::push, &queue, i);
    }
    for( int i=5; i< 10; i++)
    {
        threads[i] = thread( &ThreadSafeQueue::wait_pop_and_accumulate, &queue, std::ref(result));
    }
    for(int i=0; i<10; i++)
    {
        threads[i].join();
    }
    cout<< "Result: " << result << std::endl;
}

struct info
{
    int a;
    int b;
};

int
sum( int s, const info& element )
{
    return (s + element.a );
}

sig_atomic_t signal_caught = 0;
mutex log_mutex;

void sigint_handler(int sig)
{
    signal_caught = 1;
}

void log_func(string text)
{
    log_mutex.lock();
    cout << text << "\n";
    log_mutex.unlock();
}

int main()
{   
/*    std::vector<info> v ={{1,1}, {2,2}, {3,3}};

    auto s = std::accumulate( v.begin(), v.end(), 0, []( int s, const info& element )
    {
        return (s + element.a );
    } );
    std::cout<< "S: "<< s << std::endl;
*/
   // queue_func();
    // stack_func();
    //parallel_accumulate();
/*
    Dispatcher::init(10);

    cout << "Init threads.\n";

    int i = 0;
    Request* r = 0;
    while ( i < 50)
    {
        r = new Request();
        r->set_value(i);
        r->set_output(&log_func);
        Dispatcher::add_request(r);
        i++;
    }

    this_thread::sleep_for(chrono::seconds(5));

    Dispatcher::stop();
    */

    Toy drums(std::string("drums")), sticks(std::string("sticks"));
    Kid Johnny(std::string("Johnny")), Mike(std::string("Mike"));

    thread t1( &Kid::play_drums, &Johnny, std::ref(drums), std::ref(sticks) );
    thread t2( &Kid::play_drums, &Mike, std::ref(sticks), std::ref(drums) );

    t1.join();
    t2.join();
}
