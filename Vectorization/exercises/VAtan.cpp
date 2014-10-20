#include "NativeVector.h"

#include<cmath>
#include<iostream>
#include<iomanip>


#define likely(x) (__builtin_expect(x, true))
#define unlikely(x) (__builtin_expect(x, false))



template<typename Float>
inline
Float atan(Float t) {
  constexpr float PIO4F = 0.7853981633974483096f;
  auto large = t > 0.4142135623730950f;  // * tan pi/8 
  auto z = t;
  Float ret = {0};
  if unlikely(nativeVector::any(large)) {
    z =  large ? (t-1.0f)/(t+1.0f) : t;
    ret = large ? ret+PIO4F : ret;
  }
  Float z2 = z * z;
  ret +=
    ((( 8.05374449538e-2f * z2
	- 1.38776856032E-1f) * z2
      + 1.99777106478E-1f) * z2
     - 3.33329491539E-1f) * z2 * z
    + z;

  return ret;
}


using VF = NativeVector<float>;
constexpr unsigned int vfl = sizeof(VF)/sizeof(float);




VF va[1024];
VF vb[1024];
VF vc[1024];

float a[vfl*1024];
float b[vfl*1024];


template<typename Vec, typename F> 
inline
Vec apply(Vec v, F f) {
  typedef typename std::remove_reference<decltype(v[0])>::type T;
  constexpr int N = sizeof(Vec)/sizeof(T);
  Vec ret;
  for (int i=0;i!=N;++i) ret[i] = f(v[i]);
  return ret;
}

void computeOne() {
    vb[0]=apply(va[0],sqrtf);
}

void computeS() {
  for (int i=0;i!=1024;++i)
    vb[i]=apply(va[i],sqrtf);
}


//inline
void computeV() {
  for (int i=0;i!=1024;++i)
    vb[i]=atan(va[i]);
}

//inline
void computeL() {
  for (int i=0;i!=vfl*1024;++i)
    b[i]=atan(a[i]);
}


// inline
void computeA() {
  for (int i=0;i!=1024;++i)
    vb[i]=apply(va[i],atan<float>);
}

// inline
void computeB() {
  for (int i=0;i!=1024;++i)
    for (int j=0;j!=vfl;++j)
    vb[i][j]=atan(va[i][j]);
}



/*
void computeK() {
  for (int i=0;i!=1024;++i)
    vb[i]=apply(va[i],unsafe_logf<8>);
}
*/

#include<random>
#include<iostream>
std::mt19937 eng;
std::mt19937 eng2;
std::uniform_real_distribution<float> rgen(0.,1.);
 

void fillR() {
  for (int i=0;i!=1024;++i)
    va[i]=apply(va[i],[&](float){ return rgen(eng);});
}

void fillO() {
  float d=0;
  for (int i=0;i!=1024;++i)
    for (int j=0;j!=vfl;++j) {
      d+=0.8f/(float(vfl)*1024.f);
      va[i][j]=d;
    }
}

void fillW() {
  float d=0;
  float u=0.8;
  for (int i=0;i!=1024;++i)
    for (int j=0;j!=vfl;j+=2) {
      d+=0.8f/(vfl*1024.f);
      u-=0.8f/(vfl*1024.f);
      va[i][j]=d;
      va[i][j+1]=u;
    }
}


float sum() {
  float q=0;
  for (int i=0;i!=1024;++i) for (int j=0;j!=vfl;j+=2) { q+=vb[i][j];q-=vb[i][j+1];}
  return q;
}


unsigned int taux=0;
inline volatile unsigned long long rdtsc() {
 return __rdtscp(&taux);
}

int main(int argc, char**) {
  {
    long long t1=0;
    float s1=0;
    long long t2=0;
    float s2=0;
    long long t3=0;
    float s3=0;
    
    
    fillR();
    computeV();
    
    
    for (int i=0; i!=10000; ++i) {
      fillO();

      t1 -= rdtsc();
      computeV();
      t1 += rdtsc();
      s1+=sum();
      
      t2 -= rdtsc();
      computeA();
      t2 += rdtsc();
      s2+=sum();
      
      t3 -= rdtsc();
      computeB();
      t3 += rdtsc();
      s3+=sum();
      
    }
    std::cout << "native vector " << s1 << " " << double(t1)/10000 << std::endl;
    std::cout << "vector by elements " << s2 << " " << double(t2)/10000 << std::endl;
    std::cout << "scalar " << s3 << " " << double(t3)/10000 << std::endl << std::endl;

  }
  {
    long long t1=0;
    float s1=0;
    long long t2=0;
    float s2=0;
    long long t3=0;
    float s3=0;
    
    
    fillO();
    computeV();
    
    
    for (int i=0; i!=10000; ++i) {
      fillR();
      t1 -= rdtsc();
      computeV();
      t1 += rdtsc();
      s1+=sum();
      
      t2 -= rdtsc();
      computeA();
      t2 += rdtsc();
      s2+=sum();
      
      memcpy(a,va,sizeof(float)*1024*vfl);
      t3 -= rdtsc();
      computeL();
      t3 += rdtsc();
      memcpy(vb,b,sizeof(float)*1024*vfl);
      s3+=sum();
      
    }
    std::cout << "native vector " << s1 << " " << double(t1)/10000 << std::endl;
    std::cout << "vector by elements " << s2 << " " << double(t2)/10000 << std::endl;
    std::cout << "scalar " << s3 << " " << double(t3)/10000 << std::endl << std::endl;
  }
  {
    long long t1=0;
    float s1=0;
    long long t2=0;
    float s2=0;
    long long t3=0;
    float s3=0;
    
    
    fillO();
    computeV();
    
    
    for (int i=0; i!=10000; ++i) {
      fillW();
      t1 -= rdtsc();
      computeV();
      t1 += rdtsc();
      s1+=sum();
      
      t2 -= rdtsc();
      computeA();
      t2 += rdtsc();
      s2+=sum();
      
      t3 -= rdtsc();
      computeB();
      t3 += rdtsc();
      s3+=sum();
      
    }
    std::cout << "native vector " << s1 << " " << double(t1)/10000 << std::endl;
    std::cout << "vector by elements " << s2 << " " << double(t2)/10000 << std::endl;
    std::cout << "scalar " << s3 << " " << double(t3)/10000 << std::endl << std::endl;
  }
  return 0;
    
}
