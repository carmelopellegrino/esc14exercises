#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

int main()
{
  std::mutex m;
  for (int n = 0; n < 10; ++n)
    {
      std::thread worker([&](int n){m.lock(); std::cout << "I'm thread " << n << std::endl; m.unlock();}, n);
      worker.detach();
    }
  sleep(10);
}
