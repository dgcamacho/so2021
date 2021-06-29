---
class: center, middle
# Expression Templates
---

# Expression Templates
## Pairwise evaluation problem
- associated with classical operator-overloading expressions in C++.
- Operators are unary or binary operations on the input and have to return a new object.
- Evaluation of a complex expression happens pairwise.
- Multiple copy operations and loops involved.

---

# Expression Templates
## Pairwise evaluation problem

```c++
Vector a{N}, b{N}, c{N}, erg{N};
erg = a + b + c;
```
generate code like this:
```c++
double* tmp1 = new double[N];   // allocation of temporary
for (int i = 0; i < N; ++i)     // copy
  tmp1[i] = a[i];
for (int i = 0; i < N; ++i)     // operator+=
  tmp1[i] += b[i];
double* tmp2 = new double[N];   // allocation of temporary
for (int i = 0; i < N; ++i)     // copy
  tmp2[i] = tmp1[i];
for (int i = 0; i < N; ++i)     // operator+=
  tmp2 += c[i];
delete[] tmp1;                  // destroy temporary
for (int i = 0; i < N; ++i)     // copy
  erg[i] = tmp2[i];
delete[] tmp2;                  // destroy temporary
```

---

# Expression Templates
## Pairwise evaluation problem

```c++
Vector a{N}, b{N}, c{N}, erg{N};
erg = a + b + c;
```

Goal: "automatically" generate function that uses only 1 loop and 0 allocations/copies:
```c++
void sum3 (Vector const& a, Vector const& b, Vector const& c, Vector& erg)
{
  for (int i = 0; i < N; ++i)
    erg[i] = a[i] + b[i] + c[i];
}
...
sum3(a, b, c, erg); // problem: no mathematical notation
```

---

# Domain-Specific (Embedded) Languages
- Description and solution of a problem to be can be expressed in the idiom and at the level of
  abstraction of the problem domain.
- Use operators and symbols with a specific meaning in the specific application domain

### Examples:
- **Matlab:** direct expression of high-level algebraic and numerical constructs in a easy to use imperative language
  Under-the-hood highly optimized C code is executed for several vectorized expressions.
- **Finite-element libraries**, that try to express the PDE problem setup in a near-mathematical
  language, e. g., [Fenics project](https://fenicsproject.org/), [FreeFem](https://freefem.org/).

---

# Domain-Specific (Embedded) Languages
## Embedded Languages
- DSL expressed in terms of host language
- Often operators are overloaded to give it a new (domain specific) meaning

### Examples:
- **finite-element libraries:** [Feel++](http://www.feelpp.org/)
- **Linear-Algebra libraries:** MTL4, Eigen, Blaze, uBlas, NT^2, VexCL

### General principle
- hide the programming details from the user of a library, and from the expert in this specific domain
- an expression can be translated to an already implemented and highly specialized function

---

# Expression templates: encoding operations
- Use operator overloading to express an operation
- Do not perform the operation in the operator, but return an object that "encodes" that operation
- An assignment of the expression to a variable, perform the encoded operation.

## Example
Assume, we have a way to (automatically) create a functor
```c++
Vector + Vector + Vector -> std::function<double(int)>
```
e.g., by using a lambda expression
```c++
std::function<double(int)> addThreeVectors = [&a,&b,&c](int i) { return a[i]+b[i]+c[i]; };
```
In assignment of `std::function<double(int)>` to `Vector`:
```c++
for (int i = 0; i < size_; ++i)
  data_[i] = addThreeVectors(i);
```

---

# Expression templates: Composition of operations
- We can only implement unary and binary operators, not `a + b + c` as one operator directly.
- Complex expressions can be decomposed into unary and binary operations, e.g.,<br> `(a + b) + c`
- Instead of performing a vector sum directly, we can return an object with the same interface
  as a vector that just encodes the operation:
  * An `operator[](int) -> double` for element access
  * A `size() -> int` method for obtaining the number of elements

---

# Expression templates: Composition of operations

```c++
class VectorPlusExpr
{
  Vector const& a_;
  Vector const& b_;

public:
  VectorPlusExpr (Vector const& a, Vector const& b)
    : a_(a)
    , b_(b)
  {}

  // element access operator
  double operator[] (int i) const { return a_[i] + b_[i]; }

  // size information
  int size () const { return a_.size(); }
};
```

---

# Expression templates: Composition of operations
Or with templates:
```c++
template <class A, class B>
class PlusExpr
{
  A const& a_;
  B const& b_;

public:
  PlusExpr (A const& a, A const& b)
    : a_(a)
    , b_(b)
  {}

  // element access operator
  double operator[] (int i) const { return a_[i] + b_[i]; }

  // size information
  int size () const { return a_.size(); }
};
```

---

# Expression templates: Composition of operations
The expression `a + b + c` can now be encoded by composition of `PlusExpr`:

```c++
a + b + c -> PlusExpr<PlusExpr<Vector, Vector>, Vector>
```
Thus, the `operator+` can simply return the binary expression `PlusExpr`:
```c++
template <class A, class B>
PlusExpr<A,B> operator+ (A const& a, B const& b)
{
  return PlusExpr<A,B>{a,b};
}
```

> .h3[Note:] In this operation no copy or move is involved. It stores everything by reference.

---

# Expression templates
## Generalization
- One could write for each individual operator its own expression
- **Better:** Also encode the operation in a template parameter, e.g., as functor

```c++
template <class Functor, class A, class B>
class BinaryExpr
{
  Functor f_;
  A const& a_;
  B const& b_;
public:
  BinaryExpr (Functor f, A const& a, B const& b)
    : f_(f), a_(a), b_(b)
  {}
  // access the i'th element of the expression
  double operator[](int i) const { return f_( a_[i], b_[i] ); }

  // size information
  int size () const { return a_.size(); }
};
```

---

# Expression templates
## Example
Using the functor `Plus`:
```c++
struct Plus {
  template <class T1, class T2>
  auto operator() (T1 const& x, T2 const& y) const { return x + y; }
};
```
we can write the `PlusExpr` as

```c++
a + b + c -> BinaryExpr<Plus, BinaryExpr<Plus, Vector, Vector>, Vector>
```

--

Thus, the `operator+` can simply return the binary expression `BinaryExpr<Plus,...>`:
```c++
template <class A, class B>
BinaryExpr<Plus,A,B> operator+ (A const& a, B const& b)
{
  return BinaryExpr<Plus,A,B>{Plus{}, a,b};
}
```

---

# Expression templates
## Example (modern)
Or using lambdas, placeholder types and class-template-argument-deduction:
```c++
auto operator+ (auto const& a, auto const& b)
{
  return BinaryExpr{[](auto ai, auto bi) { return ai + bi; }, a, b};
}
```

---

# Expression templates
## Terminal Operations
- A terminal operation is an operation when the expression is actually evaluated.
- It might be that the expression can be evaluated only once.

### Examples:
- Constructor
- Assignment operator
- Inside of reduction functions, (e.g. vector norms or inner products)
- On direct element access to the expression

---


# Expression templates
## Terminal Operations
### Vector with Constructor from Expression
```c++
struct Vector {
  ...
  template <class F, class A, class B>
  Vector (BinaryExpr<F,A,B> const& expr)  // construction from expression
    : Vector(expr.size())
  {
    for (int i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] = expr[i];
  }
  ...
```

---

# Expression templates
## Terminal Operations
### Vector with assignment operators
```c++
  ...
  template <class F, class A, class B>
  Vector& operator= (BinaryExpr<F,A,B> const& expr)
  {
    assert(size_ == expr.size());
    for (int i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] = expr[i];
  }

  template <class F, class A, class B>
  Vector& operator+= (BinaryExpr<F,A,B> const& expr)
  {
    assert(size_ == expr.size());
    for (int i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] += expr[i];
  }
};
```
