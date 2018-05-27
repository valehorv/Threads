#include "stack.h"

threadsafe_stack::threadsafe_stack() {}

threadsafe_stack::threadsafe_stack(const threadsafe_stack &other)
{
  std::lock_guard<std::mutex> lock(other.m);
  data = other.data;
}

void
threadsafe_stack::push(int new_value)
{
  std::lock_guard<std::mutex> lock(m);
  data.push(new_value);
}
/*
std::shared_ptr<int>
threadsafe_stack::pop()
{
  std::lock_guard<std::mutex> lock(m);
  if ( data.empty( ) )
  {
    throw empty_stack( );
  }
  std::shared_ptr<int> const result(std::make_shared<int>(data.top()));
  data.pop();
  return result;
}
*/

void
threadsafe_stack::pop(int &value)
{
  std::lock_guard<std::mutex> lock(m);
  if (data.empty())
  {
    throw empty_stack();
  }
  value = data.top();
  data.pop();
}

bool
threadsafe_stack::empty() const
{
  std::lock_guard<std::mutex> lock(m);
  return data.empty();
}


