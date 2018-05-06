#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <thread>

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

int main()
{
    parallel_accumulate();
}
