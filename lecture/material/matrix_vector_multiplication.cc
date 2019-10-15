#include <cmath>
#include <iostream>

#include <cblas.h>
#include <boost/numeric/mtl/mtl.hpp>

#include "linear_algebra.hh"
#include "timer.hh"

int main(int argc, char** argv)
{
  using namespace scprog;
  Timer t;

  const int N = 10000;

  DenseMatrix A(N, N, 1.0);
  DenseVector x(N, 1.0);

  // CBLAS
  {
    t.reset();
    int m = A.rows();         // number of rows of the matrix A
    int n = A.cols();         // number of columns of the matrix A
    int lda = std::max(1,m);  // Specifies the leading dimension of array storing the value of A
    int incx = 1;             // Specifies the increment for the elements of x
    int incy = 1;             // Specifies the increment for the elements of y
    double alpha = 1.0, beta = 1.0;

    DenseVector y(m, 0.0);
    cblas_dgemv(CblasRowMajor, CblasNoTrans, m, n, alpha, &A[0][0], lda,
                &x[0], incx, beta, &y[0], incy);
    std::cout << "CBLAS implementation: " << t.elapsed() << " sec" << std::endl;
    std::cout << "|y| = " << y.two_norm() << std::endl;
  }

  // lecture implementation
  {
    t.reset();
    DenseVector y(A.rows(), 0.0);
    y += A*x;
    std::cout << "lecture implementation: " << t.elapsed() << " sec" << std::endl;
    std::cout << "|y| = " << y.two_norm() << std::endl;
  }

  // mtl4 implementation
  {
    mtl::dense2D<double> A(N,N);
    A = mtl::mat::ones<double>(N,N);
    mtl::dense_vector<double> x(N, 1.0);

    t.reset();
    mtl::dense_vector<double> y(N, 0.0);
    y += A*x;
    std::cout << "mtl4 implementation: " << t.elapsed() << " sec" << std::endl;
    std::cout << "|y| = " << two_norm(y) << std::endl;
  }
}