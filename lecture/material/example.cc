#include "example.hh"
#include <cmath>

// definition of a member function
Point Point::subtract(Point other) const
{
  return {this->x - other.x, this->y - other.y};
}

// definition of the function distance()
double distance(Point a, Point b)
{
  Point ab = a.subtract(b);
  return std::sqrt(ab.x * ab.x + ab.y * ab.y);
}

int main(int argc, char** argv)
{
  Point a{ 1.0, 2.0 }, b{ 7.0,-1.5 };
  distance(a,b);
  return 0;
}