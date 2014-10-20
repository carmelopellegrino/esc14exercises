#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

typedef int mytype;

int main () {
  std::cout << std::boolalpha;
  std::cout << "Minimum value: " << std::numeric_limits<mytype>::min() << '\n';
  std::cout << "Maximum value: " << std::numeric_limits<mytype>::max() << '\n';
  std::cout << "Minimum subnormal: " << std::numeric_limits<mytype>::denorm_min() << '\n';
  std::cout << "epsilon: " << std::numeric_limits<mytype>::epsilon() << '\n';
  std::cout << "error: " << std::numeric_limits<mytype>::round_error() << '\n';
  std::cout << "Is signed: " << std::numeric_limits<mytype>::is_signed << '\n';
  std::cout << "Non-sign bits: " << std::numeric_limits<mytype>::digits << '\n';
  std::cout << "has infinity: " << std::numeric_limits<mytype>::has_infinity << '\n';
  return 0;
}

