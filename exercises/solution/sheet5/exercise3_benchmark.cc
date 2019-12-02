// Compile this code and link against google benchmark suite
// g++ -O2 -DNDEBUG -isystem benchmark/include exercise3a.cc exercise3b.cc exercise3c.cc exercise3_benchmark.cc -o exercise3_benchmark -L benchmark/lib -lbenchmark -lpthread

#include <benchmark/benchmark.h>

#include "exercise3a.hh"
#include "exercise3b.hh"
#include "exercise3c.hh"

// Implementation of a (generic) test for full matrix insertion and adding
template <class Matrix>
void full_matrix()
{
  const std::size_t size = 1000;

  // matrix construction
  Matrix lhs(size,size), rhs(size,size);

  // matrix initialization
  std::srand(12345);
  for (std::size_t i = 0; i < size; ++i) {
    for (std::size_t j = 0; j < size; ++j) {
      lhs(i,j) = 1 + std::rand() % 100;
      rhs(i,j) = 1 + std::rand() % 100;
    }
  }

  // matrix addition
  lhs += rhs;
}

// Implementation of a (generic) test for sparse matrix insertion and adding
template <class Matrix>
void sparse_matrix()
{
  const std::size_t size = 1000;

  // matrix construction
  Matrix lhs(size,size), rhs(size,size);

  // matrix initialization
  std::srand(12345);
  for (std::size_t n = 0; n < size; ++n) {
    std::size_t i = std::rand() % size;
    std::size_t j = std::rand() % size;

    lhs(i,j) = 1 + std::rand() % 100;
    rhs(i,j) = 1 + std::rand() % 100;
  }

  // matrix addition
  lhs += rhs;
}


// setting up all the benachmarks:

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
