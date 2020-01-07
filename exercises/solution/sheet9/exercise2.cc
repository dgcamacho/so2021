#include <iostream>
#include <vector>
#include "Timer.hh"

/// Numerical vector class derives from std::vector for data storage
class Vector
    : public std::vector<double>
{
  using Super = std::vector<double>;

public:
  // Import the constructors of std::vector
  using Super::Super;

  // Assignment of the sum
  Vector& operator+=(Vector const& that)
  {
    for (std::size_t i = 0; i < size(); ++i)
      (*this)[i] += that[i];

    return *this;
  }

  // Assignment of the difference
  Vector& operator-=(Vector const& that)
  {
    for (std::size_t i = 0; i < size(); ++i)
      (*this)[i] -= that[i];

    return *this;
  }

  // Scaling of the vector entries
  Vector& operator*=(double scalar)
  {
    for (std::size_t i = 0; i < size(); ++i)
      (*this)[i] *= scalar;

    return *this;
  }
};

// Returns lhs + rhs
Vector operator+(Vector lhs, Vector const& rhs)
{
  return lhs += rhs;
}

// Returns lhs - rhs
Vector operator-(Vector lhs, Vector const& rhs)
{
  return lhs += rhs;
}

// Returns vec * scalar
Vector operator*(Vector vec, double scalar)
{
  return vec *= scalar;
}

// Returns scalar * vec
Vector operator*(double scalar, Vector vec)
{
  return vec *= scalar;
}

// Returns (vec1 + vec2) * scalar
Vector add_scale(Vector const& vec1, Vector const& vec2, double scalar)
{
  Vector result(vec1.size());
  for (std::size_t i = 0; i < vec1.size(); ++i)
    result[i] = (vec1[i] + vec2[i]) * scalar;
  return result;
}

// Returns vec1 + vec2 + vec3 + vec4 + vec5
Vector add5(Vector const& vec1, Vector const& vec2, Vector const& vec3, Vector const& vec4, Vector const& vec5)
{
  Vector result(vec1.size());
  for (std::size_t i = 0; i < vec1.size(); ++i)
    result[i] = vec1[i] + vec2[i] + vec3[i] + vec4[i] + vec5[i];
  return result;
}

int main()
{
  scprog::Timer t;

  const std::size_t n = 1e7;
  Vector vec1(n, 1.0), vec2(n, 2.0), vec3(n, 3.0), vec4(n, 4.0), vec5(n, 5.0);

  const std::size_t repeat = 50;

  // Test 1
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    Vector result = vec1 + vec2;
  std::cout << "time(vec1 + vec2) = " << t.elapsed() / repeat << std::endl;

  // Test 2
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    vec1 += vec2;
  std::cout << "time(vec1 += vec2) = " << t.elapsed() / repeat << std::endl;

  // Test 3
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    Vector result = (vec1 + vec2) * 2;
  std::cout << "time((vec1 + vec2) * 2) = " << t.elapsed() / repeat << std::endl;

  // Test 4
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    Vector result = vec1 + vec2 + vec3 + vec4 + vec5;
  std::cout << "time(vec1 + vec2 + vec3 + vec4 + vec5) = " << t.elapsed() / repeat << std::endl;

  // Test 3a
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    Vector result = add_scale(vec1, vec2, 2);
  std::cout << "time(add_scale(vec1, vec2, 2)) = " << t.elapsed() / repeat << std::endl;

  // Test 4a
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    Vector result = add5(vec1, vec2, vec3, vec4, vec5);
  std::cout << "time(add5(vec1, vec2, vec3, vec4, vec5)) = " << t.elapsed() / repeat << std::endl;

  // Test 4b
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r) {
    Vector result = vec1 + vec2;
    result += vec3;
    result += vec4;
    result += vec5;
  }
  std::cout << "time((((vec1 + vec2) += vec3) += vec4) += vec5) = " << t.elapsed() / repeat << std::endl;


  std::cout << std::endl;
  std::cout << "preallocate storage for result:" << std::endl;

  Vector result(n);

  // Test 1'
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    result = vec1 + vec2;
  std::cout << "time(vec1 + vec2) = " << t.elapsed() / repeat << std::endl;

  // Test 3'
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    result = (vec1 + vec2) * 2;
  std::cout << "time((vec1 + vec2) * 2) = " << t.elapsed() / repeat << std::endl;

  // Test 4'
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    result = vec1 + vec2 + vec3 + vec4 + vec5;
  std::cout << "time(vec1 + vec2 + vec3 + vec4 + vec5) = " << t.elapsed() / repeat << std::endl;

  // Test 3a'
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    result = add_scale(vec1, vec2, 2);
  std::cout << "time(add_scale(vec1, vec2, 2)) = " << t.elapsed() / repeat << std::endl;

  // Test 4a'
  t.reset();
  for (std::size_t r = 0; r < repeat; ++r)
    result = add5(vec1, vec2, vec3, vec4, vec5);
  std::cout << "time(add5(vec1, vec2, vec3, vec4, vec5)) = " << t.elapsed() / repeat << std::endl;
}