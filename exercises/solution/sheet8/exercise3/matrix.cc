#include <cassert>

#include "matrix.hh"
#include "almost_equal.hh"

Matrix::Matrix(Matrix::size_type r, Matrix::size_type c, Matrix::value_type value)
  : rows_(r)
  , cols_(c)
{
  data_.resize(rows_*cols_, value);
}


Matrix& Matrix::operator+=(Matrix const& B)
{
  assert(data_.size() == B.data_.size());
  assert(rows_ == B.rows_);
  assert(cols_ == B.cols_);

  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] += B.data_[i];

  return *this;
}


Matrix& Matrix::operator*=(Matrix::value_type factor)
{
  for (size_type i = 0; i < data_.size(); ++i)
    data_[i] *= factor;

  return *this;
}


bool Matrix::operator==(Matrix const& rhs) const
{
  if (num_rows() != rhs.num_rows())
    return false;
  if (num_cols() != rhs.num_cols())
    return false;

  for (size_type i = 0; i < data_.size(); ++i)
    if (!almost_equal(data_[i], rhs.data_[i]))
      return false;

  return true;
}
