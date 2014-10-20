#include "../../libesc/libesc_api.h"
#include <cstdio>
#include <fenv.h>
#include <vector>


template<typename T>
T kahanSum(T const* input, size_t n)
{
  T sum = input[0];
  T t = 0.0; // A running compensation for lost low-order bits.
  for (size_t i = 1; i != n; ++i) {
    T y = input[i] - t; // so far, so good: t is zero.
    T s = sum + y; // Alas, sum is big, y small, so low-order digits of y are lost.
    t = (s - sum) - y; // ( s - sum) recovers the high-order part of y
    // subtracting y recovers -(low part of y)
    sum = s; //Algebraically, t should always be zero.
    // Beware eagerly optimising compilers!
  } //Next time around, the lost low part will be added to y in a fresh attempt.
  return sum;
}

int main() {
  const int seed = 500000 * esc_start_auto();
/*
FE_TONEAREST //Round to nearest.
FE_UPWARD    // Round toward +&infin;.
FE_DOWNWARD // Round toward -&infin;.
FE_TOWARDZERO //
*/

  /*if (! seed)
  {
    printf("seed is: %d.\n", seed);
    return -1;
  }

   printf("rounding %d\n",fegetround());
//   fesetround(FE_UPWARD);
//   fesetround(FE_TOWARDZERO);
   printf("new rounding %d\n", fegetround());
*/
   float tenth = 0.1f;
   //float t = 0;
   //long long n = 0;
   /*
   while(n < seed) {
     t += tenth;
     ++n;
     if (n<21 || n%36000==0) printf("%d %f %a\n",n,t,t);
   }*/
   
   std::vector<float> array(seed, tenth);
   /*float* array = new float[seed];
   for (int i = 0; i < seed; ++i) {
     array[i] = tenth;
   }*/
   
   float ksum = kahanSum<float>(array.data(), seed);

   //printf("\n\n");

   //printf("Ksum = %f\n", ksum);
   //printf("sum  = %f\n", t);

   //float count = float(60*60*100*10);
   //printf("\n\n%f %f %a\n\n",count,float(count*tenth),float(count*tenth));

//   int result = 1;

   return esc_finish(&ksum,1,ESC_TYPE_FLOAT,ESC_ACCURACY_DEFAULT);
}
