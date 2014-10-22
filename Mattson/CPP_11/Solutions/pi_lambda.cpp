/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

It uses the C++'11 threads utility (though in a "C" programming
style instead of a "proper" C++ style).

History: Written by Tim Mattson, 08/2013.

*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex m;
static long num_steps = 100000000;
double step;
double pi=0.0;

int main ()
{
   int i;
   unsigned long hw_thrds = std::thread::hardware_concurrency();

   std::vector<std::thread>threads(hw_thrds-1);

   for(int i=0; i<hw_thrds;i++) {
        threads[i]=std::thread([](int id, int nthreads){
           double x, sum=0.0;
           double step = 1.0/(double) num_steps;
           for (int i=id;i<= num_steps; i+=nthreads){
               x = (i-0.5)*step;
               sum = sum + 4.0/(1.0+x*x);
           }
           m.lock();
              pi += step * sum;
           m.unlock();
           return;
         },i,hw_thrds);
   }

   for(int id=0; id<hw_thrds;id++)
        threads[id].join();

   std::cout << "\n pi with " << num_steps << " is " << pi <<"\n";
}	  

