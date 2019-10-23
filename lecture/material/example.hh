#ifndef EXAMPLE_HH
#define EXAMPLE_HH

// declaration and definition of a class
struct Point
{
  double x, y;

  // declaration of a member function
  Point subtract(Point other) const;
};

// declaration of a function
double distance(Point a, Point b);

// declaration of a template function
template <class T> void foo();

#include "example.impl.hh"
#endif // EXAMPLE_HH