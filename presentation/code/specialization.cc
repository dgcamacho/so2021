#include <cmath>
#include <array>

template <typename Point>
auto distance (Point const& a, Point const& b) -> decltype((std::size_t(a.size()), double(a[0]))) {
  double result = 0.0;
  for (std::size_t i = 0; i < a.size(); ++i)
    result += (a[i] - b[i]) * (a[i] - b[i]);
  return std::sqrt(result);
}

// function overloading:
double distance (double a, double b) {
  return std::abs(a-b);
}

int main()
{
  using Point = std::array<double,2>;
  Point a{1.0,2.0}, b{2.0,3.0};

  distance(a,b);
  distance(1.0,2.0);
  distance(1.0f, 2.0f);
}