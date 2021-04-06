#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>

using namespace mtl;

int main(int argc, char** argv)
{
  int const size = 40, N = size * size;
  using matrix_t = compressed2D<double>;

  // Set up a matrix 1,600 x 1,600 with
  // 5-point-stencil
  matrix_t A{N, N};
  mat::laplacian_setup(A, size, size);

  // Compute b = A*x with x == 1
  dense_vector<double> x{N, 1.0}, b;
  b = A * x;

  std::cout << two_norm(b) << std::endl;
}
