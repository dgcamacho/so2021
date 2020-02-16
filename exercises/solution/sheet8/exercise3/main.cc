#include <cstdlib>
#include <algorithm>

#include "matrix.hh"
#include "rational.hh"
#include "polynomial.hh"
#include "main.hh"

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

template <>
Polynomial identity<Polynomial>()
{
  return Polynomial{};
}

// random generators

template <>
double random<double>()
{
  return 200 * (double(std::rand()) / RAND_MAX) - 100;
}

template <>
int random<int>()
{
  return std::rand()%200 - 100;
}

template <>
unsigned int random<unsigned int>()
{
  return std::rand()%100;
}

template <>
Rational random<Rational>()
{
  return Rational{random<int>(), 1 + int(random<unsigned int>())};
}

template <>
Matrix random<Matrix>()
{
  Matrix m{10, 10};
  for (std::size_t i = 0; i < m.num_rows(); ++i)
    for (std::size_t j = 0; j < m.num_cols(); ++j)
      m(i,j) = random<double>();

  return m;
}

template <>
Polynomial random<Polynomial>()
{
  std::size_t num_coeff = random<unsigned int>();
  std::vector<Polynomial::coeff_type> coeffs(num_coeff);
  std::generate(coeffs.begin(), coeffs.end(), random<double>);

  return Polynomial(std::move(coeffs));
}

int main()
{
  std::srand(12345);

  test<Matrix>();
  test<Rational>();
  test<Polynomial>();

  test<int>();
  test<unsigned int>();
  test<double>();
}
