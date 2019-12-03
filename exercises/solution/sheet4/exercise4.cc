#include <cassert>
#include <iostream>

// Returns the greatest-common divisor of a and b
// NOTE:
// - returns 0 if a == 0 && b == 0
// - always returns a non-negative number
inline int gcd(int a, int b)
{
  return b == 0 ? (a < 0 ? -a : a)
                : gcd(b, a % b);
}

/// \brief Class representing the rational numbers a/b in fully reduced form with b>0
/**
 * Rational numbers are represented by the pair (numerator, denominator) of integers. The
 * fully reduced form (or irreducible fraction) is a fraction in which the numerator and
 * denominator are integers that have no other common divisors than 1.
 * Additionally we unify the fraction by enforcing the denominator to be always positive.
 **/
class Rational
{
public:

  // Initializing constructor gets numerator and a denominator
  Rational(int numerator = 1, int denominator = 1)
  {
    assign_reduced(numerator, denominator);
  }

public:  // arithmetic assignment operators

  // NOTE:
  // - members of the argument can be accessed directly, if the argument type is of the same type as the class
  // - outsource the normalization/reduction to reduced form to a separate function!
  // - in any assignment operators, return a reference to the class!
  // - the reference to the class can be obtained as the de-referenced pointer `this` pointing to the instance of that class
  Rational& operator*=(Rational const& rhs)
  {
    auto const a = numerator_ * rhs.numerator_;
    auto const b = denominator_ * rhs.denominator_;
    return assign_reduced(a,b);
  }

  Rational& operator/=(Rational const& rhs)
  {
    auto const a = numerator_ * rhs.denominator_;
    auto const b = denominator_ * rhs.numerator_;
    return assign_reduced(a,b);
  }

  Rational& operator+=(Rational const& rhs)
  {
    auto const a = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
    auto const b = denominator_ * rhs.denominator_;
    return assign_reduced(a,b);
  }

  Rational& operator-=(Rational const& rhs)
  {
    auto const a = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
    auto const b = denominator_ * rhs.denominator_;
    return assign_reduced(a,b);
  }

public: // access functions

  // Return the numerator value
  // NOTE:
  // - this function is marked const, since we do not change any class member.
  int numerator() const
  {
    return numerator_;
  }

  int denominator() const
  {
    return denominator_;
  }

public: // comparison operators

  // NOTE:
  // - comparison operators always return a bool
  // - a simple comparison does not change the members of the class, so mark it `const`
  // - we can just compare numerator and denominator, since we are in fully reduced form
  bool operator==(Rational const& rhs) const
  {
    return numerator_ == rhs.numerator_ && denominator_ == rhs.denominator_;
  }

private:
  // helper function to get fully reduced form of a/b
  // NOTE:
  // - since this is an assignment function, return a reference to the class
  Rational& assign_reduced(int const a, int const b)
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

private:
  // the numerator of the rational number numerator/denominator
  // NOTE:
  // - I use a trailing underscore to highlight member variables. This is just a personal style.
  //   Alternatives could be `_numerator` or `m_numerator` or just `numerator`.
  int numerator_ = 1;

  // the denominator of the rational number numerator/denominator
  int denominator_ = 1;
};


// binary arithmetic operators
// NOTE: all implemented using the compound assignment operators

Rational operator*(Rational lhs, Rational const& rhs)
{
  return lhs *= rhs;
}

Rational operator/(Rational lhs, Rational const& rhs)
{
  return lhs /= rhs;
}

Rational operator+(Rational lhs, Rational const& rhs)
{
  return lhs += rhs;
}

Rational operator-(Rational lhs, Rational const& rhs)
{
  return lhs -= rhs;
}

// The output operator << can be overloaded like any other function
// It gets as first argument the output stream by mutable reference and returns
// this reference. This is like a classical assignment operator.
std::ostream& operator<<(std::ostream& out, Rational const& r)
{
  return out << r.numerator() << '/' << r.denominator();
}


int main()
{
  // 1. test the gcd function
  assert(gcd(12,18) == 6);
  assert(gcd(12,-18) == 6);
  assert(gcd(-12,18) == 6);
  assert(gcd(18,12) == 6);
  assert(gcd(18,-12) == 6);
  assert(gcd(-18,12) == 6);
  assert(gcd(0,6) == 6);
  assert(gcd(6,0) == 6);
  assert(gcd(0,0) == 0);

  // 2. test the Rational numbers class
  Rational f1(-3, 12), f2(4, 3), f3(0, 1);

  assert(f1 + f2 == Rational(13,12));
  assert(f1 * f2 == Rational(-1,3));
  assert(4 + f2  == Rational(16,3));
  assert(f2 + 5  == Rational(19,3));
  assert(12 * f1 == Rational(-3,1));
  assert(f1 * 6  == Rational(-3,2));
  assert(f1 / f2 == Rational(-3,16));

  // 3. print all fractions
  std::cout << "f1 + f2 = " << f1 << " + " << f2 << " = " << (f1 + f2) << std::endl;
  std::cout << "f1 * f2 = " << f1 << " * " << f2 << " = " << (f1 * f2) << std::endl;
  std::cout << "4 + f2  = " << 4  << " + " << f2 << " = " << (4 + f1)  << std::endl;
  std::cout << "f2 + 5  = " << f2 << " + " << 5  << " = " << (f2 + 5)  << std::endl;
  std::cout << "12 * f1 = " << 12 << " * " << f1 << " = " << (12 * f2) << std::endl;
  std::cout << "f1 * 6  = " << f1 << " * " << 6  << " = " << (f1 * 6)  << std::endl;
  std::cout << "f1 / f2 = " << f1 << " / " << f2 << " = " << (f1 / f2) << std::endl;
  std::cout << "f3 = " << f3 << std::endl;
}