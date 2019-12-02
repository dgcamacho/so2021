#include <cassert>
#include <vector>

struct Matrix
{
  std::vector<std::vector<double>> rows;
};

// Initialize the Matrix
void init(Matrix& matrix, std::size_t r, std::size_t c, double value = 0.0)
{
  matrix.rows.clear();      // empty all rows
  matrix.rows.resize(r);    // set the number of rows
  for (auto& row : matrix.rows)
    row.resize(c, value);   // set the number of columns and the default value
}

// Return the (i,j)th entry of the matrix
double access(Matrix const& matrix, std::size_t i, std::size_t j)
{
  return matrix.rows[i][j];
}

// Add the two matrices A and B and return the sum
Matrix add(Matrix const& A, Matrix const& B)
{
  assert(A.rows.size() == B.rows.size());
  Matrix C{A}; // create a copy of the matrix

  for (std::size_t i = 0; i < A.rows.size(); ++i) {
    assert(A.rows[i].size() == B.rows[i].size());
    for (std::size_t j = 0; j < A.rows[i].size(); ++j) {
      C.rows[i][j] += B.rows[i][j];
    }
  }

  return C;
}

/* alternative add implementation:

// Pass the first argument by value
Matrix add(Matrix A, Matrix const& B)
{
  assert(A.rows.size() == B.rows.size());

  for (std::size_t i = 0; i < A.rows.size(); ++i) {
    assert(A.rows[i].size() == B.rows[i].size());
    for (std::size_t j = 0; j < A.rows[i].size(); ++j) {
      A.rows[i][j] += B.rows[i][j];
    }
  }

  return A;
}

*/