#include<iostream>
#include<cstdio>

#ifdef ESC_SERVER
#include "libesc/libesc_api.h"
#endif



int f(int) {
  int n=0; float w=1; float y=0; float prev=0;
  do {
    prev=y;
    y = w++;
    ++n;
  } while (w>y);
  std::cout << n << ": " << prev << " " << y << " " << w << std::endl;
  printf("%a %a %a\n\n", prev,y,w);
  return n;
}


int main() {
#ifdef ESC_SERVER
  int seed = esc_start_auto(); 
#else
  int seed = 1000;
#endif

  auto solution = f(seed);
#ifdef ESC_SERVER
  return esc_finish(&solution, 1, ESC_TYPE_INT, ESC_ACCURACY_DEFAULT);
#else
  return solution>0;
#endif
}

