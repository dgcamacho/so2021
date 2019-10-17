#include <iostream>
#include "linear_algebra.hh"

namespace scprog {

// set all entries of the vector to value v
DenseVector& DenseVector::operator=(value_type v)
{
  for (auto& v_i : data_)
    v_i = v;
  return *this;
}


// perform update-assignment elementwise +=
DenseVector& DenseVector::operator+=(DenseVector const& that)
{
  assert(size() == that.size());
  for (size_type i = 0; i < size(); ++i)
    data_[i] += that.data_[i];
  return *this;
}


// perform update-assignment elementwise +=
DenseVector& DenseVector::operator-=(DenseVector const& that)
{
  assert(size() == that.size());
  for (size_type i = 0; i < size(); ++i)
    data_[i] -= that.data_[i];
  return *this;
}


// perform update-assignment elementwise *= with a scalar
DenseVector& DenseVector::operator*=(value_type s)
{
  for (size_type i = 0; i < size(); ++i)
    data_[i] *= s;
  return *this;
}


// perform update-assignment elementwise /= with a scalar
DenseVector& DenseVector::operator/=(value_type s)
{
  assert(s != value_type(0));
  for (size_type i = 0; i < size(); ++i)
    data_[i] /= s;
  return *this;
}


// computes Y = a*X + Y.
void DenseVector::axpy(value_type a, DenseVector const& x)
{
  assert(size() == x.size());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += a * x.data_[i];
}


// computes Y = a*Y + X.
void DenseVector::aypx(value_type a, DenseVector const& x)
{
  assert(size() == x.size());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] = a * data_[i]  + x.data_[i];
}


// return the two-norm ||vector||_2 = sqrt(sum_i v_i^2)
typename DenseVector::value_type DenseVector::two_norm() const
{
  using std::sqrt;
  value_type result = 0;
  for (auto const& d : data_)
    result += d * d;
  return sqrt(result);
}


// return the infinity-norm ||vector||_inf = max_i(|v_i|)
typename DenseVector::value_type DenseVector::inf_norm() const
{
  using std::abs;
  using std::max;
  value_type result = 0;
  for (auto const& d : data_)
    result = max(result, value_type(abs(d)));
  return result;
}


// return v^T*v
typename DenseVector::value_type DenseVector::unary_dot() const
{
  value_type result = 0;
  for (auto const& d : data_)
    result += d*d;
  return result;
}


// return v^T*v2
typename DenseVector::value_type DenseVector::dot(DenseVector const& v2) const
{
  assert(v2.size() == size());
  value_type result = 0;
  for (size_type i = 0; i < size(); ++i)
    result += data_[i] * v2.data_[i];
  return result;
}

// construct a matrix from initializer lists
DenseMatrix::DenseMatrix(std::initializer_list<std::initializer_list<value_type>> l)
{
  // 1. determine number of entries
  size_type columns = 0;
  size_type rows = l.size();
  for (auto const& row : l) {
    if (columns == 0)
      columns = row.size();
    else
      assert(columns == row.size());
  }

  // 2. insert entries from initializer lists into matrix
  data_.reserve(rows*columns);
  for (auto const& row : l)
    data_.insert(data_.end(), row.begin(), row.end());
}


// perform update-assignment elementwise +=
DenseMatrix& DenseMatrix::operator+=(DenseMatrix const& that)
{
  assert(rows() == that.rows());
  assert(cols() == that.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += that.data_[i];
  return *this;
}


// perform update-assignment elementwise +=
DenseMatrix& DenseMatrix::operator-=(DenseMatrix const& that)
{
  assert(rows() == that.rows());
  assert(cols() == that.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] -= that.data_[i];
  return *this;
}


// set all entries to v
DenseMatrix& DenseMatrix::operator=(value_type v)
{
  for (auto& A_ij : data_)
    A_ij = v;
  return *this;
}


// matrix-vector product A*x
DenseVector operator*(DenseMatrix const& A, DenseVector const& x)
{
  using value_type = typename DenseMatrix::value_type;
  DenseVector y(A.cols(), value_type(0));
  A.mult(x, y);
  return y;
}


// computes the matrix-vector product, y = Ax.
void DenseMatrix::mult(DenseVector const& x, DenseVector& y) const
{
  assert(x.size() == cols());
  assert(y.size() == rows());
  for (size_type r = 0; r < rows(); ++r) {
    y[r] = value_type(0);
    value_type const* row = (*this)[r];
    for (size_type c = 0; c < cols(); ++c)
      y[r] += row[c]*x[c];
  }
}


// computes v3 = v2 + A * v1.
void DenseMatrix::mult_add(DenseVector const& v1, DenseVector const& v2, DenseVector& v3) const
{
  assert(v1.size() == cols());
  assert(v2.size() == rows());
  assert(v3.size() == rows());
  for (size_type r = 0; r < rows(); ++r) {
    v3[r] = v2[r];
    value_type const* row = (*this)[r];
    for (size_type c = 0; c < cols(); ++c)
      v3[r] += row[c]*v1[c];
  }
}


// computes Y = a*X + Y.
void DenseMatrix::axpy(value_type a, DenseMatrix const& X)
{
  assert(rows() == X.rows());
  assert(cols() == X.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += a * X.data_[i];
}


// computes Y = a*Y + X.
void DenseMatrix::aypx(value_type a, DenseMatrix const& X)
{
  assert(rows() == X.rows());
  assert(cols() == X.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] = a * data_[i]  + X.data_[i];
}


// Setup a matrix according to a Laplacian equation on a 2D-grid using a five-point-stencil.
// Results in a matrix A of size (m*n) x (m*n)
void laplacian_setup(DenseMatrix& A, std::size_t m, std::size_t n)
{
  A.resize(m*n, m*n);
  A = 0;

  for (std::size_t i = 0; i < m; i++) {
    for (std::size_t j = 0; j < n; j++) {
      std::size_t row = i * n + j;
      A(row, row) = 4;
      if (j < n - 1) A(row, row + 1) = -1;
      if (i < m - 1) A(row, row + n) = -1;
      if (j > 0)     A(row, row - 1) = -1;
      if (i > 0)     A(row, row - n) = -1;
    }
  }
}


// Iteration finished according to residual value r
bool BasicIteration::finished(real_type const& r)
{
  bool result = false;
  if (converged(r))
    result = finished_ = true;
  if (!result)
    result = check_max();
  print_resid();
  return result;
}


bool BasicIteration::check_max()
{
  if (i_ >= max_iter_)
    error_ = 1, finished_ = true, err_msg_ = "Too many iterations.";
  return finished_;
}


bool BasicIteration::converged() const
{
  if (norm_r0_ == 0)
    return resid_ <= atol_;  // ignore relative tolerance if |r0| is zero
  return resid_ <= rtol_ * norm_r0_ || resid_ <= atol_;
}


void BasicIteration::print_resid()
{
  if (!quite_ && i_ % cycle_ == 0) {
    if (i_ != last_print_) { // Avoid multiple print-outs in same iteration
      std::cout << "iteration " << i_ << ": resid " << resid() << std::endl;
      last_print_ = i_;
    }
  }
}


int BasicIteration::error_code() const
{
  using std::pow;
  if (!suppress_)
    std::cout << "finished! error code = " << error_ << '\n'
              << iterations() << " iterations\n"
              << resid() << " is actual final residual. \n"
              << relresid() << " is actual relative tolerance achieved. \n"
              << "Relative tol: " << rtol_ << "  Absolute tol: " << atol_ << '\n'
              << "Convergence:  " << pow(relresid(), 1.0 / double(iterations())) << std::endl;
  return error_;
}


// Apply the conjugate gradient algorithm to the linear system A*x = b and return the number of iterations
int cg(DenseMatrix const& A, DenseVector& x, DenseVector const& b, BasicIteration& iter)
{
  using std::abs;
  using Vector = DenseVector;
  using Scalar = typename DenseVector::value_type;
  using Real   = typename BasicIteration::real_type;

  Scalar rho(0), rho_1(0), alpha(0);
  Vector p(b), q(b), z(b);
  Vector r(b - A*x);

  rho = r.unary_dot();
  while (! iter.finished(Real(sqrt(abs(rho))))) {
    ++iter;
    if (iter.first())
      p = r;
    else
      p.aypx(rho / rho_1, r); // p = r + (rho / rho_1) * p;

    q = A * p;
    alpha = rho / p.dot(q);

    x.axpy(alpha, p);     // x += alpha * p
    r.axpy(-alpha, q);    // r -= alpha * q

    rho_1 = rho;
    rho = r.unary_dot();  // rho = r^T * r
  }

  return iter;
}

} // end namespace scprog