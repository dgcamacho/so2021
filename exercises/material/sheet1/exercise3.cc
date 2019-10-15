#include <iostream>
#include "linear_algebra.hh"

int main(int argc, char** argv)
{
  using namespace scprog;
  std::size_t n = 50;

  // right-hand side vector b
  DenseVector b(n, 1.0);

  // system matrix
  DenseMatrix A;
  laplacian_setup(A,n,n);

  // solution vector
  DenseVector x(n);

  // iteration object with max_iter and rtol
  BasicIteration iter(b, 0, 1.e-6, 0, 10);

  // solve the linear system using a conjugate-gradient algorithm
  int err = cg(A, x, b, iter);
  if (err) {
    std::cerr << "ERROR: Linear system could not be solved.\n"
              << "       |b-A*x| = " << iter.resid() << ", |b-A*x|/|b| = " << iter.relresid() << std::endl;
    std::abort();
  }

  return err;
}