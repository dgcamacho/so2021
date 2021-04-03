# Exercise sheet 5

## Exercise 1
What is the error (if any) in the following function definitions?
```c++
(a) double func(double) { return (2*double); }
(b) double func(double x) { return 2 * x };
(c) double func( double x) { x *= 2; }
(d) double& func(double x) { return x; }
(e) double func(double& x) { return &x; }
(f) double& func(double& x) { return x; }
```

## Exercise 2
Implement a simple matrix class
```c++
struct Matrix
{
  std::vector<std::vector<double>> rows;
};
```
as a vector of row vectors. To use that class, we need to provide
- initialization function `void init(Matrix& matrix, std::size_t r, std::size_t c, double value)` that resizes the rows vector and all its rows
  to the desired size `(r x c)` and initializes all entries with `value`.
- (read) access function `double access(Matrix const& matrix, std::size_t i, std::size_t j)`, to access the (i,j)-th element
- matrix addition `Matrix add(Matrix const& A, Matrix const& B)` that returns `A + B` of two equal size matrices.
- What else could be useful?

Implement all these functions as free functions.

## Exercise 3
Reimplement the matrix class from exercise 2 using a class with member functions
- A constructor, i.e. a function without return type and with the name equal to the class name, instead of `init()`
- A member function `double at(std::size_t i, std::size_t j) const` for the element access.
- Another member function `double operator()(std::size_t i, std::size_t j) const` also for the element access.
- A member function `Matrix& operator+=(Matrix const& B)` for the accumulated addition `A += B` where `A` is the instance of the class itself.
- A free function `Matrix operator+(Matrix const& A, Matrix const& B)` for the  addition of two matrices. Note: reuse `operator+=`!

### Note
- Inside of these methods, the data `rows` can be accessed directly.

### Further ideas
- Replace the data `rows` with just a `std::vector<double>` storing all the elements row-wise in a contiguous container.
  What do you need to store additionally in the matrix?
- A sparse matrix could be implemented with a `std::map<std::pair<std::size_t,std::size_t>, double>` instead of the vector, mapping the
  index pair (r,c) to the actual value. Note: Implement an intelligent addition that does not iterate over the whole matrix. You could assume that
  both matrices have the same non-zero positions.
- Benchmark all three data representations for the matrix addition of two 1000 x 1000 matrices with
    * all entries randomly set to a value in the range `[1,100]`
    * Just 1000 entries unequal to 0

### Resources
- [cppreference:constructors](https://en.cppreference.com/w/cpp/language/initializer_list)
- [cppreference:operators](https://en.cppreference.com/w/cpp/language/operators)

## Exercise 4
Which conversions are used in the following program in each expression?
```c++
struct X {
  int i;
  X(int); // constructor
  X operator+(int); // X + int
};

struct Y {
  int i;
  Y(X); // constructor
  Y operator+(X); // Y + X
  operator int(); // cast-to-int operator
};

inline X operator*(X,Y); // X * Y
inline int f(X); // f(X) -> int

int main() {
  X x = 1;
  Y y = x;
  int i = 2;

  i + 10;     y + 10;      y + 10 * y;
  x + y + i;  x * x + i;   f(7);
  f(y);       y + y;       106 + y;
}
```
Change the code to correct all errors and print the value of each expression.
