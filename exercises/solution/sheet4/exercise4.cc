#include <cassert>
#include <iostream>

int gcd(int a, int b)
{
  return b == 0 ? a : gcd(b, a % b);
}

class Rational
{
public:
  Rational() = default;
  Rational(int numerator, int denominator = 1)
  {
    assign_normalized(numerator, denominator);
  }

public:  // arithmetic assignment operators

  Rational& operator*=(Rational const& rhs)
  {
    int const a = numerator_ * rhs.numerator_;
    int const b = denominator_ * rhs.denominator_;
    assign_normalized(a,b);
    return *this;
  }

  Rational& operator/=(Rational const& rhs)
  {
    int const a = numerator_ * rhs.denominator_;
    int const b = denominator_ * rhs.numerator_;
    assign_normalized(a,b);
    return *this;
  }

  Rational& operator+=(Rational const& rhs)
  {
    int const a = numerator_ * rhs.denominator_ + rhs.numerator_ * denominator_;
    int const b = denominator_ * rhs.denominator_;
    assign_normalized(a,b);
    return *this;
  }

  Rational& operator-=(Rational const& rhs)
  {
    int const a = numerator_ * rhs.denominator_ - rhs.numerator_ * denominator_;
    int const b = denominator_ * rhs.denominator_;
    assign_normalized(a,b);
    return *this;
  }

public: // comparison operators

  bool operator==(Rational const& rhs) const
  {
    return numerator_ == rhs.numerator_ && denominator_ == rhs.denominator_;
  }

private:
  void assign_normalized(int const a, int const b)
  {
    assert(b != 0);
    if (b < 0)
      assign_normalized(-a, -b);

    int const d = gcd(a, b);
    numerator_ = a / d;
    denominator_ = b / d;
  }

private:
  int numerator_ = 1;
  int denominator_ = 1;
};


// binary arithmetic operators

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


int main()
{
  Rational f1(-3, 12), f2(4, 3), f3(0, 1);

  assert(f1 + f2 == Rational(13,12));
  assert(f1 * f2 == Rational(-1,3));
  assert(4 + f2 == Rational(16,3));
  assert(f2 + 5 == Rational(19,3));
  assert(12 * f1 == Rational(-3,1));
  assert(f1 * 6 == Rational(-3,2));
  assert(f1 / f2 == Rational(-3,16));
}