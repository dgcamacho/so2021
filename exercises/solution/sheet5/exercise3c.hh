#include <cassert>
#include <map>
#include <tuple>

struct Matrix3
{
  // Default initialization
  // NOTE:
  // - The keyword `= default` means: use the default implementation for that function.
  // - The default implementation of the default constructor is: default-construct all
  //   members of the class.
  // - If a member is written with `= value` thisvalue is used in the default initialization.
  Matrix3() = default;

  // Initialize the Matrix3
  Matrix3(std::size_t r, std::size_t c);

  // Return the (i,j)th entry of the matrix
  // NOTE:
  // - Functions with just 1 line could be implemented "inline" in the class
  // - If the entry does not exist in the map, an *exception* is thrown
  double access(std::size_t i, std::size_t j) const
  {
    return data_.at({i,j});
  }

  // Mutable access to the entry (i,j) of the matrix
  // NOTE: The only differences to the const access are
  // 1. return type is reference
  // 2. function is not const.
  // 3. If the entry does not exist in the map, a new entry with value 0 is created
  double& access(std::size_t i, std::size_t j)
  {
    return data_[{i,j}];
  }

  // Access by the bracket operator
  // NOTE:
  // - The additional indirection by the call to `access` does not count, if
  //   that function is inlined by the compiler.
  double operator()(std::size_t i, std::size_t j) const
  {
    return access(i,j);
  }

  // An additional useful function is the *mutable* access to the data
  double& operator()(std::size_t i, std::size_t j)
  {
    return access(i,j);
  }

  // Accumulated plus operator
  Matrix3& operator+=(Matrix3 const& B);


  // The number of rows in the matrix
  std::size_t rows_ = 0;
  // The number of columns in the matrix
  std::size_t cols_ = 0;

  // The data of the matrix: an index to value map
  std::map<std::pair<std::size_t,std::size_t>, double> data_;
};

// Add the two matrices A and B and return the sum
// NOTE:
// - Here, the first argument is taken by value, since we need to create a copy anyway
// - An alternative signature would be (Matrix3 const& lhs, Matrix3 const& rhs)
// - Always try to implement the binary operators in terms of the compound assignment operators!
Matrix3 operator+(Matrix3 lhs, Matrix3 const& rhs);
