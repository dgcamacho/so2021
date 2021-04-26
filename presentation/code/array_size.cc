#include <tuple>

#define SIZE(a)  (sizeof(a) / sizeof(a[0]))
#define ROWS(a)  (sizeof(a) / sizeof(a[0]))
#define COLS(a)  ((sizeof(a) / sizeof(a[0][0])) / (sizeof(a) / sizeof(a[0])))

/// Return the number of entries in an array
template <class T, int N>
int array_size(T (&)[N]) { return N; }

/// Return the number of rows and columns in a matrix
template <class T, int N1, int N2>
std::pair<int,int> mult_array_size(T (&)[N1][N2]) { return {N1, N2}; }

void f (int (&vec)[5])
{
  static_assert(SIZE(vec) == 5);
}

int main()
{

  int vec[5]{1,2,3};
  static_assert(SIZE(vec) == 5);

  int mat[][2]{1,2,3,4,5,6};
  static_assert(ROWS(mat) == 3);
  static_assert(COLS(mat) == 2);

  f(vec);
}
