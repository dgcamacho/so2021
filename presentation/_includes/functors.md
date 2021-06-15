---
class: center, middle
# Function Objects
---

# Function Objects

Some algorithms have an additional customization point to specify an operation to perform on the
elements. E.g. in `std::accumulate` you can specify how to fold the elements, i.e., to use `operator+` or
another binary function.

--

Regular functions are not objects in C++
- Cannot be passed as parameters
- Cannot have state

C++ additionally defines the *FunctionObject* named requirement. For a type `T` to
be a FunctionObject or **functor**
- `T` has to be an object
- `operator() (<args>...)` has to be defined for `T` for a suitable argument list `<args>...` which can be empty

---

# Function Objects
There are a number of valid function objects defined in C ++
- Pointers to functions
- Stateful function objects in form of classes
- Lambda expressions

Functions and function references are not function objects
- Can still be used in the same way due to implicit *function-to-pointer* conversion

---

# Pointers to functions

While functions are not objects they do have an address
- Location in memory where the actual assembly code resides
- Allows declaration of function pointers

Function pointers to non-member functions
- Declaration: `<return_type> (*function_name) (<args>...)`
- Allows passing functions as parameters
- E.g. passing a custom compare function to `std::sort` (see later)
- E.g. passing a callback to a method
- Can be invoked in the same way as a function

---

# Pointers to functions
## Example
```c++
template <class InputIt, class T>
T accumulate (InputIt first, InputIt last, T init, T (*op)(T, T))
{
  for (; first != last; ++first)
    init = op(init, *first); // Automatically dereferenced, or (*or)(init, *first)
  return init;
}

//--------------------------------------------------------
int add (int const arg1, int const arg2) { return arg1 + arg2; }
int mult (int const arg1, int const arg2) { return arg1 * arg2; }

//--------------------------------------------------------
int main () {
  std::vector<int> v{1,2,3,4,5,6,7,8,9};
  auto i = accumulate(v.begin(), v.end(), 0, add);
  auto i = accumulate(v.begin(), v.end(), 0, &mult); // "&" can be omitted
}
```

---

# Function objects of class type
The requirement for a function object is the availability of the call-operator `operator()`.

```c++
struct <functor>
{
  <return_type> operator() (<args>...) [const] { ... }
};
```

Since we implement a class, the full flexibility of classes can be used, i.e.,
- Member variables as parameters to the function
- Custom constructors
- Other member functions with implementation details
- Derive class from other base class
- ...

---

# Function objects of class type
## Example - Parametrized functions

```c++
struct Add4 {
  int operator() (int arg) const { return arg + 4; }
};

struct AddX {
  int x_;                                               // member variable
  AddX (int x) : x_(x) {}                               // constructor
  int operator() (int arg) const { return impl(arg); }  // redirect to private function

private:
  int impl (int arg) const { return arg + a_; }         // implementation detail
};
...
Add4 add4{};
assert( add4(17) == 21 );

AddX add7{7};
assert( add7(17) == 24 );
```

---

# Function objects of class type
## Passing functors to functions

Since each functor is implemented as another class with no common base, we have to use template
parameters to pass functor classes:

```c++
template <class InputIt, class T, class BinaryOp>
T accumulate (InputIt first, InputIt last, T init, BinaryOp op)
{
  for (; first != last; ++first)
    init = op(init, *first);
  return init;
}
```

- Often functors are passed-by-value
- Sometimes passed by `const&` if we assume that the passed functor object might be large
- Later: universal references

---

# Function objects of class type
## Example - Accumulate

```c++
struct Adder {
  int operator() (int arg1, int arg2) const { return arg1 + arg2; }
};
...
accumulate(v.begin(), v.end(), Adder{}); // (1) instantiate functor
Adder adder{};
accumulate(v.begin(), v.end(), adder);   // (2)
accumulate(v.begin(), v.end(), mult);    // (3) we can still pass function pointer
```

--

## Example - ForEach

```c++
template <class Range, class F>
void forEach (Range& range, F func) {
  for (auto& x : range)
    func(x);
}
...
std::vector v{1,2,3,4,5,6,7,8,9};
forEach(v, Add4{});
```

---

# Function objects of class type
## Stateful functors
Function objects cannot only be parametrized, they can also hold an internal state and change
on evaluation. The call-operator `operator()` doesn't need to be `const`:

```c++
struct Counter {
  int num = 0;
  void operator() (int const /*arg*/) { num++; } // change internal state
};

Counter count;
count(7);   // num == 1
count(42);  // num == 2
count(3);   // num == 3
```

> .h3[Attention:] Passing stateful functors to functions requires the functor argument to reference
> Otherwise, either the result is lost at the end of the call, or the non-`const` function cannot be called.

---

# Function objects of class type
## Generic functors

Functors are classes, can thus be parametrized by types.
```c++
template <class T>
struct Plus {
  T operator() (T const arg1, T const arg2) const { return arg1 + arg2; }
};
...
accumulate(v.begin(), v.end(), 0, Plus<int>{});
```

--

But also the member functions, especially the `operator()` can be parametrized:
```c++
struct Plus {
  template <class T>
  T operator() (T const arg1, T const arg2) const { return arg1 + arg2; }
};
...
accumulate(v.begin(), v.end(), 0, Plus{});
```

---

# Lambda Expressions
Function pointers can be unwieldy
- Function pointers cannot easily capture environment
- Have to pass all variables that affect function by parameter
- Cannot have "local" functions within other functions

--

Functor classes are out-of-place
- Must be defined in global, class or namespace scope
- Implementing member variables often requires constructors

--

C++ defines *lambda expressions* as a more flexible alternative
- Lambda expressions construct a *closure*
- Closures store a function together with an environment
- Lambda expressions can capture variables from the scope where they are
  defined

---

# Lambda Expressions

Lambda expressions can be declared as follows:
```c++
[captures...] (<aprgs>...) -> <return_type> { return ...; };
// or shorter in case of automatic return type deduction
[captures...] (<aprgs>...) { return ...; };
// or shorter in case of empty parameter list
[captures...] { return ...; };
```
Without the "capture" clause, it looks like a regular function definition
- The `captures...` is a list of zero or more variables or references that can be used inside the function
- `<args>...` is a list of function parameters including its types and qualifiers
- `<return_type>` is the (optional) (trailing) return type of the function. Can be omitted if return type can be deduced automatically from return statement.
- The function body may contain any sequence of valid c++ statements and (optionally) return statement(s).

---

# Lambda Expressions
## Example - Accumulate using Lambda Expression
As in the previous accumulate example, we pass a functor to the function. A lambda expression is a special
type of functor, thus can be directly passed without changing the function signature
```c++
template <class InputIt, class T, class BinaryOp>
T accumulate (InputIt first, InputIt last, T init, BinaryOp op);
...
std::vector v{1,2,3,4,5,6,7,8,9};
accumulate(v.begin(), v.end(), 0, [](int arg1, int arg2) -> int { return arg1 + arg2; });
accumulate(v.begin(), v.end(), 0, [](int arg1, int arg2) { return arg1 + arg2; });

// capturing a variable
int shift = 7;
accumulate(v.begin(), v.end(), 0,
  [shift](int const arg1, int const arg2) { return arg1 + arg2 + shift; });
```

---

# Lambda Expressions
## Example - ForEach
Passing a functor to the `forEach` function, allows very natural looking loops:
```c++
forEach(v, [](int arg) -> void {
  std::cout << arg << std::endl;
});

// shorter without trailing return type
forEach(v, [](int arg) {
  std::cout << arg << std::endl;
});
```

--

## Storing Lambdas

- Lambda expressions have a **unique** unnamed class type
- Store lambda expressions, using `auto`
- Do not return multiple lambdas from a function!


---

# Lambda Expressions
## Captures

The capture list is very similar to a constructor argument list to a functor that stores parameters.
All variables in that list introduce a "local" member variable inside the lambda expression, that can
be used inside the lambda expression function body. Any other variable from the environment cannot
be accessed.

Using capture lists, a connection to the surrounding scope can be established:

```c++
[]    // no captures
[a]   // stores a copy of the local variable `a`
[&a]  // stores a reference to the local variable `a`
[=]   // copies all (used) variables from the surrounding scope
[&]   // references all (used) variables from the surrounding scope

[a,b,c]   // multiple capture separated by comma
[x=a,y=b] // give captures new names
```

> .h3[Remark:] Empty capture list results in stateless lambda expression.

---

# Lambda Expressions
## Generic Lambdas

- Lambda expressions can be implemented using placeholder argument types `auto` including qualifiers
- Similar to generic member function in functor
- Since C++20 a list of template parameters is allowed:

```c++
[captures...] <template_params...> (<args>...) -> <return_type> { ... };
```

- All generic types can be constrained.

### Example

```c++
forEach(v, [](auto arg) { std::cout << arg << std::endl; });
forEach(v, [](std::floating_point auto arg) { std::cout << arg << std::endl; });
forEach(v, []<typename T>(T const arg) { std::cout << sizeof(T) << std::endl; });
```


---

# Function objects and Constraints
## Passing functors to function

Remember the `accumulate()` function. It gets iterators, and initial value and a binary operation.
The binary functor gets as input two argument of the same type as the initial value and return the same type

1) Function pointers
```c++
template <class InputIt, class T>
T accumulate (InputIt first, InputIt last, T init, T (*op)(T, T));
```

--

2) Template parameter
```c++
template <class InputIt, class T, class BinaryOp>
T accumulate (InputIt first, InputIt last, T init, BinaryOp op); // information lost
```

--

3) Constraints
```c++
template <class InputIt, class T, std::invocable<T,T> BinaryOp>
T accumulate (InputIt first, InputIt last, T init, BinaryOp op); // not as expressive as 1)
```

---

# Function objects and Constraints
## Passing functors to function

Remember the `accumulate()` function. It gets iterators, and initial value and a binary operation.
The binary functor gets as input two argument of the same type as the initial value and return the same type

4) Use `std::function` wrapper
```c++
template <class InputIt, class T>
T accumulate (InputIt first, InputIt last, T init, std::function<T(T,T)> op); // overhead!
```

---

# Function objects
## Algorithms with functors
### Example: `std::generate`

The algorithm `std::generate` fills a range by values generated by a nullary functor, called "generator":
```c++
// #include <numeric>
template <class ForwardIt, class Generator>
void generate (ForwardIt first, ForwardIt lst, Generator g)
{
  while (first != last)
    *first++ = g();
}
```
(Compare with `std::fill` and `std::iota`)

---

# Function objects
## Algorithms with functors
### Example: `std::transform`
The algorithm `std::transform` applies a unary functor to the elements of a range and assigned the result to an output functor
```c++
// #include <algorithm>
template <class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform (InputIt first, InputIt last, OutputIt d_first, UnaryOperation unary_op)
{
  while (first != last)
    *d_first++ = unary_op(*first++);
  return d_first;
}
```

---

# Function objects
## Algorithms with functors
### Example: `std::inner_product`
The numerical algorithm `std::inner_product` folds two ranges using two binary operations for elementswise
and reduction operation
```c++
// #include <numeric>
template <class InputIt1, class InputIt2, class T, class BinaryOp1, class BinaryOp2>
T inner_product (InputIt1 first1, InputIt1 last1, Input2 first2, T value,
                 BinaryOp1 op1, BinaryOp2 op2)
{
  while (first1 != last1) {
    value = op1(value, op2(*first1, *first2));
    ++first1;
    ++first2;
  }
  return value;
}
```


---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write 3 functions `add`, `sub`, and `mul` that take 2 parameters each and return their sum, difference, and product respectively.*

```c++
auto add = [](auto x, auto y) {
  return x + y;
};
auto sub = [](auto x, auto y) {
  return x - y;
};
int mul (int x, int y) {
  return x * y;
};
```

---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write a function, `identityf`, that takes an argument and returns a function that returns that argument.*

```c++
auto identityf = [](auto x) {
  return [=]() { return x; };
};
identityf(5)(); // 5
```

---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write a function that produces a function that returns values in a range.*

```c++
auto fromto = [](auto start, auto finish) {
  return [=]() mutable {    // allow the captured variables to be modified
    if (start < finish)
      return start++;
    else
      throw std::runtime_error("Complete");
  };
};
auto range = fromto(0, 10);
range(); // 0
range(); // 1
```

(see also [coroutines](https://en.cppreference.com/w/cpp/language/coroutines))
---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write a function that adds from two invocations.*

```c++
auto addf = [](auto x) {
  return [=](auto y) {
    return x+y;
  };
};
addf(5)(4); // 9
```

---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write a function swap that swaps the arguments of a binary function.*

```c++
auto swap =[](auto binary) {
  return [=](auto x, auto y) {
    return binary(y, x);
  };
};
swap(sub)(3, 2); // -1
```

---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write a function that takes a binary function and makes it callable with two invocations.*

```c++
auto applyf = [](auto binary) {
  return [=](auto x) {
    return [=](auto y) {
      return binary(x, y);
    };
  };
};
applyf(mul)(3)(4); // 12
```

---

# Function objects
## Fun with Lambdas
Extracted from http://cpptruths.blogspot.com

*Write a function that takes a function and an argument and returns a function that takes the second argument and applies the function.*

```c++
auto curry = [](auto binary, auto x) {
  return [=](auto y) {
    return binary(x, y);
  };
};
curry(mul, 3)(4); // 12
```

Currying (schönfinkeling)
- Currying is the technique of transforming a function that takes multiple arguments in such a way
  that it can be called as a chain of functions, each with a single argument.
- In "lambda calculus" functions take a single argument only.