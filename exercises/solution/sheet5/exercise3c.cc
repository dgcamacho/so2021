#include <cassert>
#include <vector>

#include "exercise3c.hh"

// Add the two matrices A and B and return the sum
Matrix3 operator+(Matrix3 lhs, Matrix3 const& rhs)
{
  return lhs += rhs;
}


// NOTE:
// - in the constructor, all class members are (default) initialized, if not specified otherwise. Thus
//   not clear of the rows is necessary
// - Here, the number of rows and number of columns are set in a constructor *initializer list*,
//   introduced with the `:` symbol after the constructor parameter list.
// - Compared to the other matrix formats, at default values does not make sense in a sparse matrix. It is always 0.
Matrix3::Matrix3(std::size_t r, std::size_t c)
  : rows_(r)
  , cols_(c)
{}


// NOTE:
// - assignment operators should always return a reference, since one wants to
//   chain those operators, e.g. A += B += C += D ...
Matrix3& Matrix3::operator+=(Matrix3 const& B)
{
  assert(data_.size() == B.data_.size());
  assert(rows_ == B.rows_);
  assert(cols_ == B.cols_);

  // traverse the matrices using *iterators*, an abstraction of pointers to the elements
  // in the container. It returns a pair (key, value) of all elements
  auto it_lhs = data_.begin();
  auto it_rhs = B.data_.begin();
  for (; it_lhs != data_.end(); ++it_lhs, ++it_rhs) {
    assert(it_lhs->first == it_rhs->first); // indices should be the same!
    it_lhs->second += it_rhs->second;       // values are added up
  }

  return *this; // return a reference to the class instance
}
