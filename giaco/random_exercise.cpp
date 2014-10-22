#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

int main()
{
  const int nrolls = 10000;  // number of experiments
  const int nstars = 100;    // maximum number of stars to distribute

  const double mean = 15.0;
  const double sigma = 9.;

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(mean, sigma);

  int p[10] = {};

  std::vector<double> numbers;
  numbers.reserve(nrolls);

  for (int i = 0; i<nrolls; ++i) {
    double number = distribution(generator);
    std::cout << number << "\n";
//    if ((number >= 0.0) && (number < 10.0)) ++p[int(number)];
    numbers.push_back(number);
  }

  auto bin = (std::max(numbers) - std::min(numbers)) / (sigma * 20);

  std::cout << "normal_distribution (" << mean << ", " << sigma << "):" << std::endl;

  for (int i=0; i<10; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }

  return 0;
}
