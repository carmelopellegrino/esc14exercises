#include "NativeVector.h"

#include<cmath>
#include<iostream>
#include<iomanip>


int main() {

  using VF = NativeVector<float>;
  
//  NativeVector<float> v1{1.f};
  NativeVector<float> v1 = nativeVector::zero<NativeVector<float>>() + 1;
  NativeVector<float> v2 = nativeVector::zero<NativeVector<float>>() + 2;
  std::cout<< v1 << std::endl;
 
  VF a,b,x;
  for (auto i=0U; i<  nativeVector::length(a); ++i) { a[i]=i+1; b[i]= 1+ 2*(i%2 ? float(i) : -float(i)); }
  std::cout<< a << ' ' << b << std::endl;

  x[0] = 0;
  for (auto i=1U; i<  nativeVector::length(x); ++i) x[i]=x[i-1]+float(M_PI)/32.f;
  std::cout<< x << std::endl;

  auto c = 3.14f*b*a;
  auto z = (a>0) ? a : -a;
  auto m = (a>b) ? a : b; 
  auto t = a/b; t = (x>float(M_PI)/8.f) ? (t-1.0f)/(t+1.0f) : t;

  std::cout << c << ' ' << z << ' ' << m << std::endl;
  std::cout<< t << std::endl;


  x = nativeVector::zero<NativeVector<float>>() + 0.1f; 
  std::cout<< std::hexfloat;
  std::cout << nativeVector::invSqrt(x) << ' ' << 1.f/std::sqrt(0.1f) << std::endl;
  std::cout << 1.f/sqrt(x) << ' ' << 1.f/std::sqrt(0.1f) << std::endl;
  std::cout<<  std::defaultfloat;

  std::cout<<  std::boolalpha;
  std::cout << nativeVector::any(v2>v1) << ' ' <<  nativeVector::all(v2>v1) << ' ' << !nativeVector::any(v2<v1) << ' ' <<  !nativeVector::all(v2<v1) << std::endl;
  v2[2] = -1;
  std::cout << nativeVector::any(v2>v1) << ' ' <<  !nativeVector::all(v2>v1) << ' ' << nativeVector::any(v2<v1) << ' ' <<  !nativeVector::all(v2<v1) << std::endl;

  return 0;
};
