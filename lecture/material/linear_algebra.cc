#include <iostream>
#include "linear_algebra.hh"

namespace scprog {

// set all entries of the vector to value v
dense_vector& dense_vector::operator=(value_type v)
{
  for (auto& v_i : data_)
    v_i = v;
  return *this;
}


// perform update-assignment elementwise +=
dense_vector& dense_vector::operator+=(dense_vector const& that)
{
  assert(size() == that.size());
  for (size_type i = 0; i < size(); ++i)
    data_[i] += that.data_[i];
  return *this;
}


// perform update-assignment elementwise +=
dense_vector& dense_vector::operator-=(dense_vector const& that)
{
  assert(size() == that.size());
  for (size_type i = 0; i < size(); ++i)
    data_[i] -= that.data_[i];
  return *this;
}


// perform update-assignment elementwise *= with a scalar
dense_vector& dense_vector::operator*=(value_type s)
{
  for (size_type i = 0; i < size(); ++i)
    data_[i] *= s;
  return *this;
}


// perform update-assignment elementwise /= with a scalar
dense_vector& dense_vector::operator/=(value_type s)
{
  assert(s != value_type(0));
  for (size_type i = 0; i < size(); ++i)
    data_[i] /= s;
  return *this;
}


// computes Y = a*X + Y.
void dense_vector::axpy(value_type a, dense_vector const& x)
{
  assert(size() == x.size());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += a * x.data_[i];
}


// computes Y = a*Y + X.
void dense_vector::aypx(value_type a, dense_vector const& x)
{
  assert(size() == x.size());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] = a * data_[i]  + x.data_[i];
}


// return the two-norm ||vector||_2 = sqrt(sum_i v_i^2)
typename dense_vector::value_type dense_vector::two_norm() const
{
  using std::sqrt;
  value_type result = 0;
  for (auto const& d : data_)
    result += d * d;
  return sqrt(result);
}


// return the infinity-norm ||vector||_inf = max_i(|v_i|)
typename dense_vector::value_type dense_vector::inf_norm() const
{
  using std::abs;
  using std::max;
  value_type result = 0;
  for (auto const& d : data_)
    result = max(result, value_type(abs(d)));
  return result;
}


// return v^T*v
typename dense_vector::value_type dense_vector::unary_dot() const
{
  value_type result = 0;
  for (auto const& d : data_)
    result += d*d;
  return result;
}


// return v^T*v2
typename dense_vector::value_type dense_vector::dot(dense_vector const& v2) const
{
  assert(v2.size() == size());
  value_type result = 0;
  for (size_type i = 0; i < size(); ++i)
    result += data_[i] * v2.data_[i];
  return result;
}

// construct a matrix from initializer lists
dense_matrix::dense_matrix(std::initializer_list<std::initializer_list<value_type>> l)
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
dense_matrix& dense_matrix::operator+=(dense_matrix const& that)
{
  assert(rows() == that.rows());
  assert(cols() == that.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += that.data_[i];
  return *this;
}


// perform update-assignment elementwise +=
dense_matrix& dense_matrix::operator-=(dense_matrix const& that)
{
  assert(rows() == that.rows());
  assert(cols() == that.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] -= that.data_[i];
  return *this;
}


// set all entries to v
dense_matrix& dense_matrix::operator=(value_type v)
{
  for (auto& A_ij : data_)
    A_ij = v;
  return *this;
}


// matrix-vector product A*x
dense_vector operator*(dense_matrix const& A, dense_vector const& x)
{
  using value_type = typename dense_matrix::value_type;
  dense_vector y(A.cols(), value_type(0));
  A.mult(x, y);
  return y;
}


// computes the matrix-vector product, y = Ax.
void dense_matrix::mult(dense_vector const& x, dense_vector& y) const
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
void dense_matrix::mult_add(dense_vector const& v1, dense_vector const& v2, dense_vector& v3) const
{
  assert(v1.size() == cols());
  assert(v2.size() == rows());
  assert(v3.size() == rows());
  for (size_type r = 0, rs = rows(); r < rs; ++r) {
    v3[r] = v2[r];
    value_type const* row = (*this)[r];
    for (size_type c = 0, cs = cols(); c < cs; ++c)
      v3[r] += row[c]*v1[c];
  }
}


// computes Y = a*X + Y.
void dense_matrix::axpy(value_type a, dense_matrix const& X)
{
  assert(rows() == X.rows());
  assert(cols() == X.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += a * X.data_[i];
}


// computes Y = a*Y + X.
void dense_matrix::aypx(value_type a, dense_matrix const& X)
{
  assert(rows() == X.rows());
  assert(cols() == X.cols());
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] = a * data_[i]  + X.data_[i];
}


// Setup a matrix according to a Laplacian equation on a 2D-grid using a five-point-stencil.
// Results in a matrix A of size (m*n) x (m*n)
void laplacian_setup(dense_matrix& A, std::size_t m, std::size_t n)
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
bool iteration::finished(real_type const& r)
{
  bool result = false;
  if (converged(r))
    result = finished_ = true;
  if (!result)
    result = check_max();
  print_resid();
  return result;
}


bool iteration::check_max()
{
  if (i_ >= max_iter_)
    error_ = 1, finished_ = true, err_msg_ = "Too many iterations.";
  return finished_;
}


bool iteration::converged() const
{
  if (norm_r0_ == 0)
    return resid_ <= atol_;  // ignore relative tolerance if |r0| is zero
  return resid_ <= rtol_ * norm_r0_ || resid_ <= atol_;
}


void iteration::print_resid()
{
  if (!quite_ && i_ % cycle_ == 0) {
    if (i_ != last_print_) { // Avoid multiple print-outs in same iteration
      std::cout << "iteration " << i_ << ": resid " << resid() << std::endl;
      last_print_ = i_;
    }
  }
}


int iteration::error_code() const
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
int cg(dense_matrix const& A, dense_vector& x, dense_vector const& b, iteration& iter)
{
  using std::abs;
  using Vector = dense_vector;
  using Scalar = typename dense_vector::value_type;
  using Real   = typename iteration::real_type;

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