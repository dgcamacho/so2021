# Exercise sheet 8 - 2019/12/11

## Exercise 1 (Valgrind)
1. Create a small program that creates arrays on the heap (using dynamic allocation). Therefore, write a function `int allocate(int n)`
   that calls itself recursively with decreasing `n` and allocates for each `n > 0` an array of integers of size `n`. The return value of that function
   is `0` in this exercise. Do not call `delete` explicitly. In your `main()`, call this function for some moderate `n`, compile your code and run it.

2. In each recursive call of `allocate()`, return the entry `n-1` of the array plus the value of the recursively called `allocate()`.
In case of `n==0` just return `0`, i.e. in python pseudo-code:
```python
def allocate(n):
  if n == 0:
    return 0

  # - allocate array a with size n
  # - recursively call allocate
  m = allocate(n - 1)
  return a[n-1] + m
```
  In your `main()`, print the number received from the `allocate()` call. Compile and run again.

3. Instead of accessing the `n-1`th element, read from the `n`th element in the return statement of the `allocate()` function. Compile and run again!


All these three steps contain memory-related errors. Here they are obvious, but in other cases it might be hard to see it from just looking at the code.
Therefore, there are tool that help finding the errors. One such tools, we have already tried out: *GDB*. Another tool that we want to look at is
*Valgrind*.

The *Valgrind* tool suite provides a number of debugging and profiling tools that help you make your programs faster and more correct.
The most popular of these tools is called *Memcheck*. It can detect many memory-related errors that are common in C and C++ programs
and that can lead to crashes and unpredictable behavior.

### Usage of Valgrind
If you normally run your program like this:
```bash
> ./myprog arg1 arg2
```
Use the following command instead:
```
> valgrind [OPTIONS] ./myprog arg1 arg2
```
Memcheck is the default tool. As options you may use `--leak-check=full` to turns on the detailed memory leak detector,
or `--track-origins=yes` to see where uninitialized values come from, or another option.

### References
- [Valgrind](http://valgrind.org/docs/manual/quick-start.html)


## Exercise 2 (Smart Pointers)
Consider the following code:
```c++
#include <memory>
std::shared_ptr<int> create_int_ptr(int value)
{
  return std::shared_ptr<int>( new int{value} );
  // or: return make_shared<int>(value);
}

int main()
{
  std::shared_ptr<int> i;
  {
    std::shared_ptr<int> j = create_int_ptr(2);
    i = j;
  }
  // #1
  return 0;
}
```
- Is this a valid program, or are there *dangling* pointer?
- How many pointers point to the memory of the allocated integer when reaching line `#1`?
- Can you replace `shared_ptr` by `unique_ptr` in this code? Why (not)?


## Exercise 3 (Combination of Tests)
On exercise sheet 4, we had to implement a rational number type (with some arithmetic), on sheet 5+6 a
matrix type with some arithmetic and on sheet 7 a polynomial type, again with some arithmetic. All these
types have in common that we can add them up (`operator+`) and there is a null-element of the plus-operation
that is an identity element. Also, the associativity law should hold for all these types ad some more properties.
Mathematically speaking, all these type build a *group* w.r.t. to plus operation. Maybe even an *Abelian group*.
(Note: this is not absolutely correct, since, e.g., integers can overflow, floating point values do not cover
the whole real numbers, so the totality property is not fulfilled in general)

We want to combine all the code from the 3/4 exercises and build one common test suite that tests for all
the mathematical properties.

Therefore, we need to
- put all the class/function declarations into header files `xxx.hh` (removing any `main()` function or specific test function)
- put all the class/function definitions into separate source files `xxx.cc`.
- copy the file `material/sheet8/exercise3.hh` to your solution folder
- add a combining source file `main.cc` that
  * includes all the implementation header files `xxx.hh` for the rational number type, the matrix type and the polynomial type
  * includes the `exercise3.hh` header file
  * implements for all three types the functions `identity<T>` and `random<T>`, returning the identity element w.r.t. addition and
    a random element of that type, see below.
  * calls the `test<T>()` function with `T` your class types, e.g. `test<Random>()`, and also some builtin types, like `int` or `double`.
- Create a *Makefile* that describes how to compile your code. Therefore, list *targets* for each class type implementation, e.g. `Rational.o`
  depending on the corresponding source code and a target for the executable that depend on the `main.cc` source code and on the other targets.


### Hints
In order to implement the functions `identity<T>` and `random<T>`, you have to specify the type for which you want to implement
the function explicitly. Assume your type is named `Rational`. Then the identity function could be implemented as follows:
```c++
template <>
Rational identity<Rational>()
{
  return Rational{0};
}
```
The first `template <>` tells the compiler that you want to specialize this function for an explicit type, the `Rational identity<Rational>` then
names this explicit type.

For the `random<T>` function, use `std::srand(12345)` in your `main()` and `std::rand() % n` for random integers in the range `[0,n)` and
`std::rand() / double(RAND_MAX)` for doubles in the range `[0,1)`. Therefore, include `<cstdlib>`.

### Remarks
The test suite makes some assumptions on the functionality of the tested types. Maybe some operations are not yet implemented. Then you will
get a compiler error.Read the code and understand the requirements on the types. Correct or extend your implementation to conform to the test suite.
**Do not modify the test suite!**

### References
- [Makefile](https://www.gnu.org/software/make/manual/html_node/Makefiles.html),
  [Makefile cheatsheet](https://devhints.io/makefile),
  [Makefile conventions and guidelines](https://eigenstate.org/notes/makefiles)

**>> Submit solution until 2020/01/08 ... (20 Points)**


## Exercise 4 (GotW-89: Smart Pointers)
See [GotW #89](https://herbsutter.com/2013/05/29/gotw-89-solution-smart-pointers).

1. When should you use `shared_ptr` vs. `unique_ptr`? List as many considerations as you can.
2. (Guru) Why should you almost always use `make_shared` to create an object to be owned by `shared_ptr`s? Explain.
3. (Guru) Why should you almost always use `make_unique` to create an object to be initially owned by a `unique_ptr`? Explain.

## Exercise 5 (GotW-91: Smart Pointer Parameters)
Also interesting: Passing smart pointers to functions? See [GotW #91](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters)