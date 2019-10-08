#include <iostream>
#include "exercise2_impl.hh"

int main(int argc, char** argv)
{
  using namespace scprog;
  std::size_t n = 50;

  dense_vector b;
  dense_matrix A;

  laplacian_setup(A,n,n);
  b.resize(n*n, 1.0);

  // solution vector
  dense_vector x(n*n);

  // iteration object with max_iter and rtol
  iteration iter(b, 1000, 1.e-6, 0, 10);
  int err = cg(A, x, b, iter);

  std::cout << "Residuum |b-A*x| = "
            << (b - A*x).two_norm()
            << std::endl;
}