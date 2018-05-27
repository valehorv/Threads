#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
    const char *what() const throw()
    {
    }
};

class threadsafe_stack {
private:
    std::stack<int> data;
    mutable std::mutex m;

public:
  threadsafe_stack();
  threadsafe_stack(const threadsafe_stack &other);
  threadsafe_stack &operator=(const threadsafe_stack &) = delete;
  void push(int new_value);
 // std::shared_ptr<int> pop();
  void pop(int &value);
  bool empty() const;
};
