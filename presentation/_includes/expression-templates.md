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

--

## Performance problem
- Multiple allocations and deallocations cost time (penalty for small vectors)
- Multiple loops cost time (penalty for large vectors)


---

# Expression Templates
## Pairwise evaluation problem

```c++
Vector a{N}, b{N}, c{N}, sum{N};
sum = a + b + c;
```
generates code like this:
```c++
double* tmp1 = new double[N];   // allocation of temporary
for (int i = 0; i < N; ++i)     // copy                         loop 1
  tmp1[i] = a[i];
for (int i = 0; i < N; ++i)     // operator+=                   loop 2
  tmp1[i] += b[i];
double* tmp2 = new double[N];   // allocation of temporary
for (int i = 0; i < N; ++i)     // copy                         loop 3
  tmp2[i] = tmp1[i];
for (int i = 0; i < N; ++i)     // operator+=                   loop 4
  tmp2[i] += c[i];
delete[] tmp1;                  // destroy temporary
for (int i = 0; i < N; ++i)     // copy                         loop 5
  sum[i] = tmp2[i];
delete[] tmp2;                  // destroy temporary
```

---

# Expression Templates
## Pairwise evaluation problem

```c++
Vector a{N}, b{N}, c{N}, sum{N};
sum = a + b + c;
```
generates code like this: (with copy elision)
```c++
double* tmp1 = new double[N];   // allocation of temporary
for (int i = 0; i < N; ++i)     // copy                         loop 1
  tmp1[i] = a[i];
for (int i = 0; i < N; ++i)     // operator+=                   loop 2
  tmp1[i] += b[i];
// double* tmp2 = new double[N];
for (int i = 0; i < N; ++i)     // copy                         loop 3
  sum[i] = tmp1[i];
for (int i = 0; i < N; ++i)     // operator+=                   loop 4
  sum[i] += c[i];
delete[] tmp1;                  // destroy temporary
// delete[] tmp2;
```

---

# Expression Templates
## Pairwise evaluation problem

```c++
Vector a{N}, b{N}, c{N}, sum{N};
sum = a + b + c;
```
generates code like this: (with *more* copy elision - not automatically)
```c++
// double* tmp1 = new double[N];
for (int i = 0; i < N; ++i)     // copy                       loop 1
  sum[i] = a[i];
for (int i = 0; i < N; ++i)     // operator+=                 loop 2
  sum[i] += b[i];
// double* tmp2 = new double[N];


for (int i = 0; i < N; ++i)     // operator+=                 loop 3
  sum[i] += c[i];
// delete[] tmp1;
// delete[] tmp2;
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
void vector_sum (Vector const& a, Vector const& b, Vector const& c, Vector& sum)
{
  for (int i = 0; i < N; ++i)
    sum[i] = a[i] + b[i] + c[i];
}
...
vector_sum(a, b, c, sum); // problem: no mathematical notation
```

---

# Domain-Specific (Embedded) Languages
## Domain-Specific Language (DSL)
- Description and solution of a problem can be expressed in the idiom and at the level of
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
- An assignment of the expression to a variable performs the encoded operation.

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
  {
    assert(a_.size() == b_.size());
  }

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
  {
    assert(a_.size() == b_.size());
  }

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
(a + b) + c -> PlusExpr<PlusExpr<Vector, Vector>, Vector>
```

--

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
  double operator[] (int i) const { return f_( a_[i], b_[i] ); }

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
(a + b) + c -> BinaryExpr<Plus, BinaryExpr<Plus, Vector, Vector>, Vector>
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
## Unary expressions

- Binary expressions can handle `+`, `-`
- Unary expression can handle negation `-`, but also multiplication with a scalar:

```c++
template <class UnaryFunctor, class A>
class UnaryExpr
{
  UnaryFunctor f_;
  A const& a_;

public:
  BinaryExpr (UnaryFunctor f, A const& a)
    : f_(f), a_(a)
  {}
  // access the i'th element of the expression
  double operator[] (int i) const { return f_( a_[i] ); }

  // size information
  int size () const { return a_.size(); }
};
```

---

# Expression templates
## Unary expressions
### Example 1: negation

To negate all the elements in a vector, apply the negate operator elementwise:
```c++
template <class A>
auto operator- (A const& a)
{
  return UnaryExpr{[](auto ai) { return -ai; }, a};
}
```

---

# Expression templates
## Unary expressions
### Example 2: scaling
Scale the elements of a container from the left (or from the right)
```c++
// multiplication from the left with factor
template <class A>
auto operator* (double factor, A const& a)
{
  return UnaryExpr{[factor](auto ai) { return factor*ai; }, a};
}

// multiplication from the right with factor
template <class A>
auto operator* (A const& a, double factor)
{
  return UnaryExpr{[factor](auto ai) { return ai*factor; }, a};
}
```

---

# Expression templates
## Generator expressions
- Similar to the `std::generate` algorithm with a generator function parameter, generator expressions
  can be used to generate values without storing them explicitly

```c++
template <class Generator>
class GeneratorExpr
{
  Generator g_;
  int size_;  // need size information explicitly
public:
  GeneratorExpr (Generator g, int size)
    : g_(g), size_(size) {}
  // generate the i'th element
  double operator[] (int i) const { return g_( i ); }
  // size information
  int size () const { return size_; }
};
```

**Note:** The generator it not in the classical sense a generator, i.e., a functor with empty parameter list,
but a functor that just receives an index.

---

# Expression templates
## Generator expressions
### Example 1: Unit vector
The Euclidean unit vectors \(\mathbf{e}_i\in\mathbb{R}^n\)
```c++
template <int i>
auto e (int size)
{
  return GeneratorExpr{[](int j) { return i==j ? 1.0 : 0.0; }, size};
}

int main() {
  const int i = 1;
  int n = 3;

  auto unit_vector = e<i>(n);
}
```

---

# Expression templates
## Generator expressions
### Example 2: Zero vector
The vector representing the origin \((0,0,\ldots,0)^T\):
```c++
auto zero (int size)
{
  return GeneratorExpr{[](int /*j*/) { return 0.0; }, size};
}

int main() {
  auto zero_vector = zero(3);
}
```


---

# Expression templates
## Terminal Operations
- A terminal operation is an operation that executes the expression, using `operator[]`.
- It might be that the expression can be evaluated only once.

### Examples:
- Constructor
- Assignment operator
- Inside of reduction functions, (e.g. vector norms or inner products)
- On direct element access to the expression

---


# Expression templates
## Terminal Operations: Vector with Constructor from Expression
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
## Terminal Operations: Vector with assignment operators
```c++
  ...
  template <class F, class A, class B>
  Vector& operator= (BinaryExpr<F,A,B> const& expr)
  {
    assert(size_ == expr.size());
    for (int i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] = expr[i];
    return *this;
  }
  template <class F, class A, class B>
  Vector& operator+= (BinaryExpr<F,A,B> const& expr)
  {
    assert(size_ == expr.size());
    for (int i = 0; i < size_; ++i)       // Evaluate the expression elementwise
      data_[i] += expr[i];
    return *this;
  }
};
```

---

# Expression templates
## Terminal Operations: Inner product

Evaluate expressions in a loop.

```c++
template <class A, class B>
double dot (A const& a, B const& b)
{
  assert(a.size() == b.size());
  double res = 0.0;
  for (int i = 0; i < a.size(); ++i)
    res += a[i] * b[i];
  return res;
}
```

---

# Expression templates
## Expression templates in action

```c++
Vector a{10}, b{10}, b{10};

Vector sum = a + b + c;
//     sum = BinaryExpr{Plus{}, BinaryExpr{Plus{}, a, b}, c};

Vector sum2 = -a + e<3>(10) + zero;
//     sum2 = BinaryExpr{Plus{},
//              BinaryExpr{Plus{},
//                UnaryExpr{Negate{},a},
//                GeneratorExpr{Unit<3>{},10} },
//              c };

double res = dot(a + b, e<3>(10) - c);
//           dot(BinaryExpr{Plus{}, a, b},
//               BinaryExpr{Minus{}, GeneratorExpr{Unit<3>{},10}, c})
```

---

# Expression templates
## Some Design Problems
- Operators, e.g., `operator+`, are implemented generically, thus accept everything \(\to\) how can we restrict the arguments?
- When implementing `UnaryExpr`, `BinaryExpr`, maybe also `GeneratorExpr`, then the number of constructors and assignment operators in the
  `Vector` class grows.
- Inventing a new type of expression means, we have to extend the `Vector`.
- Everything is stored by reference. This might lead to dangling references.

--

## Different Solution ideas
- curiously recurring template pattern (CRTP)
- C++20 concepts

---

# Curiously recurring template pattern (CRTP)
An idiom in C++ in which a class `D` derives from a class template instantiation `B<D>` using `D` itself as a template argument.
```c++
// The Curiously Recurring Template Pattern (CRTP)
template <class T>
struct Base
{
  // methods within Base can use template to access members of Derived
};
struct Derived : public Base<Derived>
{
  // ...
};
```

- Class `Derived` inherits all members from `Base<Derived>`, its base class.
- Class `Base` cannot directly access any member from `Derived`

---

# Curiously recurring template pattern (CRTP)
An idiom in C++ in which a class `D` derives from a class template instantiation `B<D>` using `D` itself as a template argument.
```c++
// The Curiously Recurring Template Pattern (CRTP)
template <class T>
struct Base
{
  void interface ()
  {
    static_cast<T*>(this)->implementation();    // cast the pointer to the class instance
  }                                             // to the derived class type.
protected:
  Base () {}                                    // constructor is protected. Can be called
};                                              // by derived class only.
struct Derived : public Base<Derived>
{
  void implementation ()
  {
    // the actual implementation
  }
};
```

---

# Curiously recurring template pattern (CRTP)
An idiom in C++ in which a class `D` derives from a class template instantiation `B<D>` using `D` itself as a template argument.

```c++
template <class T>
void foo (Base<T>& base)
{
  base.interface();
}

int main ()
{
  Derived derived;
  foo(derived);
}
```

`foo()` can be called, since `Derived` *is-a* `Base<Derived>`.

---

# Expression Templates - CRTP
## A Base Expression
- Use the CRT pattern to implement a common base class for all expressions:

```c++
template <class E>
struct Expr
{
  // Element access
  auto operator[] (auto const i) const
  {
    return static_cast<E const&>(*this).access_impl(i);
  }

  // Length of the vector expression
  auto size () const
  {
    return static_cast<E const&>(*this).size_impl();
  }

protected:
  Expr () = default;
};
```

---

# Expression Templates - CRTP
## All expressions derived from `Expr<E>`

```c++
template <class Functor, class A, class B>
class BinaryExpr : public Expr< BinaryExpr<Functor,A,B> >
{
  Functor f_;
  A const& a_;
  B const& b_;
public:
  BinaryExpr (Functor f, A const& a, B const& b)
    : f_(f), a_(a), b_(b)
  {
    assert(a_.size() == b_.size());
  }

  // implementation of element access
  double access_impl (int i) const { return f_( a_[i], b_[i] ); }

  // implementation of size information
  int size_impl () const { return a_.size(); }
};
```

---

# Expression Templates - CRTP
## Generic argument `Expr<E>`
In all functions expecting an expression and combining expressions, use `Expr<E>` instead:
```c++
template <class A, class B>
auto operator+ (Expr<A> const& a, Expr<B> const& b)
{
  return BinaryExpr{Plus{}, a, b};
}
```

**Note:** The class `Vector` must also derive from `Expr<Vector>`.
```c++
class Vector : public Expr<Vector>
{
  template <class E>
  Vector (Expr<E> const& expr); // copy-construct the vector from a generic expression
  ...
  double access_impl (int i) const { return data_[i]; }
  int size_impl () const { return size_; }
};
```

---

# Expression Templates - CRTP
## Example: inner product

```c++
template <class E1, class E2>
auto dot (Expr<E1> const& expr1, Expr<E2> const& expr2)
{
  assert(a.size() == b.size());
  using T = decltype(expr1[0]*expr2[0]);  // type of the elements
  using S = decltype(expr1.size());       // type of the indices

  T res = 0.0;
  for (S i = 0; i < a.size(); ++i)
    res += a[i] * b[i];
  return res;
}
```

---

# Expression Templates
## Design problems with CRTP

- It is intrusive, i.e., you need to derive from a base class
- You need to implement a specific "impl" function.
- Increases compile times due to additional templates and indirection

## Possible Solution
- C++20 Concepts