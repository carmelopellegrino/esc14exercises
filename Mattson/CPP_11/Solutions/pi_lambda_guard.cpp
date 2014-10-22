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
   unsigned long nthrds = std::thread::hardware_concurrency();

   std::vector<std::thread>threads(nthrds-1);

   for(int id=0; id<nthrds;id++) {
        threads[id]=std::thread([id,nthrds]{

           double x, sum=0.0;
           double step = 1.0/(double) num_steps;
           for (int i=id;i<= num_steps; i+=nthrds){
               x = (i-0.5)*step;
               sum = sum + 4.0/(1.0+x*x);
           }
           std::lock_guard<std::mutex> guard(m);
           pi += step * sum;

         });
   }

   for(int id=0; id<nthrds;id++) threads[id].join();

   std::cout << "\n pi with " << num_steps << " is " << pi <<"\n";
}	  

