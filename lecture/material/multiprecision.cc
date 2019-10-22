#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>

// Type-alias for floating-point number with 50 decimal digits
using float_50 = boost::multiprecision::cpp_dec_float_50;

template <class T>
T area_of_a_circle(T r)
{
   using boost::math::constants::pi;
   return pi<T>() * r * r;
}

template <class T>
int digits() { return std::numeric_limits<T>::digits10; }

int main()
{
  float r_f = float(123) / 100;
  float a_f = area_of_a_circle(r_f);

  double r_d = double(123) / 100;
  double a_d = area_of_a_circle(r_d);

  float_50 r_mp = float_50(123) / 100;
  float_50 a_mp = area_of_a_circle(r_mp);

  // 4.75292
  std::cout << std::setprecision(digits<float>()) << a_f << std::endl;
  // 4.752915525616
  std::cout << std::setprecision(digits<double>()) << a_d << std::endl;
  // 4.7529155256159981904701331745635599135018975843146
  std::cout << std::setprecision(digits<float_50>()) << a_mp << std::endl;
}