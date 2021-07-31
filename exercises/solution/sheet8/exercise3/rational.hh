#pragma once
#include <cassert>
#include <iostream>

// Returns the greatest-common divisor of a and b
inline int gcd(int a, int b)
{
  return b == 0 ? (a < 0 ? -a : a)
                : gcd(b, a % b);
}

/// \brief Class representing the rational numbers a/b in fully reduced form with b>0
class Rational
{
public:

  // Initializing constructor gets numerator and a denominator
  Rational(int numerator = 1, int denominator = 1)
  {
    assign_reduced(numerator, denominator);
  }

public:  // arithmetic assignment operators

  Rational& operator*=(Rational const& rhs);

  Rational& operator/=(Rational const& rhs);

  Rational& operator+=(Rational const& rhs);

  Rational& operator-=(Rational const& rhs);

public: // access functions

  // Return the numerator value
  int numerator() const
  {
    return numerator_;
  }

  // Return the denominator value
  int denominator() const
  {
    return denominator_;
  }

public: // comparison operators

  bool operator==(Rational const& rhs) const
  {
    return numerator_ == rhs.numerator_ && denominator_ == rhs.denominator_;
  }

  bool operator!=(Rational const& rhs) const
  {
    return !(*this == rhs);
  }

private:
  // helper function to get fully reduced form of a/b
  Rational& assign_reduced(int const a, int const b);

private:
  // the numerator of the rational number numerator/denominator
  int numerator_ = 1;

  // the denominator of the rational number numerator/denominator
  int denominator_ = 1;
};


// binary arithmetic operators

inline Rational operator*(Rational lhs, Rational const& rhs)
{
  return lhs *= rhs;
}

inline Rational operator/(Rational lhs, Rational const& rhs)
{
  return lhs /= rhs;
}

inline Rational operator+(Rational lhs, Rational const& rhs)
{
  return lhs += rhs;
}

inline Rational operator-(Rational lhs, Rational const& rhs)
{
  return lhs -= rhs;
}

inline Rational operator-(Rational r)
{
  return r *= Rational(-1);
}

// The output operator << can be overloaded like any other function
// It gets as first argument the output stream by mutable reference and returns
// this reference. This is like a classical assignment operator.
inline std::ostream& operator<<(std::ostream& out, Rational const& r)
{
  return out << r.numerator() << '/' << r.denominator();
}
