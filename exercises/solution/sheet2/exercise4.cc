#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <typeinfo>

using T = double;
static const int N = 100;

/// Calculate sum_{k=0}^N x[k] using Kahan summation algorithm
T kahan(std::vector<T> const& x)
{
  if (x.empty())
    return T(0);

  T s = x[0];
  T c = 0;
  for (std::size_t j = 1; j < x.size(); ++j) {
    T y = x[j] - c;
    T t = s + y;
    c = (t - s) - y;
    s = t;
  }

  return s;
}

/// Calculate sum_{k=0}^N x[k] using standard summation
T simple(std::vector<T> const& x)
{
  T s = 0;
  for (T const& x_j : x)
    s += x_j;
  return s;
}

void comparison(std::string order, T const exp_value, T const kahan_sum, T const simple_sum)
{
  std::cout << std::setprecision(std::numeric_limits<T>::max_digits10);
  std::cout << "comparison for type: " << typeid(T).name() << " and order: " << order << std::endl;
  std::cout << "exp:\t"     << exp_value << std::endl;
  std::cout << "kahan:\t"   << kahan_sum  << "\t |kahan-exp|:\t" << std::abs(kahan_sum - exp_value) << std::endl;
  std::cout << "simple:\t"  << simple_sum << "\t |simple-exp|:\t" << std::abs(simple_sum - exp_value) <<  std::endl;
  std::cout << "|kahan-simple|: " << std::abs(simple_sum - kahan_sum) <<  std::endl;
}

int main()
{
  std::vector<T> x(N);

  // fill the vector without using pow and factorial
  x[0] = 1;
  for (std::size_t k = 1; k < x.size(); ++k)
    x[k] = x[k-1] * 7 / k;

  T exp_value = std::exp(T(7));

  // default order
  {
    T kahan_sum = kahan(x);
    T simple_sum = simple(x);
    comparison("default", exp_value, kahan_sum, simple_sum);
  }

  std::cout << std::endl;

  // reverse order
  {
    std::reverse(x.begin(), x.end());

    T kahan_sum = kahan(x);
    T simple_sum = simple(x);
    comparison("reverse", exp_value, kahan_sum, simple_sum);
  }

  std::cout << std::endl;

  // random order
  {
    std::srand(12345);               // fixed initial seed
    std::random_shuffle(x.begin(), x.end(), [](int n) { return std::rand() % n; });

    T kahan_sum = kahan(x);
    T simple_sum = simple(x);
    comparison("random", exp_value, kahan_sum, simple_sum);
  }
}
