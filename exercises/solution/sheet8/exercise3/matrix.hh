#pragma once

#include <vector>

class Matrix
{
public:
  using value_type = double;
  using size_type = std::size_t;

  // Default initialization
  Matrix() = default;

  // Initialize the Matrix
  Matrix(size_type r, size_type c, value_type value = 0.0);

  // Access by the bracket operator
  value_type operator()(size_type i, size_type j) const
  {
    return data_[i * cols_ + j];
  }

  // An additional useful function is the *mutable* access to the data
  value_type& operator()(size_type i, size_type j)
  {
    return data_[i * cols_ + j];
  }

  size_type num_rows() const
  {
    return rows_;
  }

  size_type num_cols() const
  {
    return cols_;
  }

  // Accumulated plus operator
  Matrix& operator+=(Matrix const& B);

  Matrix& operator*=(value_type factor);

  bool operator==(Matrix const& rhs) const;

  bool operator!=(Matrix const& rhs) const
  {
    return !(*this == rhs);
  }

private:
  // The number of rows in the matrix
  size_type rows_ = 0;
  // The number of columns in the matrix
  size_type cols_ = 0;

  // The data of the matrix: vector of concatenated rows
  std::vector<value_type> data_;
};

// Add the two matrices A and B and return the sum
inline Matrix operator+(Matrix lhs, Matrix const& rhs)
{
  return lhs += rhs;
}

// Negation of all matrix entries
inline Matrix operator-(Matrix m)
{
  return m *= Matrix::value_type(-1);
}
