#pragma once

#include <cassert>
#include <vector>

struct Matrix1
{
  // Default initialization
  // NOTE:
  // - The keyword `= default` means: use the default implementation for that function.
  // - The default implementation of the default constructor is: default-construct all
  //   members of the class.
  Matrix1() = default;

  // Initialize the Matrix1
  Matrix1(std::size_t r, std::size_t c, double value = 0.0);

  // Return the (i,j)th entry of the matrix
  // NOTE:
  // - implemented inline (keyword `inline` not necessary)
  // - Functions with just 1 line could be implemented "inline" in the class
  double access(std::size_t i, std::size_t j) const
  {
    return rows[i][j];
  }

  // Mutable access to the entry (i,j) of the matrix
  // NOTE: The only differences to the const access are
  // 1. return type is reference
  // 2. function is not const.
  // NOTE: implemented inline (keyword `inline` not necessary)
  double& access(std::size_t i, std::size_t j)
  {
    return rows[i][j];
  }

  // Access by the bracket operator
  // NOTE:
  // - implemented inline (keyword `inline` not necessary)
  // - The additional indirection by the call to `access` does not count, if
  //   that function is inlined by the compiler.
  double operator()(std::size_t i, std::size_t j) const
  {
    return access(i,j);
  }

  // An additional useful function is the *mutable* access to the data
  // NOTE: implemented inline (keyword `inline` not necessary)
  double& operator()(std::size_t i, std::size_t j)
  {
    return access(i,j);
  }

  // Accumulated plus operator
  Matrix1& operator+=(Matrix1 const& rhs);

  // The data of the matrix: row vectors
  std::vector<std::vector<double>> rows;
};

// Add the two matrices A and B and return the sum
// NOTE:
// - Here, the first argument is taken by value, since we need to create a copy anyway
// - An alternative signature would be (Matrix1 const& lhs, Matrix1 const& rhs)
// - Always try to implement the binary operators in terms of the compound assignment operators!
// - keyword `inline` is necessary, since implemented in a header file
inline Matrix1 operator+(Matrix1 lhs, Matrix1 const& rhs)
{
  return lhs += rhs;
}
