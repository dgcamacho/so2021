# Exercise sheet 10 - 2020/01/08

## Exercise 1 (Standard Containers)
The C++ standard library provides implementations of several common data-structures: vector, list, deques, queues,...
We want to compare some of them for performance of insertion and sorting algorithms:

1. Create an empty Container of type `std::list, std::vector, std::deque, ...` with value type one of {`char, double, A`},
  where `A` is a class
```c++
struct A {
  short s; int i; char c;
  A(short s, int i, char c) : s(s), i(i), c(c) {}
};
```
  and fill the container with `1,000,000` elements (or more) of random values using the function `push_back`, or `push_front`
  and `emplace_back` or `emplace_front`, respectively.

2. Add a comparison operator for objects of type `A`, i.e.,
```c++
// lexicographical comparison
inline bool operator<(A const& lhs, A const& rhs)
{
  return std::tie(lhs.s, lhs.i, lhs.c) < std::tie(rhs.s, rhs.i, rhs.c);
}
```
  and sort the containers using a function like `std::sort` (from `<algorithm>`) or a member function `container.sort()`.

3. Measure the time needed for each of the above steps. Therefore use the class `Timer` provided in the lecture material folder.

### Hints
- Use the functions `std::rand()` or functions / classes from `<random>` (e.g. `uniform_int_distribution`) to produce the
  random numbers. See [cppreference:rand](https://en.cppreference.com/w/cpp/numeric/random/rand),
  [cppreference:random](https://en.cppreference.com/w/cpp/numeric/random).

- In case the data-structure provides such a function, use `reserve()` or `resize()` before inserting or filling with the values.
  Compare to the time without previous reservation of space.


## Exercise 2 (Inheritance and Composition)
Write a class `NumVector`, which represents a numerical vector. The size of the vector (passed as constructor argument)
has to be fixed. Read and write access to the individual entries of the vector should be granted by means of the
brackets operator. In addition, the class should have the method `double norm()` that calculates
the Euclidean norm of the vector. Other methods should not be visible. In particular, a `NumVector`
should not be a `std::vector<double>`!

Design two implementations of this class, both of which store the values in a `std::vector<double>`.
The first implementation has to be derived from `std::vector<double>` and the second one should
not use inheritance. Use two different header files for this (e.g. `NumVector[1/2].hh`), and only include
one of them at a time when testing with the programs below.

Test your implementation as follows:

1. The classes should work correctly with the following main program.
```c++
#include <iostream>
#include "NumVector[1/2].hh"

int main()
{
  NumVector v(3);
  v[0] = 1; v[1] = 3, v[2] = 4;
  NumVector const& w = v;
  std::cout << "norm is " << w.norm() << std::endl;
  std::cout << "vector is [" << w[0] << ", " << w[1] << ", " <<w [2] << "]" << std::endl;
}
```

2. The following program must not compile though!
```c++
#include <vector>
#include "NumVector[1/2].hh"

void vectorTest(std::vector<double>& v) {}

int main()
{
  NumVector v(3);
  v.resize(2);    // must be hidden, just like other methods of std::vector!
  vectorTest(v);  // this should also lead to a compiler error!
}
```

## Exercise 3 (Inheritance and Functions)
Find the errors in the following program. What is the output after the incorrect lines are removed,
and why?
```c++
#include <iostream>

class SuperClass
{
public:
  void foo() const
  {
    std::cout << "SuperClass::foo" << std::endl;
  }
};

class DerivedClass : public SuperClass
{
public:
  void foo()
  {
    std::cout << "DerivedClass::foo" << std::endl;
  }
};

class LeafClass : private DerivedClass
{
public:
  void bar()
  {
    foo();
  }
};

void test(SuperClass const& super)
{
  super.foo();
}

int main()
{
  SuperClass super;
  DerivedClass derived;
  LeafClass leaf;

  super.foo();

  derived.foo();
  test(derived);

  leaf.bar();
  test(leaf);
}
```


## Exercise 4 (External Libraries):pencil2:
We have implemented our own matrix and vector classes in the last exercises. For most of the
data-structures there is an efficient implementation already available. Especially for linear
algebra containers and algorithms there exist a large variety of libraries, all with a different focus
or intention, often with a similar syntax.

We want to explore some of the external libraries in this exercise. The task is as follows:
- Choose one of the libraries below
- Download and install (compile) the library (if necessary)
- Create a source file `main.cc` that performs the following steps:
  * Create a dense matrix `A` of size 100 x 100 and a vector `b` of size 100.
  * Fill the matrix with the 1d finite-difference 3-point laplace stencil, i.e. on the diagonal the value `+2` and on
    the first lower and upper off-diagonal the value `-1`.
  * Fill the vector with all entries `1`.
  * Solve the linear system `A*x = b` for the unknown vector `x`
- Provide a `Makefile` or a compile script that links or includes the external library

### Possible external libraries
- [MTL4](http://www.simunova.com/de/mtl4)
- [Eigen3](http://eigen.tuxfamily.org)
- [Blaze](https://bitbucket.org/blaze-lib/blaze)
- [Armadillo](http://arma.sourceforge.net)

**>> Submit solution until 2020/01/22 ... (10 Points)**
