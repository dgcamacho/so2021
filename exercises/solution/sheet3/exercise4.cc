#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include <benchmark/benchmark.h>

using T = double;

T f(T a, T x)
{
  return x*x - a;
}

T df(T a, T x)
{
  return 2*x;
}

T newton(T a, T x)
{
  return x - f(a,x) / df(a,x);
}


// Return the square-root of a calculated recursively with break condition x0 and recursion depth N
/**
 * Recursion defined by
 * x_n := x_{n-1} - f(x_{n-1})/f'(x_{n-1})
 * with x_0 = x0
 * for f(x) = x*x - a and f'(x) = df(x)/dx
 *
 * Return the value x_N.
 **/
T sqrt_recu(T a, T x0, int N)
{
  assert(N >= 0);
  return N == 0 ? x0 : newton(a, sqrt_recu(a,x0,N-1));
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
T sqrt_iter(T a, T x, int N)
{
  for (int i = 1; i <= N; ++i)
    x = newton(a,x);
  return x;
}


T my_sqrt(T a)
{
  T x1 = a, x2 = 0;
  for (int i = 1; i <= 16; ++i)
    x1 = newton(a,x1);

  for (int i = 1; i <= 100; ++i, x1 = x2) {
    x2 = newton(a,x1);
    if (std::abs(x1 - x2) < 4*std::numeric_limits<T>::epsilon())
      break;
  }

  return x2;
}


static void benchmark_mysqrt(benchmark::State& state)
{
  double a = 37345.0;
  for (auto _ : state)
    benchmark::DoNotOptimize( my_sqrt(a) );
}
BENCHMARK(benchmark_mysqrt);

static void benchmark_stdsqrt(benchmark::State& state)
{
  double a = 37345.0;
  for (auto _ : state)
    benchmark::DoNotOptimize( std::sqrt(a) );
}
BENCHMARK(benchmark_stdsqrt);

BENCHMARK_MAIN();


#if 0
int main()
{
  // test for a=10, x0=3, and N={5,10,100}
  // compare against std::sqrt

  T a = 10.0;
  T x0 = 3.0;

  T sqrt_a = std::sqrt(a);
  T my_sqrt_a = my_sqrt(a);
  std::cout << "error(sqrt) = " << std::abs(sqrt_a - my_sqrt_a) << std::endl;
  for (int N : {1,2,3,4,5,6,7,8,9,10})
    std::cout << N << ") error(iter) = " << std::abs(sqrt_a - sqrt_iter(a,x0,N)) << std::endl;
}
#endif