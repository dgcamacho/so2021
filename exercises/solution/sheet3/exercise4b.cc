#include <cmath>
#include <limits>

// This implementation is written for bencharking purposes, using the
// Google benchmarking suite: https://github.com/google/benchmark

// Compile with
// g++ exercise4b.cc -O2 -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o exercise4b

#include <benchmark/benchmark.h>

using T = double;

// implementation of f(x)
T f(T const a, T const x) { return x*x - a; }

// implementation of f'(x)
T df(T const a, T const x) { return 2*x; }

// the Newton fixed-point operator
T newton(T const a, T const x)
{
  return x - f(a,x) / df(a,x);
}


// Implementation of a sqrt function using error |x_n - x_{n-1}| < TOL as break condition
// where TOL = 4 * eps
T sqrt1(T a)
{
  int const n = std::numeric_limits<T>::max_exponent;
  T const tol = 4*std::numeric_limits<T>::epsilon();

  T x1 = a, x2 = a;
  for (int i = 0; i < n; ++i, x1 = x2) {
    x2 = newton(a,x2);
    if (std::abs(x1 - x2) < tol)
      return x2;
  }

  return x2;
}


// Implementation of a sqrt function using error f(x_n) < TOL as break condition
// where TOL = 4 * eps
T sqrt2(T a)
{
  int const n = std::numeric_limits<T>::max_exponent;
  T const tol = 4*std::numeric_limits<T>::epsilon();

  T x1 = a, x2 = a;
  for (int i = 0; i < n; ++i, x1 = x2) {
    x2 = newton(a,x2);
    if (f(a,x2) < tol)
      return x2;
  }

  return x2;
}


// Implementation of a sqrt function using error f(x_n) < TOL as break condition
// where TOL = 4 * eps, perform always a fixed number of 16 iteration without any test
T sqrt3(T a)
{
  int const n = std::numeric_limits<T>::max_exponent;
  T const tol = 4*std::numeric_limits<T>::epsilon();

  T x1 = a, x2 = a;
  for (int j = 0; j < 16; ++j)
    x2 = newton(a,x2);

  x1 = newton(a, x2);
  if (std::abs(x1 - x2) < tol)
    return x2;

  for (int i = 0; i < n/16 - 1; ++i, x1 = x2) {
    for (int j = 0; j < 16; ++j)
      x2 = newton(a,x2);

    if (std::abs(x1 - x2) < tol)
      return x2;
  }

  return x2;
}

#ifndef BENCHMARK_VALUE_A
#define BENCHMARK_VALUE_A 3623465.0
#endif

static void benchmark_sqrt1(benchmark::State& state)
{
  double a = BENCHMARK_VALUE_A;
  for (auto _ : state)
    benchmark::DoNotOptimize( sqrt1(a) );
}
BENCHMARK(benchmark_sqrt1);

static void benchmark_sqrt2(benchmark::State& state)
{
  double a = BENCHMARK_VALUE_A;
  for (auto _ : state)
    benchmark::DoNotOptimize( sqrt2(a) );
}
BENCHMARK(benchmark_sqrt2);

static void benchmark_sqrt3(benchmark::State& state)
{
  double a = BENCHMARK_VALUE_A;
  for (auto _ : state)
    benchmark::DoNotOptimize( sqrt3(a) );
}
BENCHMARK(benchmark_sqrt3);

static void benchmark_stdsqrt(benchmark::State& state)
{
  double a = BENCHMARK_VALUE_A;
  for (auto _ : state)
    benchmark::DoNotOptimize( std::sqrt(a) );
}
BENCHMARK(benchmark_stdsqrt);

BENCHMARK_MAIN();
