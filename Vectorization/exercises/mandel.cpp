/*
**  PROGRAM: Mandelbrot area
**
**  PURPOSE: Program to compute the area of a  Mandelbrot set.
**           Correct answer should be around 1.510659.
**           WARNING: this program may contain errors
**
**  USAGE:   Program runs without input ... just run the executable
**            
**  HISTORY: Written:  (Mark Bull, August 2011).
**           Changed "comples" to "d_comples" to avoid collsion with 
**           math.h complex type (Tim Mattson, September 2011)
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>

#include "NativeVector.h"


#include<iostream>


using FLOAT =  float;

// using FLOAT = NativeVector<float>;
// constexpr int vsize = sizeof(FLOAT)/sizeof(float);



# define NPOINTS 1024
# define MAXITER 1024


struct d_complex{
   FLOAT r;
   FLOAT i;
};


void testpoint(struct d_complex);



int numoutside = 0;

float driver(int seed){


  //  constexpr FLOAT eps  =  nativeVector::zero<NativeVector<float>>() + 1.0e-5f;
  
  constexpr FLOAT eps = 1.0e-5f;
  
  //   Loop over grid of points in the complex plane which contains the Mandelbrot set,
  //   testing each point to see whether it is inside or outside the set.
  
  for (int i=0; i<NPOINTS; i++) {
    for (int j=0; j<NPOINTS; j++) {
      struct d_complex c;
      c.r = -2.0f+2.5f*(float)(i)/(float)(NPOINTS)+eps;
      c.i = 1.125f*(float)(j)/(float)(NPOINTS)+eps;
      testpoint(c);
    }
  }

  // Calculate area of set and error estimate and output the results
  
  auto area=2.0f*2.5f*1.125f*(float)(NPOINTS*NPOINTS-numoutside)/(float)(NPOINTS*NPOINTS);
  auto error=area/(float)NPOINTS;
  
  printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
  printf("Correct answer should be around 1.510659\n");
  
  return area;

}

void testpoint(d_complex c){
  
// Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
// If loop count reaches MAXITER, point is considered to be inside the set
  
// careful with inf and nan!
  
  d_complex z;
  int iter;
  FLOAT temp;
  
  
  //      std::cout << c.r << ' ' << c.i << std::endl;
  
  
  z=c;
  for (iter=0; iter<MAXITER; iter++){
    temp = (z.r*z.r)-(z.i*z.i)+c.r;
    z.i = z.r*z.i*2+c.i;
    z.r = temp;
    if ((z.r*z.r+z.i*z.i)>4.0f) {  
      numoutside++;
      break;
    }
  }
  
  //  if ((z.r*z.r+z.i*z.i)>4.0f) numoutside++;
  
  // std::cout << (z.r*z.r+z.i*z.i) << std::endl;
  
  
}


#ifdef ESC_SERVER
#include "libesc/libesc_api.h"
#endif

#include<iostream>
int main() {

#ifdef ESC_SERVER
  int seed = esc_start_auto();
#else
  int seed=2;
#endif

    auto solution = driver(seed);

   std::cout << "solution = " << solution << std::endl;

#ifdef ESC_SERVER
  return esc_finish(&solution, 1, ESC_TYPE_FLOAT, 0.0015);
#else
   return 0;
#endif
};
