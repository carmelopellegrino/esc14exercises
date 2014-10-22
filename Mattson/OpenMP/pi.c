/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>

const static long num_steps = 100000000;
double step;

int main ()
{
	  double pi, sum = 0.0;
	  double start_time, run_time;

	  step = 1.0/(double) num_steps;

    //omp_set_num_threads(1);

	  start_time = omp_get_wtime();

    double sums[100];
    
    for (int i = 0; i < 100; ++i)
    {
      sums[i] = -1;
    }

    #pragma omp parallel
    {
      int ID = omp_get_thread_num();
      double local = 0.;

      int nthreads = omp_get_num_threads();

      int chunk = num_steps / nthreads;

      int range_start = ID * chunk;
      int range_stop = range_start + chunk;
      //printf("Thread %d\t\t min = %d, max = %d\n", ID, range_start, range_stop);
      range_stop = range_stop < num_steps ? range_stop : num_steps;

      for (int i = range_start; i < range_stop; ++i) {


      //for (int i = ID; i < num_steps; i += nthreads) {
        double x = (i-0.5)*step;
        local += 4.0/(1.0 + x*x);
      }
      sums[ID] = local;
    }


    int i = 0;
    do
    {
      sum += sums[i++];
    } while (sums[i] > 0);

	  pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  
