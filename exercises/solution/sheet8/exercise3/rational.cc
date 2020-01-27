#include "rational.hh"

Rational& Rational::operator*=(Rational const& rhs)
{
  auto const a = numerator_ * rhs.numerator_;
  auto const b = denominator_ * rhs.denominator_;
  return assign_reduced(a,b);
}


Rational& Rational::operator/=(Rational const& rhs)
{
  auto const a = numerator_ * rhs.denominator_;
  auto const b = denominator_ * rhs.numerator_;
  return assign_reduced(a,b);
}


Rational& Rational::operator+=(Rational const& rhs)
{
  auto const a = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
  auto const b = denominator_ * rhs.denominator_;
  return assign_reduced(a,b);
}


Rational& Rational::operator-=(Rational const& rhs)
{
  auto const a = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
  auto const b = denominator_ * rhs.denominator_;
  return assign_reduced(a,b);
}


Rational& Rational::assign_reduced(int const a, int const b)
{
  if (b < 0)
    return assign_reduced(-a, -b);

  assert(b != 0);
  auto const divisor = gcd(a, b);
  assert(divisor != 0); // since b != 0, the divisor is also != 0
  numerator_   = a / divisor;
  denominator_ = b / divisor;
  return *this;
}
