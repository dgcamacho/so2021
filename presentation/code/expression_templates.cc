#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>

template <class E>
struct Expr
{
  // Element access
  auto operator[] (std::size_t const i) const
  {
    return static_cast<E const&>(*this).access_impl(i);
  }

  auto& operator[] (std::size_t const i)
  {
    return static_cast<E&>(*this).access_impl(i);
  }

  // Length of the vector expression
  auto size () const
  {
    return static_cast<E const&>(*this).size_impl();
  }

protected:
  Expr () = default;
};

template <class Functor, class A, class B>
class BinaryExpr : public Expr< BinaryExpr<Functor,A,B> >
{
  Functor f_;
  A const& a_;
  B const& b_;
public:
  BinaryExpr (Functor f, A const& a, B const& b)
    : f_(f), a_(a), b_(b)
  {
    assert(a_.size() == b_.size());
  }

  // implementation of element access
  double access_impl (std::size_t i) const { return f_( a_[i], b_[i] ); }

  // implementation of size information
  auto size_impl () const { return a_.size(); }
};

struct Vector : public Expr<Vector>
{
  std::size_t size_ = 0;
  double* data_ = nullptr;

  Vector (std::size_t const size)
    : size_(size)
    , data_(size > 0 ? new double[size] : nullptr)
  {}

  ~Vector () { delete[] data_; }

  Vector (Vector const& other)
    : Vector(other.size_)
  {
    //std::cout << "copy-constructor" << std::endl;
    std::copy(other.data_, other.data_+other.size_, this->data_);
  }

  template <class E>
  Vector (Expr<E> const& expr)  // construction from expression
    : Vector(expr.size())
  {
    for (std::size_t i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] = expr[i];
  }

  Vector& operator= (Vector other)
  {
    //std::cout << "assignment operator" << std::endl;
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
    return *this;
  }

  Vector& operator+= (Vector const& other)
  {
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] += other.data_[i];
    return *this;
  }

  template <class E>
  Vector& operator= (Expr<E> const& expr)
  {
    assert(size_ == expr.size());
    for (std::size_t i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] = expr[i];
    return *this;
  }

  template <class E>
  Vector& operator+= (Expr<E> const& expr)
  {
    assert(size_ == expr.size());
    for (std::size_t i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] += expr[i];
    return *this;
  }

  double  access_impl (std::size_t i) const { return data_[i]; }
  double& access_impl (std::size_t i)       { return data_[i]; }

  std::size_t size_impl () const { return size_; }
};



struct Plus {
  template <class T1, class T2>
  auto operator() (T1 const& x, T2 const& y) const { return x + y; }
};

template <class A, class B>
auto operator+ (Expr<A> const& a, Expr<B> const& b)
{
  return BinaryExpr{Plus{}, a, b};
}


int main ()
{
  Vector a{10}, b{10}, c{10};

  Vector sum = a + b + c;
}