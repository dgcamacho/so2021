# Exercise sheet 9

## Exercise 1 (Vector class)
In the following vector class and main function there are more than 25 programming
and style errors included. Try to find as many as possible.
```c++
class vector
{
  typedef value_type double;

  vector(int s)
    : s(s), data(new double[s]) { }

  vector(vector const& that)
    : s(that.s), data(new double[s])
  {
    for (int i= 0; i <= s; i++)
      that.data[i] = data[i];
    return *this;
  }

  ~vector(double[] data) { delete data; }

  vector& operator=(vector const& that) const {
    assert(s != that.s)
    for (unsigned i= s-1; i >= 0; i--)
      data[i]= that.data[i];
    return this;
  }

  double const& operator[](unsigned i)
  {
    return data(i);
  }

  double& operator[](unsigned i)
  {
    return data(i);
  }

  unsigned size(const vector& v) { return v->s; }

private:
  double const data[];
  unsigned const s;
}

void main()
{
  vector v1(6);
  vector v2(v1);
  vector v3(10);
  v1 = v2;
  v3 = v2;
  v1(2) = 1;
  const vector v4(v2);
  v4[2] = 1.0;
  v4.size(v3);
}
```

## Exercise 2 (Vector class 2)
Write your own numerical vector class `Vector`, maybe inspired by the corrected version of
exercise 1, but instead of manual dynamic memory management use a `std::vector<double>`
for the storage of the vector coefficients.

The vector class should support at least the following operations
- construction from a size and initial value (default size is 0)
- construction from an `std::initializer_list` (see below)
- `operator+`, `operator-` for two vectors (implemented in terms of `operator+=` and `operator-=`)
- `operator*` for vector * scalar and scalar * vector
- an access `operator[]` (mutable and const)
- a method that returns the size of the vector

Write a small program that creates 5 vectors of size `n=10^7`: `vec1, vec2, ..., vec5`. Then,
perform small benchmarks of the following expressions:
1. `vec1 + vec2`
2. `vec1 += vec2`
3. `(vec1 + vec2) * 2`
4. `vec1 + vec2 + vec3 + vec4 + vec5`

In the cases 1., 3., and 4. assign the result to a new vector, i.e. something along the line
`Vector result = vec1 + vec2`.

For the cases 3. and 4. create new (free) functions, that perform these operations
directly, i.e. `Vector add_scale(Vector const& vec1, Vector const& vec2, double scalar)` and
`Vector add5(Vector const& vec1, Vector const& vec2...., Vector const& vec5)`.
Compare its performance to the previous ones using arithmetic operators.

### Hints
- The `std::initializer_list<double>` is a bit like a vector of values, but has less functionality
  and is used to allow direct construction from a list of values, just like the `std::vector` or
  `std::array` classes. Usage:

```c++
Vector(std::initializer_list<double> list)
  : data_(list.begin(), list.end())
{}
```
where `data_` is your storage vector. Then you can simply construct your vector with
values from curly braces: `Vector vec{1.0, 2.0, 3.0, 4.0}`. (Note: nested initializer lists
can be used to construct a matrix from values in curly braces)

- The benchmarks can be performed using the `Time` class from the lecture material, or
  using the google (micro) benchmarking suite.

- Perform the benchmarks with optimization flags enabled for your compiler.


## Exercise 3 (GotW-30: Koenig Lookup)
See [GotW #30](http://www.gotw.ca/gotw/030.htm).

Recapitulation Name Lookup: In the following code, which functions are called? Why? Analyze the implications.
```c++
namespace A {
  struct X;
  struct Y;
  void f(int); // (a)
  void g(X);   // (b)
}

namespace B {
  void f(int i) {  // (c)
    f(i);   // which f()?
  }
  void g(A::X x) { // (d)
    g(x);   // which g()?
  }
  void h(A::Y y) { // (e)
    h(y);   // which h()?
  }
}
```

### Resources
- Koenig Lookup or [Argument dependent name lookup](https://de.wikipedia.org/wiki/Argument_dependent_name_lookup)
