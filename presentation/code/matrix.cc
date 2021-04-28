#include <vector>

double** make_matrix(int nrows, int ncols)
{
  double** mat = new double*[nrows];
  for (int i = 0; i < nrows; ++i)
    mat[i] = new double[ncols];
  return mat;
}

void delete_matrix(double** mat, int nrows)
{
  for (int i = 0; i < nrows; ++i)
    delete[] mat[i];
  delete[] mat;
}

int main()
{
  int const nrows = 4;
  int const ncols = 4;

  { // version 1
    double* row1 = new double[4]{1.0, 2.0, 3.0, 4.0};
    double* row2 = new double[4]{2.0, 3.0, 4.0, 5.0};
    double* row3 = new double[4]{3.0, 4.0, 5.0, 6.0};
    double* row4 = new double[4]{4.0, 5.0, 6.0, 7.0};

    double** mat  = new double*[4]{row1, row2, row3, row3};

    delete[] row1;
    delete[] row2;
    delete[] row3;
    delete[] row4;
    delete[] mat;
  }

  { // version 2
    double** mat = make_matrix(nrows, ncols);
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;

    delete_matrix(mat, nrows);
  }

  { // version 3
    auto mat = std::vector<std::vector<double>>(nrows, std::vector<double>(ncols, 0.0));
    mat[0][0] = 1.0;
    mat[0][1] = 2.0;
  }

  { // version 4
    std::vector<std::vector<double>> mat{
      {1.0, 2.0, 3.0, 4.0},
      {2.0, 3.0, 4.0, 5.0},
      {3.0, 4.0, 5.0, 6.0},
      {4.0, 5.0, 6.0, 7.0}
    };
  }
}