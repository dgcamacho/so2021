#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "polynomial.hh"
#include "almost_equal.hh"

int Polynomial::degree() const
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


Polynomial::coeff_type Polynomial::operator[](std::size_t i) const
{
  return i < coefficients_.size() ? coefficients_[i] : coeff_type(0);
}


Polynomial::coeff_type& Polynomial::operator[](std::size_t i)
{
  if (i >= coefficients_.size())
    coefficients_.resize(i+1);
  return coefficients_[i];
}


Polynomial::value_type Polynomial::operator()(Polynomial::value_type x) const
{
  if (degree() < 0)
    return 0;

  int n = degree();
  value_type result = coefficients_[n];
  for (; n > 0; --n)
    result = coefficients_[n-1] + result*x;

  return result;
}


Polynomial& Polynomial::operator+=(Polynomial const& p)
{
  coefficients_.resize(std::max(degree(), p.degree())+1, coeff_type(0));
  for (int i = 0; i <= p.degree(); ++i)
    coefficients_[i] += p.coefficients_[i];
  return *this;
}


Polynomial& Polynomial::operator-=(Polynomial const& p)
{
  coefficients_.resize(std::max(degree(), p.degree())+1, coeff_type(0));
  for (int i = 0; i <= p.degree(); ++i)
    coefficients_[i] -= p.coefficients_[i];
  return *this;
}


Polynomial& Polynomial::operator*=(Polynomial::coeff_type factor)
{
  for (std::size_t i = 0; i < coefficients_.size(); ++i)
    coefficients_[i] *= factor;
  return *this;
}


bool Polynomial::operator==(Polynomial const& p) const
{
  int d = degree();
  if (d != p.degree())
    return false;

  for (int i = 0; i <= d; ++i)
    if (!almost_equal(coefficients_[i], p.coefficients_[i]))
      return false;

  return true;
}


Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs)
{
  int target_degree = lhs.degree() >= 0 && rhs.degree() >=0
    ? lhs.degree() + rhs.degree()
    : -1;

  Polynomial p(target_degree);
  for (int i = 0; i <= lhs.degree(); ++i)
    for (int j = 0; j <= rhs.degree(); ++j)
      p[i+j] = lhs[i]*rhs[j];

  return p;
}


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
