#include "worker.h"
#include "dispatcher.h"
#include <chrono>

using namespace std;

void Worker::get_condition(condition_variable *&cv) { cv = &(this)->cv; }

void Worker::run()
{
  while (running)
  {
    if (ready)
    {
      ready = false;
      request->process();
    }
    if (Dispatcher::add_worker(this))
    {
      while (!ready && running)
      {
        if (cv.wait_for(ulock, chrono::seconds(1)) == cv_status::timeout)
        {
        }
      }
    }
  }
}
