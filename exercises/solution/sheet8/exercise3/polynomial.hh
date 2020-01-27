#pragma once

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

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

  Polynomial(std::vector<coeff_type> coefficients)
    : coefficients_(std::move(coefficients))
  {}

  // The degree of a polynomial, i.e. the highest of the degrees of its monomials
  // with non-zero coefficients. The zero-polynomial has by definition the degree -1
  // [[ensures: degree() < coefficients_.size()]]
  int degree() const;

  // return the i-th coefficient
  // if i > degree+1 then return 0
  coeff_type operator[](std::size_t i) const;

  // give write-access to the i-th coefficient
  // if coefficient i not yet allocated, resize container correspondingly
  coeff_type& operator[](std::size_t i);

  // Evaluation of the polynomial using Horner's method
  value_type operator()(value_type x) const;

  // adding two polynomial = adding coefficients
  Polynomial& operator+=(Polynomial const& p);

  // subtracting two polynomial = subtracting coefficients
  Polynomial& operator-=(Polynomial const& p);

  // Scaling of the coefficients of a polynomial by the given scalar factor
  Polynomial& operator*=(coeff_type factor);

  // Comparison of two polynomials (for almost_equal coefficients)
  bool operator==(Polynomial const& p) const;

  bool operator!=(Polynomial const& p) const
  {
    return !(*this == p);
  }

private:
  std::vector<coeff_type> coefficients_;
};


// Polynomial multiplication
Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs);

// adding two polynomial
inline Polynomial operator+(Polynomial lhs, Polynomial const& rhs)
{
  return lhs += rhs;
}

// subtracting two polynomial
inline Polynomial operator-(Polynomial lhs, Polynomial const& rhs)
{
  return lhs -= rhs;
}

// scaling a polynomial from the right
inline Polynomial operator*(Polynomial p, Polynomial::coeff_type factor)
{
  return p *= factor;
}

// scaling a polynomial from the left
inline Polynomial operator*(Polynomial::coeff_type factor, Polynomial p)
{
  return p *= factor;
}

// negation of the coefficients
inline Polynomial operator-(Polynomial p)
{
  return p *= Polynomial::coeff_type(-1);
}

// printing a polynomial
std::ostream& operator<<(std::ostream& out, Polynomial const& p);
