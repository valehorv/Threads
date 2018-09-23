#ifndef WORKER_H
#define WORKER_H

#include "abstract_request.h"
#include <condition_variable>
#include <mutex>

using namespace std;

class Worker
{
  condition_variable cv;
  mutex mtx;
  unique_lock<mutex> ulock;
  AbstractRequest *request;
  bool running;
  bool ready;

public:
  Worker()
  {
    running = true;
    ready = false;
    ulock = unique_lock<mutex>(mtx);
  }
  void run();
  void stop() { running = false; }
  void set_request(AbstractRequest *request)
  {
    this->request = request;
    ready = true;
  }
  void get_condition(condition_variable* &cv);
};

#endif // WORKER_H
