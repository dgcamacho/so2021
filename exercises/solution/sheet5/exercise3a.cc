#include <cassert>
#include <vector>

#include "exercise3a.hh"

// Add the two matrices A and B and return the sum
Matrix1 operator+(Matrix1 lhs, Matrix1 const& rhs)
{
  return lhs += rhs;
}


// NOTE:
// - default values for function parameters should not be repeated in the function definition.
// - in the constructor, all class members are (default) initialized, if not specified otherwise. Thus
//   not clear of the rows is necessary
Matrix1::Matrix1(std::size_t r, std::size_t c, double value)
{
  rows.resize(r);         // set the number of rows
  for (auto& row : rows)
    row.resize(c, value); // set the number of columns and the default value
}


// NOTE:
// - assignment operators should always return a reference, since one wants to
//   chain those operators, e.g. A += B += C += D ...
Matrix1& Matrix1::operator+=(Matrix1 const& B)
{
  assert(rows.size() == B.rows.size());

  for (std::size_t i = 0; i < rows.size(); ++i) {
    assert(rows[i].size() == B.rows[i].size());
    for (std::size_t j = 0; j < rows[i].size(); ++j) {
      rows[i][j] += B.rows[i][j];
    }
  }

  return *this; // return a reference to the class instance
}
