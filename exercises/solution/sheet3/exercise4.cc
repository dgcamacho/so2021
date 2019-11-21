#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>

using T = double;

// anonymous namespace, since just implementation details
namespace
{
  // implementation of f(x)
  T f(T const a, T const x) { return x*x - a; }

  // implementation of f'(x)
  T df(T const a, T const x) { return 2*x; }

  // the Newton fixed-point operator
  T newton(T const a, T const x)
  {
    // Note: for a == 0 and x == 0 the result should be 0
    // This is not enforced here, for simplicity
    return x - f(a,x) / df(a,x);
  }

  // compute the sign of a value
  int sgn(T value)
  {
    return (T(0) < value) - (value < T(0));
  }
}


/// Return the square-root of a calculated recursively with break condition x0 and recursion depth n
T sqrt_recu(T const a, T const x0, int const n)
{
  // these asserts check for valid input
  assert(a >= 0);
  assert(sgn(a) == sgn(x0));
  assert(n >= 0);
  return n == 0 ? x0 : newton(a, sqrt_recu(a,x0,n-1));
}

/// Return the square-root of a calculated iteratively, starting from initial value x0 with n iterations
T sqrt_iter(T const a, T x, int const n)
{
  // these asserts check for valid input
  assert(a >= 0);
  assert(sgn(a) == sgn(x));
  assert(n >= 0);
  for (int i = 0; i < n; ++i)
    x = newton(a,x);
  return x;
}


/// Implementation of a sqrt function using the Newton step as break condition
std::pair<T,int> sqrt1(T a)
{
  // this is some upper bound for the number of iteration
  int const n = std::numeric_limits<T>::max_exponent;
  // a break tolerance for |x_n - x_{n-1}| < TOL
  T const tol = 4*std::numeric_limits<T>::epsilon();
  // use a bas initial condition
  T x1 = a, x2 = a;
  for (int i = 0; i < n; ++i, x1 = x2) {
    x2 = newton(a,x1);
    if (std::abs(x1 - x2) < tol)
      return {x2, i};
  }

  return {x2, n};
}


/// Implementation of a sqrt function using error f(x_n) < TOL as break condition
/// where TOL = 4 * eps
std::pair<T,int> sqrt2(T a)
{
  // this is some upper bound for the number of iteration
  int const n = std::numeric_limits<T>::max_exponent;
  // a break tolerance for f(x_n) < TOL
  T const tol = 4*std::numeric_limits<T>::epsilon();
  // use a bas initial condition
  T x1 = a, x2 = a;
  for (int i = 0; i < n; ++i, x1 = x2) {
    x2 = newton(a,x1);
    if (f(a,x2) < tol)
      return {x2, i};
  }

  return {x2, n};
}


int main()
{
  // test for a=10, x0=3, and N={5,10,100}
  // compare against std::sqrt

  T a = 10.0;
  T x0 = 3.0;

  T sqrt_a = std::sqrt(a);
  auto sqrt1_a = sqrt1(a);
  auto sqrt2_a = sqrt2(a);

  std::cout << std::setprecision(std::numeric_limits<T>::max_digits10);

  // print the errors of the sqrt implementations compared to std::sqrt
  std::cout << "error(sqrt1) = " << std::abs(sqrt_a - sqrt1_a.first) << ", iterations: " << sqrt1_a.second << std::endl;
  std::cout << "error(sqrt2) = " << std::abs(sqrt_a - sqrt2_a.first) << ", iterations: " << sqrt2_a.second << std::endl;

  // print the values for the test set
  for (int n : {1, 2, 3, 4, 5, 10, 100}) {
    assert(sqrt_iter(a,x0,n) == sqrt_recu(a,x0,n));
    std::cout << n << ") error(iter) = " << std::abs(sqrt_a - sqrt_iter(a,x0,n)) << std::endl;
  }
}
