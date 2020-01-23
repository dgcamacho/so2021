#include <cstdlib>

#include "matrix.hh"
#include "rational.hh"
#include "exercise3.hh"

// identity elements of addition

template <>
double identity<double>()
{
  return 0.0;
}

template <>
int identity<int>()
{
  return 0;
}

template <>
unsigned int identity<unsigned int>()
{
  return 0u;
}

template <>
Rational identity<Rational>()
{
  return Rational{identity<int>()};
}

template <>
Matrix identity<Matrix>()
{
  return Matrix{10, 10, identity<double>()};
}

// random generators

template <>
double identity<double>()
{
  return 200 * (double(std::rand()) / RAND_MAX) - 100;
}

template <>
int identity<int>()
{
  return std::rand()%200 - 100;
}

template <>
unsigned int identity<unsigned int>()
{
  return std::rand()%100;
}

template <>
Rational random<Rational>()
{
  return Rational{identity<int>(), 1 + identity<unsigned int>()};
}

template <>
Matrix random<Matrix>()
{
  Matrix m{10, 10};
  for (std::size_t i = 0; i < m.num_rows(); ++i)
    for (std::size_t j = 0; j < m.num_cols(); ++j)
      m(i,j) = identity<double>();

  return m;
}

int main()
{
  std::srand(12345);

  test<Matrix>();
  test<Rational>();
}
