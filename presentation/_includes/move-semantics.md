---
class: center, middle
# Value Categories and Move Semantics
---

# Value Categories

Each expression in C++ is characterized by two independent properties
- Its *type* (e.g. `unsigned int`, `float`)
- Its *value category*
- Operators may require operands of certain value categories
- Operators result in expressions of certain value categories

Broadly (and inaccurately) there are two value categories: **lvalues** and **rvalues**
- *lvalues* refer to the identity of an object
- *rvalues* refer to the value of an object
- Modifiable *lvalues* can appear on the left-hand side of an assignment
- lvalues and *rvalues* can appear on the right-hand side of an assignment

C++ actually has a much more sophisticated taxonomy of expressions (see later)

---

# Value Categories
## Examples
```c++
int i = 3;
int j = 4;

i;              // the name of a variable is an lvalue
123; bool; 'c'; // literals (except for string literals) are rvalues
"Hello, world!" // string literals are lvalues!

// a + b, a % b, a & b, a << b, and all other built-in arithmetic expressions are rvalues

int c = i * j; // OK, rvalue on the right-hand side of an assignment
i * j = 42;    // ERROR, rvalue not allowed on the left-hand side of an assignment

// more on lvalues:
i = 43;           // OK, i is an lvalue
int* p = &i;      // OK, i is an lvalue

int& foo ();      // a function call, whose return type is reference is an lvalue
foo() = 42;       // OK, foo() is an lvalue
int* p1 = &foo(); // OK, foo() is an lvalue
```

---

# RValue References

A reference declaration declares an alias to an already-existing object. We distinguish between
*lvalue-references* and *rvalue-references*:

```c++
<base_type>&  <lvalue_reference> = <lvalue>;
<base_type>&& <rvalue_reference> = <rvalue>;
```

*Lvalue-references* bind to *lvalues* and cannot (in general) bind to *rvalues*. Whereas,
*rvalue_references* cannot (directly) bind to *lvalues*.

> .h3[Note:] *rvalues* are just values and thus might have a lifetime until the end of a statement.
> They are often referred to as **temporaries**.

---

# RValue References
## Examples
```c++
int i = 10;
int&& rref1 = i;      // ERROR: Cannot bind rvalue reference to lvalue
int&& rref2 = 42;     // OK

// more on rvalues:
int foobar ();        // a function call, whose return type is non-reference is a rvalue

int l = 0;
l = 42;               // OK, 42 is an rvalue
l = foobar();         // OK, foobar() is an rvalue
int* ptr = &foobar(); // ERROR, cannot take the address of an rvalue
auto* fptr = &foobar; // OK, function pointer!
```

--

Extend the lifetimes of temporary objects
```c++
int i = 10;
int j = 32;
int&& k = i + j;      // k == 42
k += 42;              // k == 84
```

---

# LValue and RValue References
## Constant LValue References
Lvalue references to `const` also extend the lifetime of temporary objects
```c++
int i = 10;
int j = 32;
int&& rref = i + j;       // OK, mutable rvalue-reference
const int& cref = i + j;  // OK, but cref is immutable
```

--

## Forwarding References
*Forwarding references* (or universal references) are a special kind of references that preserve the
*value category* of the initializer. Those references can only be declared using templates or placeholder
types:

```c++
auto&& uref = i + j;  // uref is of type int&&
template <class T>
void fun (T&& arg);
fun(i + j);           // arg is of type int&&
```

---

# Overload by Value Category

Language allows overload resolution to distinguish between lvalues and rvalues
```c++
void foo (int& x);        // (1)
void foo (int const& x);  // (2)
void foo (int&& x);       // (3)

int& bar ();
int  baz ();

int main () {
  int i = 42;
  const int j = 84;
  foo(i);           // calls foo(int&)        (1)
  foo(j);           // calls foo(const int&)  (2)
  foo(123);         // calls foo(int&&)       (3)


  foo(bar());       // calls foo(int&)        (1)
  foo(baz());       // calls foo(int&&)       (3)
}
```

---

# Lifetimes and Temporaries
## Remember
- When objects go out of scope, their destructor is called
- Objects allocated dynamically with `new` have lifetime until `delete` is called
- Function returning *by-value* return a temporary that is destroyed after the function call
- Function parameters taken *by-value* are destroyed at the end of the function

RValue-references and `const`-references can extend the lifetime of these *temporaries*:
- Some values need to materialize in memory to hold a reference to it
- Other values are destroyed only after the reference goes out of scope

> .h3[Principle:] Since we know that temporaries are destroyed at the end of their lifetime, we can
> make use of that fact. Idea: instead of copying these values, we "steal" their resources

---

# Copy Constructor and Move Constructor
## Reminder: Copy semantics
Classes typically have a copy constructor and a copy-assignment operator:
```c++
struct MyClass {
  MyClass (MyClass const& other);             // copy constructor
  MyClass& operator= (MyClass const& other);  // copy-assignment operator
  ...
};
```
these are defined by taking `const&` arguments, thus the lifetime of the passed objects is extended
into these functions.

---

# Copy Constructor and Move Constructor

For a class type `T` and objects `a, b`, the copy constructor is invoked on
- Direct initialization: `T a{b};`
- Copy initialization: `T a = b;`
- Function argument passing: `f(a);` where `f` is `void f(T t);`
- Function return: `return a;` inside a function `T f();` if `T` has no move
  constructor (more details next)

Copy semantics often incur unnecessary overhead or are unwanted
- An object may be immediately destroyed after it is copied
- An object might not want to share a resource it is holding

---

# Copy Constructor and Move Constructor

Move semantics provide a solution to such issues
- Move constructors/assignment operators typically "steal" the resources of the
  argument
- Leave the argument in a valid but indeterminate state
- Greatly enhances performance in some cases

Custom move constructors/assignment operators are *often* necessary
- A class that manages some kind of resource almost always requires custom
  move constructors and assignment operators

## Syntax:
```c++
struct MyClass {
  MyClass (MyClass&& other);             // move constructor
  MyClass& operator= (MyClass&& other);  // move-assignment operator
  ...
};
```

---

# Copy Constructor and Move Constructor
## Explanation:
- Overload resolution decides if the copy or move constructor should be called
- Temporary values and calls to functions that return an object are rvalues
- Use `std::move` function from `<utility>` header to convert
  *lvalue* to *rvalue*
- We know that the argument does not need its resources any more, so we can
  simply steal them

For a class type `T` and objects `a, b`, the move constructor is invoked on
- Direct initialization: `T a{std::move(b)};`
- Copy initialization: `T a = std::move(b);`
- Function argument passing: `f(std::move(b));` with `void f(T t);`
- Function return: `return a;` inside `T f();`

---

# Implementing Custom Move Operations
## Guidelines for implementing custom move operations
- The programmer should either provide neither a move constructor nor a move
assignment operator, or both
- The move assignment operator should usually include a check to detect
self-assignment
- The move operations should typically not allocate new resources, but steal
the resources from the argument
- The move operations should leave the argument in a valid state
- Any previously held resources must be cleaned up properly

---

# Implementing Custom Move Operations
## Example - A Vector class

```c++
struct Vector
{
  std::size_t size_ = 0;
  real_t* data_ = nullptr;

  Vector (std::size_t size) : size_(size), data_(size > 0 ? new real_t[size] : nullptr) {}
  ~Vector () { delete[] data_; }

  Vector (Vector const& other)    // copy constructor
    : Vector(other.size_)
  {
    std::copy(other.data_, other.data_+other.size_, this->data_);
  }

  Vector (Vector&& other)         // move constructor
  {
    std::swap(this->size_, other.size_);    // other.size_ = 0
    std::swap(this->data_, other.data_);    // other.data_ = nullptr
  }
};
```

---

# Implementing Custom Move Operations
## Example - A Vector class
Implement the copy and move-assignment operators using the copy-and-swap ideom:
```c++
struct Vector
{
  ...
  Vector& operator= (Vector const& other) {  // copy-assignment operator
    Vector that(other);             // call the copy-constructor
    std::swap(size_, that.size_);   // swap the content of this and the temporary that
    std::swap(data_, that.data_);
    return *this;
  }

  Vector& operator= (Vector&& other) {      // move-assignment operator
    Vector that(std::move(other));  // call the move-constructor
    std::swap(size_, that.size_);   // swap the content of this and the temporary that
    std::swap(data_, that.data_);
    return *this;
  }
};
```

---

# Implementing Custom Move Operations
## Example - A Vector class
Implement the copy and move-assignment operators using the copy-and-swap ideom:
```c++
struct Vector
{
  ...
  Vector& operator= (Vector other) {// copy and move-assignment operator
                                    // Take the argument by-value (uses copy or move)
    std::swap(size_, that.size_);   // swap the content of this and the temporary that
    std::swap(data_, that.data_);
    return *this;
  }
};
```

--

Example of usage
```c++
Vector a{5};
Vector b{a};              // calls copy constructor
Vector c{std::move(a)};   // calls move constructor, `a` cannot be used any more
b = c;                    // calls copy-assignment operator
b = std::move(c);         // calls move-assignment operator, `c` cannot be used any more
```

---

.center[<img src="images/auto_constructors.png" width="70%">]

.footnote[Howard Hinnant: Everything You Ever Wanted To Know About Move Semantics (and then some) (ACCU 2014)]

---

# Copy Elision / Return-Value Optimization
Compilers must omit copy and move constructors under certain circumstances
- Objects are directly constructed in the storage into which they would
  be copied/moved
- Results in zero-copy pass-by-value semantics
- Most importantly in return statements and variable initialization from a
  temporary
- More optimizations allowed, but not required

--

```c++
#include <iostream>
struct A
{
  int a;
  A(int a) : a(a)                 { std::cout << "constructed" << std::endl; }
  A(A const& other) : a(other.a)  { std::cout << "copy-constructed" << std::endl; }
};

A foo() { return A{42}; }   // returns a temporary

int main() {
  A var = foo();            // prints only "constructed"
}                           // equivalent to A var{42};
```

---

# Value Categories
Move semantics and copy elision require a more sophisticated taxonomy of expressions

<img src="images/value_categories.png" style="float:right; width:250px; margin: 10px">

- *glvalues* identify objects
- *xvalues* identify an object whose resources can be reused
- *prvalues* compute the value of an operand or initialize an object

In particular, std::move just converts its argument to an *xvalue* expression
- `std::move` is exactly equivalent to a `static_cast` to an *rvalue reference*
- `std::move` is exclusively syntactic sugar (to guide overload resolution)

.footnote[Image extracted from slides from http://db.in.tum.de/teaching/ss20/c++praktikum]

---
class: center, middle
# Quiz
---

# Implementing the `operator+` for Vector
We have the `Vector` class as before. Additionally, it has an `operator+=`:
```c++
struct Vector {
  ...
  Vector& operator+= (Vector const& other) {
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] += other.data_[i];
    return *this;
  }
};
```
We want to implement the `operator+`.
```c++
Vector operator+ (Vector const& lhs, Vector const& rhs);
```

> .h3[Question:] How often is the copy constructor (or move constructor) invoked in the following examples?

---

# Implementing the `operator+` for Vector
## 1. Use `operator+=` in the return statement
```c++
Vector operator+ (Vector const& lhs, Vector const& rhs)
{
  return Vector{lhs} += rhs;
}
```

Consider the expression
```c++
Vector a{10}, b{10}, c{10};
Vector erg = a + b + c;
```

---

# Implementing the `operator+` for Vector
## 2. Use `operator+=` on a local variable
```c++
Vector operator+ (Vector const& lhs, Vector const& rhs)
{
  Vector tmp{lhs};
  tmp += rhs;
  return tmp;
}
```

Consider the expression
```c++
Vector a{10}, b{10}, c{10};
Vector erg = a + b + c;
```

---

# Implementing the `operator+` for Vector
## 3. Use `operator+=` on a function parameter
```c++
Vector operator+ (Vector lhs, Vector const& rhs)
{
  lhs += rhs;
  return lhs;
}
```

Consider the expression
```c++
Vector a{10}, b{10}, c{10};
Vector erg = a + b + c;
```