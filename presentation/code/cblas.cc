#include <iostream>                             // clas.cc
#include <cblas.h>
int main () {
  int const N = 3;
  double A[N*N] = {1.0,0.0,0.0,  0.0,1.0,0.0,  0.0,0.0,1.0};
  double x[N] = {1.0,1.0,1.0};
  double y[N] = {0.0};

  // y += 0.5*x
  cblas_daxpy(N, 0.5, x, 1, y, 1);
  // y += 0.5*A*x
  cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, 0.5, A, N, x, 1, 1.0, y, 1);
  // |y|_2
  double two_norm = cblas_dnrm2(N, y, 1);

  std::cout << two_norm << std::endl;
}