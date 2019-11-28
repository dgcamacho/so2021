#include <cassert>
#include <vector>

#include "exercise3b.hh"

// Add the two matrices A and B and return the sum
Matrix2 operator+(Matrix2 lhs, Matrix2 const& rhs)
{
  return lhs += rhs;
}


// NOTE:
// - default values for function parameters should not be repeated in the function definition.
// - in the constructor, all class members are (default) initialized, if not specified otherwise. Thus
//   not clear of the rows is necessary
// - Here, the number of rows and number of columns are set in a constructor *initializer list*,
//   introduced with the `:` symbol after the constructor parameter list.
Matrix2::Matrix2(std::size_t r, std::size_t c, double value)
  : rows_(r)
  , cols_(c)
{
  data_.resize(rows_*cols_, value);
}


// NOTE:
// - assignment operators should always return a reference, since one wants to
//   chain those operators, e.g. A += B += C += D ...
Matrix2& Matrix2::operator+=(Matrix2 const& B)
{
  assert(data_.size() == B.data_.size());
  assert(rows_ == B.rows_);
  assert(cols_ == B.cols_);

  for (std::size_t i = 0; i < data_.size(); ++i)
    data_[i] += B.data_[i];

  return *this; // return a reference to the class instance
}
