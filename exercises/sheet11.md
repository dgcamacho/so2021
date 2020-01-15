# Exercise sheet 11 - 2020/01/15

## Exercise 1 (Function templates)
1. Write a function template `minmax(a,b)` to calculate minimum and maximum of two values `a` and
`b` of the same type given as arguments to the function. The return type should be a pair of values, i.e.
`std::pair<T,T>`, where `T` is the type of the arguments. The first entry in the pair corresponds to the minimal
value, the second entry to the maximal value.

What are the requirements on the types that must be fulfilled in order to call the function properly?

**Guru Question:** Could this be implemented using C-Macros? If yes, how? Why are function templates the
better choice?

2. Consider the generic function
```c++
template <typename T1, typename T2>
T1 min(T1 a, T2 b)
{
  return a < b ? a : b;
}
```
Which design decision are inappropriate? Why? Construct a function call that results in a wrong result!

3. Templates can be used to specify the functionality in a function, e.g.
```c++
#include <functional> // -> std::less
template <typename T, typename Compare = std::less<T> >
T min(T a, T b, Compare less = Compare{})
{
  return less(a, b) ? a : b;
}
```
How to call that function for values of type `int`, `double`, and for a user-defined type, like `Rational`?
What do you need to implement in order to make the call work?


## Exercise 2
We have a header file `ex11.h` that declares a class and three methods:
```c++
template<typename T> struct A { void foo(); };
template<typename T> void bar1();
template<typename T> void bar2();
void bar3();
```
In another header file `ex11.hh` we provide the definition of the member-function of the class-template:
```c++
template<typename T>
void A<T>::foo() { std::cout << "foo-T\n"; }
```
In a third file `ex11_impl.cc` we provide the implementation of two methods:
```c++
template<typename T> void bar1() { std::cout << "bar1\n"; }
void bar3() { bar1<double>(); }
```
and finally in the main `ex11.cc` file we have
```c++
template<> void A<double>::foo() { std::cout << "foo-double\n"; }
template<typename T> void bar2() { std::cout << "bar2\n"; }
int main() {...}
```

1. Try to find the links between these file. Which files needs to include which else. Finally we want to compile
both `.cc` files via
```
> g++-7 ex11_impl.cc ex11.cc -o ex11
```

2. Consider the following implementation of the main() function:
```c++
int main()
{
  A<float> a;
  a.foo();
  bar1<float>();
  bar1<double>();
  bar2<double>();
  bar3();
}
```
Try to compile the code. What error do you get and why? Try to remove the corrupted line and compile
again! What is the output of the program and why? Use the tools `nm` or `objdump` in order to find the provided
and expected symbols in the files.


## Exercise 3 (Class Templates) :pencil2:
Choose one of the three classes from the last exercises (`Rational`, `Matrix`, or `Polynomial`) and transform it into a
class template, i.e.
```c++
template <class C, class V>
class Polynomial {
  using coeff_type = C;  // type used for the coefficients
  using value_type = V;  // type used for the evaluation argument
  ...
};

template <class T>
class Matrix {
  using value_type = T; // type used for the matrix entries
  ...
};

template <class T>
class Rational
{
  using value_type = T; // type used for numerator and denominator
  ...
};
```

1. Try it out with the template types filled with the explicitly specified types before and run the tests.

2. What are the requirements on the template parameters, i.e. what are the operations you need to perform with
   objects of that types?

3. Try to instantiate your class with one of the other classes, i.e. `Rational<Polynomial>` to form a rational function,
   `Matrix<Rational>` a matrix with rational coefficients, or `Polynomial<double,Matrix>` a matrix polynomial. What
   functionality is missing in the template types and can you easily correct/extend it? Run the test suite on those types!


**>> Submit solution until 2020/01/29 ... (10 Points)**


#### Note
- The full correction/extension in step 3 might be a complicated task. This is optional!
Just identity the missing functions, maybe implement it with a placeholder function or an error message so that at least the code
compiles.

- Please, only implement on of the class templates.

#### Resources
- [Polynomial greatest common devisor](https://en.wikipedia.org/wiki/Polynomial_greatest_common_divisor),
  [Polynomial division](https://en.wikipedia.org/wiki/Polynomial_long_division),
  [Rational function](https://en.wikipedia.org/wiki/Rational_function)
- [Matrix polynomial](https://en.wikipedia.org/wiki/Matrix_polynomial)
- [Class Templates](https://en.cppreference.com/w/cpp/language/class_template)


## Exercise 4 (Guru Exercise)
Write a class `SmartPointer<T>` representing a smart pointer:
- `SmartPointer` has a destructor, taking a pointer of type `T*` and store it in a member variable
- `SmartPointer` has a destructor, releasing the memory of the stored pointer .
- A dereferencing operator `*` and a member access operator `->` should be added.
- What is a reasonable default constructor?
- Does it make sense to define copy or move constructor/assignment operator?
- What other methods should be added to make it a pointer-like type?

Try out your smart pointer with the following example code:
```c++
SmartPointer<double> f() {
  return SmartPointer<double>{ new double };
}

int main() {
  auto p = f();
  *p = 1.0;
  auto q = p; // Does this make sense for your pointer type?
  *q = 2.0;
  // What is the effect on p?
}
```
Use `valgrind` to test for memory errors.
