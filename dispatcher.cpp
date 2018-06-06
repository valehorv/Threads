#include "dispatcher.h"
#include <iostream>

using namespace std;

queue<AbstractRequest *> Dispatcher::requests;
queue<Worker *> Dispatcher::workers;

mutex Dispatcher::requests_mutex;
mutex Dispatcher::workers_mutex;
vector<Worker *> Dispatcher::all_workers;
vector<thread *> Dispatcher::threads;

bool Dispatcher::init(int workers)
{
  thread *t = 0;
  Worker *w = 0;
  for (int i = 0; i < workers; ++i)
  {
    w = new Worker;
    all_workers.push_back(w);
    t = new thread(&Worker::run, w);
    threads.push_back(t);
  }
  return true;
}

bool Dispatcher::stop()
{
  for (int i = 0; i < all_workers.size(); ++i)
  {
    all_workers[i]->stop();
  }
  cout << "Stopped workers\n";

  for (int i = 0; i < threads.size(); ++i)
  {
    threads[i]->join();
  }
  cout << "Joined threads\n";

  return true;
}

void Dispatcher::add_request(AbstractRequest *request)
{
  workers_mutex.lock();
  if (!workers.empty())
  {
    Worker *worker = workers.front();
    worker->set_request(request);
    condition_variable *cv;
    worker->get_condition(cv);
    cv->notify_one();
    workers.pop();
    workers_mutex.unlock();
  }
  else
  {
    workers_mutex.unlock();
    requests_mutex.lock();
    requests.push(request);
    requests_mutex.unlock();
  }
}

bool Dispatcher::add_worker(Worker *worker)
{
  bool wait = true;
  requests_mutex.lock();
  if (!requests.empty())
  {
    AbstractRequest *request = requests.front();
    worker->set_request(request);
    requests.pop();
    wait = false;
    requests_mutex.unlock();
  }
  else
  {
    requests_mutex.unlock();
    workers_mutex.lock();
    workers.push(worker);
    workers_mutex.unlock();
  }
  return wait;
}
