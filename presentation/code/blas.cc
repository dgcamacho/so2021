#include <cassert>
#include <cmath>
#include <iostream>
#include <span>
#include <experimental/mdspan>  // see https://github.com/kokkos/mdspan

namespace stdex = std::experimental;

using DynamicVector
  = std::span<double, std::dynamic_extent>;

using DynamicMatrix
  = stdex::mdspan<double, stdex::dynamic_extent, stdex::dynamic_extent>;

// workaround for missing mdspan::span
DynamicVector span(DynamicMatrix mat)
{
  return {mat.data(), std::size_t(mat.extent(0)*mat.extent(1))};
}

double* make_vector (int const size)
{
  return new double[size];
}

double* make_matrix (int const nrows, int const ncols)
{
  return new double[nrows * ncols];
}

// vec_i = value
void fill (DynamicVector vec, double const value) {
  for (int i = 0; i < vec.size(); ++i)
    vec[i] = value;
}

// vec = factor * vec
void scale (DynamicVector vec, double const factor) {
  for (int i = 0; i < vec.size(); ++i)
    vec[i] *= factor;
}

// y = alpha * x + y
void axpy (double const alpha, DynamicVector x, DynamicVector y) {
  assert(x.size() == y.size());
  for (int i = 0; i < y.size(); ++i)
    y[i] += alpha * x[i];
}

// x^T * y
double dot (DynamicVector x, DynamicVector y) {
  assert(x.size() == y.size());
  double d = 0.0;
  for (int i = 0; i < y.size(); ++i)
    d += x[i] * y[i];
  return d;
}

// |vec|_2
double two_norm (DynamicVector vec) {
  return std::sqrt(dot(vec, vec));
}

// mat_ij = value
void fill (DynamicMatrix mat, double const value) {
  fill(span(mat), value);  // use vector method
}

// mat = mat * factor
void scale (DynamicMatrix mat, double const factor)
{
  scale(span(mat), factor);
}

// y = alpha * x + y
void axpy (double const alpha, DynamicMatrix x, DynamicMatrix y)
{
  axpy(alpha, span(x), span(y));
}

// Frobenius inner product
double ddot (DynamicMatrix x, DynamicMatrix y) {
  return dot(span(x), span(y));
}

// Frobenius norm |mat|_F
double frobenius_norm (DynamicMatrix mat) {
  return two_norm(span(mat));
}

// y = alpha * A * x + y
void mat_vec (double const alpha, DynamicMatrix A, DynamicVector x, DynamicVector y)
{
  assert(A.extent(0) == y.size());
  assert(A.extent(1) == x.size());

  for (int i = 0; i < A.extent(0); ++i)
  {
    double f = 0.0;
    for (int j = 0; j < A.extent(1); ++j)
      f += A(i,j) * x[j];

    y[i] += alpha * f;
  }
}

// C = alpha * A * B + C
void mat_mat (double const alpha, DynamicMatrix A, DynamicMatrix B, DynamicMatrix C)
{
  assert(A.extent(0) == C.extent(0));
  assert(A.extent(1) == B.extent(0));
  assert(B.extent(1) == C.extent(1));

  for (int i = 0; i < C.extent(0); ++i) {
    for (int j = 0; j < C.extent(1); ++j)
    {
      double f = 0.0;
      for (int k = 0; k < A.extent(1); ++k)
        f += A(i,k) * B(k,j);

      C(i,j) += alpha * f;
    }
  }
}


int main ()
{
  auto data_A = make_matrix(10, 10);
  auto A = DynamicMatrix(data_A, 10, 10);

  auto data_x = make_vector(10);
  auto x = DynamicVector(data_x, 10);

  auto data_y = make_vector(10);
  auto y = DynamicVector(data_y, 10);

  fill(A, 1.0);  fill(x, 1.0);  fill(y, 0.0);

  // y += 0.5*x
  axpy(0.5, x, y);
  // y += 0.5*A*x
  mat_vec(0.5, A, x, y);

  std::cout << frobenius_norm(A) << std::endl;
  std::cout << two_norm(y) << std::endl;
}