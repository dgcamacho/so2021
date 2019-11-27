#include <vector>

struct Matrix
{
  // Initialize the Matrix
  Matrix(std::size_t r, std::size_t c, double value);

  // Return the (i,j)th entry of the matrix
  double access(std::size_t i, std::size_t j) const;

  double operator()(std::size_t i, std::size_t j) const
  {
    return access(i,j);
  }

  Matrix& operator+=(Matrix const& B);

  std::vector<std::vector<double>> rows;
};


Matrix::Matrix(std::size_t r, std::size_t c, double value)
{
  matrix.clear();           // empty all rows
  matrix.rows.resize(r);    // set the number of rows
  for (auto& row : matrix.rows)
    row.resize(c, value);   // set the number of columns and the default value
}


double Matrix::access(Matrix const& matrix, std::size_t i, std::size_t j)
{
  return matrix.rows[i][j];
}

// Add the two matrices A and B and return the sum
Matrix operator+(Matrix const& A, Matrix const& B)
{
  assert(A.rows.size() == B.rows.size());
  Matrix C{A}; // create a copy of the matrix

  for (std::size_t i = 0; i < A.rows.size(); ++i) {
    assert(A.rows[i].size() == B.rows[i].size());
    for (std::size_t j = 0; j < B.rows.size(); ++j) {
      C.rows[i][j] = A.rows[i][j] + B.rows[i][j];
    }
  }

  return C;
}