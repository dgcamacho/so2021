#include <cassert>
#include <cmath>
#include <complex>
#include <initializer_list>
#include <string>
#include <vector>

namespace scprog
{
  /// A contiguous vector with vector-space operations
  class DenseVector
  {
  public:

    using size_type       = std::size_t;
    using value_type      = double;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;


  // ----- constructors / assignment -------------------------------------------
  public:

    /// default constructor, creates an empty vector of size 0
    DenseVector() = default;

    /// constructor of vector with size s and all entries initialized with value v
    explicit DenseVector(size_type s, value_type v = value_type{})
      : data_(s, v)
    {}

    /// constructor with vector entries initialized by initializer_list
    explicit DenseVector(std::initializer_list<value_type> l)
      : data_(l.begin(), l.end())
    {}

    /// set all entries of the vector to value v
    DenseVector& operator=(value_type v);

    /// resize vector to size s and fill new entries with value v
    void resize(size_type s, value_type v = value_type{})
    {
      data_.resize(s, v);
    }

    /// return the number of elements in the vector
    size_type size() const
    {
      return data_.size();
    }


  // ----- vector-space operations  --------------------------------------------
  public:

    /// perform update-assignment elementwise +=
    DenseVector& operator+=(DenseVector const& that);

    /// perform update-assignment elementwise +=
    DenseVector& operator-=(DenseVector const& that);

    /// perform update-assignment elementwise *= with a scalar
    DenseVector& operator*=(value_type s);

    /// perform update-assignment elementwise /= with a scalar
    DenseVector& operator/=(value_type s);


  // ----- element access functions  -------------------------------------------
  public:

    /// return a mutable reference to the vector entry v_i
    reference operator[](size_type i)
    {
      assert(i < data_.size());
      return data_[i];
    }

    /// return a const reference to the vector entry v_i
    const_reference operator[](size_type i) const
    {
      assert(i < data_.size());
      return data_[i];
    }


  // ----- binary operations  ---------------------------------------------------
  public:

    /// addition of two vectors
    friend DenseVector operator+(DenseVector lhs, DenseVector const& rhs)
    {
      return lhs += rhs;
    }

    /// subtraction of two vectors
    friend DenseVector operator-(DenseVector lhs, DenseVector const& rhs)
    {
      return lhs -= rhs;
    }

    /// multiplication of the vector with a scalar from the right, i.e. vec * s
    friend DenseVector operator*(DenseVector vec, value_type s)
    {
      return vec *= s;
    }

    /// multiplication of the vector with a scalar from the left, i.e. s * vec
    friend DenseVector operator*(value_type s, DenseVector vec)
    {
      return vec *= s;
    }

    /// computes Y = a*X + Y.
    void axpy(value_type a, DenseVector const& X);

    /// computes Y = a*Y + X.
    void aypx(value_type a, DenseVector const& X);


  // ----- reduction operators  ------------------------------------------------
  public:

    /// return the two-norm ||vector||_2 = sqrt(sum_i v_i^2)
    value_type two_norm() const;

    /// return the infinity-norm ||vector||_inf = max_i(|v_i|)
    value_type inf_norm() const;

    /// return v^T*v
    value_type unary_dot() const;

    /// return v^T*v2
    value_type dot(DenseVector const& v2) const;


  // ----- data members  -------------------------------------------------------
  private:

    std::vector<value_type> data_;
  };


  /// A dense matrix with row-wise contiguous storage and matrix-matrix as well as
  /// matrix-vector operations.
  class DenseMatrix
  {
  public:
    using size_type       = std::size_t;
    using value_type      = double;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;


  // ----- constructors / assignment -------------------------------------------
  public:

    /// default constructor, creates and empty matrix of size 0x0
    DenseMatrix() = default;

    /// constructor of matrix with rows r, columns c and all entries initialized with value v
    explicit DenseMatrix(size_type r, size_type c, value_type v = value_type{})
      : data_(r*c, v)
      , rows_(r)
      , cols_(c)
    {}

    /// constructor with matrix entries initialized by initializer_list
    explicit DenseMatrix(std::initializer_list<std::initializer_list<value_type>> l);

    /// set all entries to v
    DenseMatrix& operator=(value_type v);

    /// resize matrix to rows r and columns c and fill new entries with value v
    void resize(size_type r, size_type c, value_type v = value_type{})
    {
      data_.resize(r*c, v);
      rows_ = r;
      cols_ = c;
    }

    /// return the number of rows in the matrix
    size_type rows() const
    {
      return rows_;
    }

    /// return the number of columns in the matrix
    size_type cols() const
    {
      return cols_;
    }


  // ----- element access functions  -------------------------------------------
  public:

    /// access to i-th matrix row
    pointer operator[](size_type r)
    {
      assert(r < rows_);
      return data_.data() + cols_ * r;
    }

    /// access to i-th matrix row for constant matrices
    const_pointer operator[](size_type r) const
    {
      assert(r < rows_);
      return data_.data() + cols_ * r;
    }

    /// access to the (r,c)-th matrix element
    reference operator()(size_type r, size_type c)
    {
      return data_[cols_ * r + c];
    }

    /// access to the (r,c)-th matrix element (const variant)
    const_reference operator()(size_type r, size_type c) const
    {
      return data_[cols_ * r + c];
    }


  // ----- binary operations  ---------------------------------------------------
  public:

    /// perform update-assignment elementwise +=
    DenseMatrix& operator+=(DenseMatrix const& that);

    /// perform update-assignment elementwise +=
    DenseMatrix& operator-=(DenseMatrix const& that);

    /// addition of two matrices
    friend DenseMatrix operator+(DenseMatrix lhs, DenseMatrix const& rhs)
    {
      return lhs += rhs;
    }

    /// subtraction of two matrices
    friend DenseMatrix operator-(DenseMatrix lhs, DenseMatrix const& rhs)
    {
      return lhs -= rhs;
    }

    /// matrix vector product A*x
    friend DenseVector operator*(DenseMatrix const& A, DenseVector const& x);

    /// computes the matrix-vector product, y = Ax.
    void mult(DenseVector const& x, DenseVector& y) const;

    /// computes v3 = v2 + A * v1.
    void mult_add(DenseVector const& v1, DenseVector const& v2, DenseVector& v3) const;

    /// computes Y = a*X + Y.
    void axpy(value_type a, DenseMatrix const& X);

    /// computes Y = a*Y + X.
    void aypx(value_type a, DenseMatrix const& X);


  // ----- data members  -------------------------------------------------------
  private:

    std::vector<value_type> data_;
    size_type rows_ = 0;
    size_type cols_ = 0;
  };


  /// Setup a matrix according to a Laplacian equation on a 2D-grid using a five-point-stencil.
  /// Results in a matrix A of size (m*n) x (m*n)
  void laplacian_setup(DenseMatrix& A, std::size_t m, std::size_t n);


  /// Basic utility class to control iterative solvers
  class BasicIteration
  {
    using self = BasicIteration;

  public:
    using real_type = double;

    /// Constructor
    /**
     * \param r0        initial residual r0 = b - A*x
     * \param max_iter  the maximal number of solver iterations
     * \param rtol      relative tolerance: |b - A*x| < rtol * |r0|
     * \param atol      absolute tolerance: |b - A*x| < atol
     * \param cycle     the print cycle of the solver iterations
     **/
    template <class Vector>
    BasicIteration(Vector const& r0, int max_iter, real_type rtol, real_type atol = real_type(0), int cycle = 100)
      : norm_r0_(std::abs(r0.two_norm()))
      , max_iter_(max_iter)
      , cycle_(cycle)
      , rtol_(rtol)
      , atol_(atol)
    {}

    /// Constructor
    /**
     * \param nb        initial residual norm nb = |b - A*x|
     * \param max_iter  the maximal number of solver iterations
     * \param rtol      relative tolerance: |b - A*x| < rtol * nb
     * \param atol      absolute tolerance: |b - A*x| < atol
     * \param cycle     the print cycle of the solver iterations
     **/
    BasicIteration(real_type nb, int max_iter, real_type rtol, real_type atol = real_type(0), int cycle = 100)
      : norm_r0_(nb)
      , max_iter_(max_iter)
      , cycle_(cycle)
      , rtol_(rtol)
      , atol_(atol)
    {}

    /// Iteration finished according to residual value r
    bool finished(real_type const& r);

    /// Iteration finished according to complex residual value r
    template <class T>
    bool finished(std::complex<T> const& r)
    {
      using std::abs;
      return finished(abs(r));
    }

    /// Iteration finished according to the norm of r
    template <class Vector>
    bool finished(const Vector& r)
    {
      return finished(r.two_norm());
    }

    /// Iteration finished according to last provided residual
    bool finished() const { return finished_; }

    template <class T>
    int terminate(T const& r) { finished(r); return error_; }


  private:

    bool check_max();

    bool converged() const;

    bool converged(real_type const& r) { resid_ = r; return converged(); }

    void print_resid();

  public:

    /// Increment counter
    self& operator++() { ++i_; return *this; }

    /// Increment counter by n
    self& operator+=(int n) { i_ += n; return *this; }

    /// Is first iteration?
    bool first() const { return i_ <= 1; }

    /// Conversion to int returns error code
    operator int() const { return error_code(); }

    /// Error code
    int error_code() const;

    /// Reached tolerance without error
    bool is_converged() const { return finished_ && error_ == 0; }

    /// Already performed iterations
    int iterations() const { return i_; }

    /// Maximal number of iterations
    int max_iterations() const { return max_iter_; }

    /// Set maximal number of iterations
    void set_max_iterations(int m) { max_iter_ = m; }

    /// Reset the iteration number
    void restart() { i_ = 0; }

    /// Last residuum
    real_type resid() const { return resid_; }

    /// Last residuum compared with initial one
    real_type relresid() const { return resid_ / norm_r0_; }

    /// Initial residual
    real_type norm_r0() const { return norm_r0_; }

    /// Reset initial residual
    void set_norm_r0(real_type r0) { norm_r0_ = r0; }

    /// Relative tolerance
    real_type rtol() const { return rtol_; }

    /// Absolute tolerance
    real_type atol() const { return atol_; }

    /// Fail with error code
    int fail(int err_code) { error_ = err_code; return error_code(); }

    /// Fail with error code and message
    int fail(int err_code, const std::string& msg)
    {
      error_ = err_code;
      err_msg_ = msg;
      return error_code();
    }

    /// Turn logging off (or on)
    void set_quite(bool q) { quite_ = q; }

    /// Is logging turned off
    bool is_quite() const { return quite_; }

    /// Suppress final resume
    void suppress_resume(bool s) { suppress_ = s; }

    /// Is final resume suppressed
    bool resume_suppressed() const { return suppress_; }

    void update_progress(BasicIteration const& that)
    {
      i_ = that.i_;
      resid_= that.resid_;
      if (that.error_ > 1) { // copy error except too many iterations
        error_ = that.error_;
        err_msg_= that.err_msg_;
        finished_ = true;
      } else
        finished(resid_);
    }

  protected:
    real_type norm_r0_;
    int error_ = 0, i_ = 0, max_iter_ = 1000, cycle_ = 100, last_print_ = -1;
    real_type rtol_, atol_, resid_;
    std::string err_msg_;
    bool finished_ = false, quite_ = false, suppress_ = false, multi_print_ = false;
  };


  /// Apply the conjugate gradient algorithm to the linear system A*x = b and return an error code
  /**
   * \param A  The system matrix
   * \param x  The solution vector. Must be of correct size.
   * \param b  The load vector of the linear system
   * \param iter  An iteration object controlling number of iterations and break tolerances.
   *
   * \return The error code of the \ref BasicIteration object. err=0 means no error.
   **/
  int cg(DenseMatrix const& A, DenseVector& x, DenseVector const& b, BasicIteration& iter);


} // end namespace scprog