#pragma once

#include <cmath>
#include <numeric>
#include <vector>

class NumVector
    : private std::vector<double>
{
  using Base = std::vector<double>;

public:
  // construct a vector with given size and default value 0.0
  NumVector(std::size_t size)
    : Base(size, 0.0)
  {}

  // import operator[] from base class for element access
  using Base::operator[];

  // import size from base class
  using Base::size;

  // return the Euclidean norm of the vector
  double norm() const
  {
    return std::sqrt(std::accumulate(Base::begin(), Base::end(), 0.0,
      [](double result, double v_i) { return result + v_i*v_i; }));
  }
};
