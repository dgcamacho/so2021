#include <concepts>
#include <cmath>
#include <array>
#include <iostream>

template <class A>
concept Array = requires (A a, typename A::size_type i) {
  { a.size() } -> std::integral;                                // compound requirement
  { a[i] }     -> std::convertible_to<typename A::value_type>;  // implicit type req.
};

template <class T>
concept Arithmetic = requires(T a, T b) {
  a + b;                            // simple requirement
  a - b;
  -a;
  requires std::totally_ordered<T>; // nested requirement
};

template <Array Point>              // constraint: `Point` must be model of `Array`
auto distance (Point const& a, Point const& b) {  // (a)
  std::cout << "(a)" << std::endl;
  typename Point::value_type result = 0.0;
  for (typename Point::size_type i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}

template <class T>
  requires Arithmetic<T>            // requires-clause
T distance (T const& a, T const& b) {             // (b)
  std::cout << "(b)" << std::endl;
  return std::abs(a - b);
}

template <Arithmetic T>
  requires std::unsigned_integral<T>  // concept refinement
T distance (T const& a, T const& b) {             // (c)
  std::cout << "(c)" << std::endl;
  return a > b ? a - b : b - a;
}

int main() {
  using Point = std::array<double,2>;

  Point a{1.0,2.0}, b{2.0,3.0};
  auto d1 = distance(a, b);       // (a)
  auto d2 = distance(1.0,2.0);    // (b)
  auto d3 = distance(1.0f,2.0f);  // (b)
  auto d4 = distance(1u,2u);      // (c)
}