#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

// floating-point comparison
template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp = 2)
{
  return std::abs(x-y) <= std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
      // unless the result is subnormal
      || std::abs(x-y) < std::numeric_limits<T>::min();
}

// integer comparison
template <class T>
typename std::enable_if< std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp = 2)
{
  return x == y;
}


class Polynomial
{
public:
  using coeff_type = double;
  using value_type = double;

  /// Default constructor, generates a zero-polynomial
  Polynomial(int degree = -1)
    : coefficients_(std::max(0,degree+1), coeff_type(0))
  {}

  /// Constructor with a list of coefficients
  Polynomial(std::initializer_list<coeff_type> const& coefficients)
    : coefficients_(coefficients)
  {}

  // The degree of a polynomial, i.e. the highest of the degrees of its monomials
  // with non-zero coefficients. The zero-polynomial has by definition the degree -1
  // [[ensures: degree() < coefficients_.size()]]
  int degree() const
  {
    int deg = -1;
    for (int i = coefficients_.size()-1; i >= 0; --i) {
      if (coefficients_[i] != coeff_type(0)) {
        deg = i;
        break;
      }
    }

    assert(deg < int(coefficients_.size())); // post-condition
    return deg;
  }

  // return the i-th coefficient
  // if i > degree+1 then return 0
  coeff_type operator[](std::size_t i) const
  {
    return i < coefficients_.size() ? coefficients_[i] : coeff_type(0);
  }

  // give write-access to the i-th coefficient
  // if coefficient i not yet allocated, resize container correspondingly
  coeff_type& operator[](std::size_t i)
  {
    if (i >= coefficients_.size())
      coefficients_.resize(i+1);
    return coefficients_[i];
  }

  // Evaluation of the polynomial using Horner's method
  value_type operator()(value_type x) const
  {
    if (degree() < 0)
      return 0;

    int n = degree();
    value_type result = coefficients_[n];
    for (; n > 0; --n)
      result = coefficients_[n-1] + result*x;

    return result;
  }

  // adding two polynomial = adding coefficients
  Polynomial& operator+=(Polynomial const& p)
  {
    coefficients_.resize(std::max(degree(), p.degree())+1, coeff_type(0));
    for (int i = 0; i <= p.degree(); ++i)
      coefficients_[i] += p.coefficients_[i];
    return *this;
  }

  // subtracting two polynomial = subtracting coefficients
  Polynomial& operator-=(Polynomial const& p)
  {
    coefficients_.resize(std::max(degree(), p.degree())+1, coeff_type(0));
    for (int i = 0; i <= p.degree(); ++i)
      coefficients_[i] -= p.coefficients_[i];
    return *this;
  }

  // Scaling of the coefficients of a polynomial by the given scalar factor
  Polynomial& operator*=(coeff_type factor)
  {
    for (std::size_t i = 0; i < coefficients_.size(); ++i)
      coefficients_[i] *= factor;
    return *this;
  }

  // Comparison of two polynomials (for almost_equal coefficients)
  bool operator==(Polynomial const& p) const
  {
    int d = degree();
    if (d != p.degree())
      return false;

    for (int i = 0; i <= d; ++i)
      if (!almost_equal(coefficients_[i], p.coefficients_[i]))
        return false;

    return true;
  }

  bool operator!=(Polynomial const& p) const
  {
    return !(*this == p);
  }

private:
  std::vector<coeff_type> coefficients_;
};


// Polynomial multiplication
Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs)
{
  int target_degree = lhs.degree() >= 0 && rhs.degree() >=0
    ? lhs.degree() + rhs.degree()
    : 0;

  Polynomial p(target_degree);
  for (int i = 0; i <= lhs.degree(); ++i)
    for (int j = 0; j <= rhs.degree(); ++j)
      p[i+j] = lhs[i]*rhs[j];

  return p;
}

// adding two polynomial
Polynomial operator+(Polynomial lhs, Polynomial const& rhs)
{
  return lhs += rhs;
}

// subtracting two polynomial
Polynomial operator-(Polynomial lhs, Polynomial const& rhs)
{
  return lhs -= rhs;
}

// scaling a polynomial from the right
Polynomial operator*(Polynomial p, Polynomial::coeff_type factor)
{
  return p *= factor;
}

// scaling a polynomial from the left
Polynomial operator*(Polynomial::coeff_type factor, Polynomial p)
{
  return p *= factor;
}

// printing a polynomial
std::ostream& operator<<(std::ostream& out, Polynomial const& p)
{
  // special handling of the zero polynomial
  if (p.degree() < 0)
    return out << "0";

  bool first = true;
  for (int i = 0; i <= p.degree(); ++i) {
    // skip coefficients that are zero
    if (p[i] == 0.0)
      continue;

    if (!first)
      out << " + ";
    out << p[i];
    first = false;

    // add monomial in the output (only for exponent > 0)
    if (i == 1)
      out << "x";
    else if (i > 1)
      out << "x^" << i;
  }
  return out;
}

int main()
{
  Polynomial p{0.0, 2.0, 0.0, 4.0, 5.0};
  Polynomial q{2.0, 0.0, 1.0, 2.0};

  std::cout << "p = " << p << "\n";
  std::cout << "q = " << q << "\n";
  std::cout << "p*q = " << p*q << "\n";

  p[10] = 7;
  std::cout << "p = " << p << "\n";
  std::cout << "p.degree = " << p.degree() << "\n";

  std::cout << "2*p = " << 2*p << "\n";

  Polynomial zero;
  std::cout << "zero = " << zero << "\n";
  std::cout << "zero.degree = " << zero.degree() << "\n";
  std::cout << "zero + p = " << zero + p << "\n";
  std::cout << "p + zero = " << p + zero << "\n";

  double x = 1;
  std::cout << "zero(1) = " << zero(x) << "\n";
  std::cout << "p(1) = " << p(x) << "\n";

  assert(p != zero);
  assert(zero != p);

  assert(p == p);

  Polynomial p0{0.0, 0.0, 0.0};
  assert(p0 == zero);
}
