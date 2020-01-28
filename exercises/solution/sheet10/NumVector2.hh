#pragma once

#include <cmath>
#include <numeric>
#include <vector>

class NumVector
{
public:
  // construct a vector with given size and default value 0.0
  NumVector(std::size_t size)
    : data_(size, 0.0)
  {}

  // element access
  decltype(auto) operator[](std::size_t i) { return data_[i]; }
  decltype(auto) operator[](std::size_t i) const { return data_[i]; }

  // return the number of elements in the vector
  std::size_t size() const { return data_.size(); }

  // return the Euclidean norm of the vector
  double norm() const
  {
    return std::sqrt(std::accumulate(data_.begin(), data_.end(), 0.0,
      [](double result, double v_i) { return result + v_i*v_i; }));
  }

private:
  std::vector<double> data_;
};
