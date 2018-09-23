#ifndef DEADLOCK_H
#define DEADLOCK_H

#include <mutex>

class Toy
{
public:
  Toy(std::string n) : name(n) {}
  std::string name;
  std::mutex m;
};

class Kid
{
  std::string name;

public:
  Kid(std::string n) : name(n) {}
  void play_drums(Toy &toy_part1, Toy &toy_part2)
  {
    static std::mutex cout_mutex;

    std::lock_guard<std::mutex> lock_toy1(toy_part1.m);
    {
      std::lock_guard<std::mutex> lock(cout_mutex);
      std::cout << name << " took the " << toy_part1.name << std::endl;
    }
    std::lock_guard<std::mutex> lock_toy2(toy_part2.m);
    {
      std::lock_guard<std::mutex> lock(cout_mutex);
      std::cout << name << " took also the " << toy_part2.name << std::endl;
      std::cout << name << " is playing drums" << std::endl;
    }
    /*
    std::lock(toy_part1.m,toy_part2.m);
    std::lock_guard<std::mutex> lock_toy1(toy_part1.m,std::adopt_lock);
    std::lock_guard<std::mutex> lock_toy2(toy_part2.m,std::adopt_lock);
    std::lock_guard<std::mutex> lock_toy2(toy_part2.m);
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout<<name << " is playing drums" << std::endl;
    }
    */
  }
};

#endif // DEADLOCK_H
