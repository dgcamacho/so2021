#include <cmath>

// Return the square-root of a calculated recursively with break condition x0 and recursion depth N
/**
 * Recursion defined by
 * x_n := x_{n-1} - f(x_{n-1})/f'(x_{n-1})
 * with x_0 = x0
 * for f(x) = x*x - a and f'(x) = df(x)/dx
 *
 * Return the value x_N.
 **/
double sqrt_recu(double a, double x0, int N)
{
  // your implementation here
}

// Return the square-root of a calculated iteratively, starting from initial value x0 with N iterations
/**
 * Iteration defined by
 * x_{n+1} := x_{n} - f(x_{n})/f'(x_{n})
 * with x_0 = x0
 * for f(x) = x*x - a and f'(x) = df(x)/dx
 *
 * Return the value x_N.
 **/
double sqrt_iter(double a, double x0, int N)
{
  // your implementation here
}


int main()
{
  // test for a=10, x0=3, and N={5,10,100}
  // compare against std::sqrt
}