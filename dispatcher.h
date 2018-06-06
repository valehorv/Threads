#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "abstract_request.h"
#include "worker.h"
#include <queue>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class Dispatcher
{
    static queue<AbstractRequest*> requests;
    static queue<Worker*> workers;
    static mutex requests_mutex;
    static mutex workers_mutex;
    static vector<Worker*> all_workers;
    static vector<thread*> threads;

public:
    static bool init(int workers);
    static bool stop();
    static void add_request(AbstractRequest* request);
    static bool add_worker(Worker* worker);
};

#endif // DISPATCHER_H
