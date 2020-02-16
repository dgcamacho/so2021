#pragma once

#include <cmath>
#include <limits>
#include <utility>

// floating-point comparison
template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp = 2)
{
  return std::abs(x-y) <= std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
      // unless the result is subnormal
      || std::abs(x-y) < std::numeric_limits<T>::min();
}

// integer comparison
template <class T>
typename std::enable_if< std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp = 2)
{
  return x == y;
}
