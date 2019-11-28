#include <benchmark/benchmark.h>

#include "exercise3a.hh"
#include "exercise3b.hh"
#include "exercise3c.hh"

template <class Matrix>
void full_matrix()
{
  // matrix construction
  Matrix lhs(1000,1000), rhs(1000,1000);

  // matrix initialization
  std::srand(12345);
  for (std::size_t i = 0; i < 1000; ++i) {
    for (std::size_t j = 0; j < 1000; ++j) {
      lhs(i,j) = 1 + std::rand() % 100;
      rhs(i,j) = 1 + std::rand() % 100;
    }
  }

  // matrix addition
  lhs += rhs;
}

template <class Matrix>
void sparse_matrix()
{
  // matrix construction
  Matrix lhs(1000,1000), rhs(1000,1000);

  // matrix initialization
  std::srand(12345);
  for (std::size_t n = 0; n < 1000; ++n) {
    std::size_t i = std::rand() % 1000;
    std::size_t j = std::rand() % 1000;

    lhs(i,j) = 1 + std::rand() % 100;
    rhs(i,j) = 1 + std::rand() % 100;
  }

  // matrix addition
  lhs += rhs;
}


static void benchmark_full_matrix1(benchmark::State& state)
{
  for (auto _ : state)
    full_matrix<Matrix1>();
}
BENCHMARK(benchmark_full_matrix1);

static void benchmark_full_matrix2(benchmark::State& state)
{
  for (auto _ : state)
    full_matrix<Matrix2>();
}
BENCHMARK(benchmark_full_matrix2);

static void benchmark_full_matrix3(benchmark::State& state)
{
  for (auto _ : state)
    full_matrix<Matrix3>();
}
BENCHMARK(benchmark_full_matrix3);


static void benchmark_sparse_matrix1(benchmark::State& state)
{
  for (auto _ : state)
    sparse_matrix<Matrix1>();
}
BENCHMARK(benchmark_sparse_matrix1);

static void benchmark_sparse_matrix2(benchmark::State& state)
{
  for (auto _ : state)
    sparse_matrix<Matrix2>();
}
BENCHMARK(benchmark_sparse_matrix2);

static void benchmark_sparse_matrix3(benchmark::State& state)
{
  for (auto _ : state)
    sparse_matrix<Matrix3>();
}
BENCHMARK(benchmark_sparse_matrix3);

BENCHMARK_MAIN();
