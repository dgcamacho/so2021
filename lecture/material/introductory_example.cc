#include <iostream> // for std::cout
#include <cmath>    // for std::sqrt

// Structure defining the vector space
struct Vector
{
  double x, y;

  Vector operator-(Vector const& that) const {
    return {this->x - that.x, this->y - that.y}; // pointer vs. reference
  }
};

double dot(Vector const& a, Vector const& b) {
  return a.x * b.x + a.y * b.y; // operator precedence!
}

double two_norm(Vector const& a) {
  return std::sqrt(dot(a,a));
}

/*
  Distance of two points
  */
double distance(Vector const& a, Vector const& b) {
  return two_norm(a - b);
}

int main() { // or int main(int argc, char** argv)
  Vector a{ 1.0, 2.0 };
  Vector b{ 7.0,-1.5 };

  std::cout << "distance of a and b = " << distance(a,b) << std::endl;
  return 0;
}