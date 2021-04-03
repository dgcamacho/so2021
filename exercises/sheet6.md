# Exercise sheet 6

## Exercise 1
In the following there are various overloads of `foo(.)` and `bar(.,.)` provided. Which of the function is called in the
main program, correspondingly. Are there ambiguities? First think about it, then implement and check yourself.
```c++
void foo(int a) {...};            // (a)
void foo(int& a) {...};           // (b)
void foo(int* a) {...};           // (c)
void foo(double a) {...};         // (d)
void bar(int a, int b) {...};     // (e)
void bar(float a, float b) {...}; // (f)

int main() {
  int a = 1;
  float b = 1.0f;
  double c = 1.0;

  foo(a);       // (1)
  foo(&a);      // (2)
  foo(1.0);     // (3)
  foo(b);       // (4)
  foo(&b);      // (5)
  foo(c);       // (6)

  bar(a, a);    // (7)
  bar(1.0, a);  // (8)
  bar(&a, a);   // (9)
  bar(b, b);    // (10)
  bar(c, c);    // (11)
  bar(b, c);    // (12)
  bar(a, b);    // (13)
}
```


## Exercise 2
What is the error in the following class definitions and access methods?
```c++
// (a)
class Encode {
  private:
    long secretKey;
  public:
    long Encode(long key);
};

// (b)
class Gift {
    string gift;
  public:
    ~Gift();
    ~Gift(std::string&);
}

// (c)
class Numeric {
  private:
    long x;
  public:
    void set(long n) const { x = n; }
    long get() { return x; } const
};

// (d)
class Pair {
  private:
    double x; double y;
  public:
    void getPair(double& x, double& y) { x = x; y = y; }
};
```


## Exercise 3
For a better structuring of your code, it is recommended to separate declaration and definition. Apply this
splitting to the code from exercise 2 or 3 of exercise sheet 5 (the `Matrix` class). Therefore, move the function
declarations and class definition to a header file (file ending `.hh` or `.hpp`) and the definition / implementation
of the functions (and member functions) to a source file (e.g. `matrix.cc`).

### Plan for Mistakes
Every programmer makes mistakes. They are inevitable. You need to check and verify continuously that your code performs correctly.
This is a difficult and challenging task. There are a few things that you should always do when programming:
- add assertions to programs to check their operation
- use (automatic) testing, i.e. every time you make changes to your code, run test functions to verify that
    * a single unit of code returns the correct result (*unit tests*)
    * pieces of code work correctly when combined (*integration tests*)
    * the behavior of a program doesn't change when details are modified (*regression tests*)
- therefore, use an off-the-shelf unit testing library and finally
- turn bugs into test cases

A more detailed explanation of this workflow is described in
[Best Practice for Scientific Computing](https://doi.org/10.1371/journal.pbio.1001745)

### Incorporate tests and assertions
In order to follow this workflow for the `Matrix` example, we need to implement tests.
Therefore, create a main source file `main.cc` that contains a test functions for the `Matrix` class.

1. First, write a helper function `compare(Matrix const&, Matrix const&)` or `operator==(...)` that tests for floating-point "equality" for matrices.
   With "equality" I mean equality up to a given tolerance of the order `std::numeric_limits<double>::epsilon()`.

2. Write a test function `bool test_init()` that initializes a new `Matrix` and returns whether the initialized size is correct. Test for corner
   cases like size `0x0` or size `0xN`.

3. Now, test the addition of two matrices with known sum, e.g. any matrix + zero matrix, sum of two diagonal/identity matrices, ...
   Therefore, write a function `bool test_add()` that performs several of these tests and returns whether all test were successful.
   Which corner cases or algebraic identities should be tested here, e.g. associativity, commutativity, additive identity, additive inverse.
   Verify experimentally, that the matrix + addition operator builds an *abelian group*.

  (Additional question: What do we need to implement (and to verify) in order to build a *matrix ring* and what are the restrictions?)

4. Write a function `bool test_access()` that tests the access function, i.e. initialize the matrix with a given value and test that on access
   you get this value.

5. Add assertions to the access operator and the addition operator to test for valid input!

In which order should the written tests `test_init(), test_add()`, and `test_access()` be called? Is one test success required to perform the
next test? In your `main()` call each test and throw an error if the test failed.

### Additional questions and further reading (optional)
- In order to run tests automatically, add a file `.gitlab-ci.yml` to your repository. This file configures a script of compile and run commands
  the are executed in a build environment and if an error occurs, a message is send to the GitLab system that shows in a pipeline that something
  went wrong. This is called *continuous integration* (CI), we continuously test (on each push) that everything works fine.

  Read, e.g. https://docs.gitlab.com/ee/ci/quick_start/ for an introduction to the GitLab CI system.

- The C macro `assert(...)` that we used so far is a not the ideal tool to handle errors in code, since it always
  aborts the program with a hard error. No chance to handle the erroneous case or to provide an alternative output
  in case of that error.

  An alternative to assertions are *exceptions* that are values that can be
    * `throw`n by any function,
    * tested for in a `try`-block, and
    * `catch`ed and handled in case the calling site receives such an exception.

  Look up in the web how to throw and handle exceptions and replace assertions by proper throw statements. Now,
  you can even test that a function produces the right error in case of wrong input. So, test the error handling!


## Exercise 4 (GotW-1: Variable initialization -- or is it?)
See [GotW #1](https://herbsutter.com/2013/05/09/gotw-1-solution/).

What is the difference, if any, among the following?
```c++
widget w;                   // (a)

widget w();                 // (b)
widget w{};                 // (c)

widget w(x);                // (d)
widget w{x};                // (e)

widget w = x;               // (f)
widget w = {x};             // (g)

auto w = x;                 // (h)
auto w = widget{x};         // (i)
```
(`widged` is a class with a default constructor and a single argument constructor that accepts an object `x`.)
