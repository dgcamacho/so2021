// file: linalg.cc

#include <span>
#include <experimental/mdspan>

import linalg;

namespace stdex = std::experimental;

using DynamicMatrix
  = stdex::mdspan<double, stdex::dynamic_extent, stdex::dynamic_extent>;

int main () {
  int const N = 3;
  double A[N*N] = {1.0,0.0,0.0,  0.0,1.0,0.0,  0.0,0.0,1.0};
  double x[N] = {1.0,1.0,1.0};
  double y[N] = {};

  mat_vec(DynamicMatrix{A,N,N}, std::span{x,N}, std::span{y,N});
}