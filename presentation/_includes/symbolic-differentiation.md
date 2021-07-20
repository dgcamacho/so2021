---
class: center, middle
# Symbolic Differentiation
---

# Symbolic Differentiation
## Introduction
- Computing first or higher-order derivatives is important for numerical algorithms:
  * solving nonlinear equations using Newton's method
  * Gradient decent methods for optimization
  * solving ordinary differential equations

- Three common methods for evaluating derivatives:
  1. **Numerical differentiation:** e.g. using finite-difference approximations or polynomial interpolation.
  2. **Automatic differentiation (AD):** get evaluation of derivative while evaluating the function, e.g., by using *dual numbers*. Examples: ADIFOR, ADOL-C
  3. **Symbolic derivatives:** Differentiating the function gives new function object that can be evaluated like a regular function. Examples: Maple, Mathematica, Matlab

.footnote[D. Kourounis, L. Gergidis, M. Saunders, A. Walther, O. Schenk: Compile-Time Symbolic Differentiation Using C++ Expression Templates, (2017)]

---

# Symbolic Differentiation
## Expression Templates

.pure-g[.pure-u-1-2[
- Expression templates encode the composition of functions and build and (abstract) expression syntax tree.
- A binary operation \(\circ\) between two functions \(f, g\) is represented by composition on evaluation:
].pure-u-1-2[
.center[<img src="images/expression-tree.png" width="90%">]
]]

\[
  f\circ g = \circ(f, g):\mathbb{R}\to\mathbb{R}; x\mapsto\big(\circ(f,g)\big)(x) =\circ(f(x),g(x)) = f(x)\circ g(x).
\]

---

# Symbolic Differentiation
## Expression Templates
- Instead of vector expressions we consider *function expressions*
- **Everything is an expression!** Everything should be evaluable like a function.

### Variables are expressions

\[
  x_i:\mathbb{R}^n\to\mathbb{R}; \{x_1,\ldots,x_n\}\mapsto x_i
\]

### Numbers are expressions

\[
  2:\mathbb{R}^n\to\mathbb{R}; \{x_1,\ldots,x_n\}\mapsto 2
\]

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

```c++
template <int varID>
struct Variable
{
  double operator() (double const* x) const
  {
    return x[varID];
  }
};
```

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

.pure-g[.pure-u-15-24[
```c++
template <int varID>
struct Variable
{
  double operator() (double const* x) const
  {
    return x[varID];
  }
};
```
].pure-u-1-24[].pure-u-8-24[
```c++
Variable<0> x0;
Variable<1> x1;
Variable<2> x2;
```
]]

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

.pure-g[.pure-u-15-24[
```c++
template <int varID>
struct Variable
{
  double operator() (double const* x) const
  {
    return x[varID];
  }
};
```
].pure-u-1-24[].pure-u-8-24[
```c++
Variable<0> x0;
Variable<1> x1;
Variable<2> x2;
```
]]
- Each Variable has a different type!

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

```c++
template <int value>
struct Integer
{
  double operator() (double const* /*x*/) const
  {
    return double(value);
  }
};
```

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

.pure-g[.pure-u-15-24[
```c++
template <int value>
struct Integer
{
  double operator() (double const* /*x*/) const
  {
    return double(value);
  }
};
```
].pure-u-1-24[].pure-u-8-24[
```c++
Integer<0> _0;
Integer<1> _1;
Integer<2> _2;
```
]]
- Maybe real constants `Real<1.234>`? Should be possible since c++20!

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

```c++
struct Number
{
  double value_;
  Number (double value) : value_(value) {}

  double operator() (double const* /*x*/) const
  {
    return value_;
  }
};
```

---

# Symbolic Differentiation
## Expression Templates

We start with these simple variable/number expressions to introduce the expression concept:
- A function expression is a type that has an `operator()` accepting a vector of `double`s and returning a `double`
- Could be generalized to arbitrary data types, but this is not needed here:

.pure-g[.pure-u-15-24[
```c++
struct Number
{
  double value_;
  Number (double value) : value_(value) {}

  double operator() (double const* /*x*/) const
  {
    return value_;
  }
};
```
].pure-u-1-24[].pure-u-8-24[
```c++
Number a = 1.234;
Number b{3.14159};
```
]]

---

# Symbolic Differentiation
## Expression Templates
- Similar to vector expressions, we can introduce composition of functions.
- See also the example from the exercise

```c++
template <class F, class A1, class A2>
struct BinaryExpr
{
  F f_;
  A1 a1_;
  A2 a2_;

  BinaryExpr (F f, A1 a1, A2 a2)
    : f_(f), a1_(a1), a2_(a2) {}

  double operator() (double const* x) const
  {
    return f_(a1_(x), a2_(x));
  }
};
```

---

# Symbolic Differentiation
## Expression Templates
- Similar to vector expressions, we can introduce composition of functions.
- See also the example from the exercise

.pure-g[.pure-u-12-24[
```c++
template <class F, class A1, class A2>
struct BinaryExpr
{
  F f_;
  A1 a1_;
  A2 a2_;

  BinaryExpr (F f, A1 a1, A2 a2)
    : f_(f), a1_(a1), a2_(a2) {}

  double operator() (double const* x) const
  {
    return f_(a1_(x), a2_(x));
  }
};
```
].pure-u-1-24[].pure-u-11-24[
```c++
template <class F, class A>
struct UnaryExpr
{
  F f_;
  A a_;

  UnaryExpr (F f, A a)
    : f_(f), a_(a) {}

  double operator() (double const* x) const
  {
    return f_(a_(x));
  }
};
```
]]

---

# Symbolic Differentiation
## Expression Templates
- Similar to vector expressions, we can introduce composition of functions.
- See also the example from the exercise
- Outlook: **Variadic Composer**

```c++
template <class F, class... Args>
struct VariadicExpr
{
  F f_;
  std::tuple<Args...> args_;

  VariadicExpr (F f, Args... args)
    : f_(f), args_(args...) {}

  auto operator() (double const* x) -> double const
  {
    return std::apply([&](auto... arg) { return f_(arg(x)...); }, args_);
  }
};
```

---

# Symbolic Differentiation
## Expression Templates
### Examples
```c++
struct Plus { auto operator() (auto a, auto b) const { return a + b; } };
struct Mult { auto operator() (auto a, auto b) const { return a * b; } };
struct Exp {  auto operator() (auto a) const { return std::exp(a); } };
```

<br>
.pure-g[.pure-u-12-24[
```c++
// F + G -> BinaryExpr<Plus,F,G>
template <class F, class G>
auto operator+ (F const& f, G const& g) {
  return BinaryExpr{Plus{},f,g};
}

// F * G -> BinaryExpr<Mult,F,G>
template <class F, class G>
auto operator* (F const& f, G const& g) {
  return BinaryExpr{Mult{},f,g};
}
```
].pure-u-1-24[].pure-u-11-24[
```c++
// Exp(F) -> UnaryExpr<Exp,F>
template <class F>
auto exp (F const& f) {
  return UnaryExpr{Exp{},f};
}
```
]]

---

# Symbolic Differentiation
## Expression Templates
### Examples
```c++
struct Plus { auto operator() (auto a, auto b) const { return a + b; } };
struct Mult { auto operator() (auto a, auto b) const { return a * b; } };
struct Exp {  auto operator() (auto a) const { return std::exp(a); } };
```

<br>
.pure-g[.pure-u-12-24[
```c++
// F + G -> VariadicExpr<Plus,F,G>
template <class F, class G>
auto operator+ (F const& f, G const& g) {
  return VariadicExpr{Plus{},f,g};
}

// F * G -> VariadicExpr<Mult,F,G>
template <class F, class G>
auto operator* (F const& f, G const& g) {
  return VariadicExpr{Mult{},f,g};
}
```
].pure-u-1-24[].pure-u-11-24[
```c++
// Exp(F) -> VariadicExpr<Exp,F>
template <class F>
auto exp (F const& f) {
  return VariadicExpr{Exp{},f};
}
```
]]

---

# Symbolic Differentiation
## Expression Templates
### Examples
The expression shown in the abstract syntax tree can now be represented in expression templates
```c++
Variable<0> x0;
Variable<1> x1;
Variable<2> x2;
Integer<2> _2;

auto f = _2 * x2 + exp(x0 * x1);
double x[] = { -1.0, 2.5, 3.14 };
std::cout << f(x) << std::endl; // outputs the value of 2*3.14+std::exp(-2.5)
```

---

# Symbolic Differentiation
## Compile-time partial derivatives
- We want to implement partial derivatives of multi-variate functions, e.g., \(\partial f/\partial x_i\)
- General idea: provide derivative expression that defines and instantiates the type of the derivative as
  one of the expression templates introduced above:

```c++
template <class F, int varID>
struct Derivative {
  using type = Integer<0>;                          // type of the derivative
  static type generate (F const& f) { return {}; }; // generator for the derivative
};

template <class F, int varID>                   // alias for the generated derivative type
using Derivative_t = typename Derivative<F,varID>::type;

template <int varID, class F>                   // note the different order of the arguments
auto derivative (F const& f) {
  return Derivative<F,varID>::generate(f);
}
```

---

# Symbolic Differentiation
## Compile-time partial derivatives
- At first, we need specializations for constants: \(\partial N/\partial x_i = 0\)

```c++
template <int value, int varID>
struct Derivative<Integer<value>, varID>
{
  using type = Integer<0>;
  static type generate (Integer<value>) { return type{}; }
};
```

---

# Symbolic Differentiation
## Compile-time partial derivatives
- Second, we need a specialization for variables.

\(\partial x_i/\partial x_j = 0\) for \(i\neq j\)

```c++
template <int i, int j>
struct Derivative<Variable<i>, j>
{
  using type = Integer<0>;
  static type generate (Variable<i>) { return type{}; }
};
```

\(\partial x_i/\partial x_i = 1\)

```c++
template <int i>
struct Derivative<Variable<i>, i> // specialization for i == j
{
  using type = Integer<1>;
  static type generate (Variable<i>) { return type{}; }
};
```

---

# Symbolic Differentiation
## Compile-time partial derivatives for expressions
- Now we consider `UnaryExpr` and `BinaryExpr`
- For compositions of functions, differentiation works by chain rule:

\[
  \frac{\partial f_1(A)}{\partial x}\to \frac{\partial A}{\partial x} f_1'(A)
\]

\[
  \frac{\partial f_2(A_1, A_2)}{\partial x}\to \frac{\partial A_1}{\partial x}\cdot\partial_1 f_2(A_1,A_2) + \frac{\partial A_2}{\partial x}\cdot\partial_2 f_2(A_1,A_2)
\]

where \(f_1, f_2, A, A_1\) and \(A_2\) are function expressions and \(f'_1(A)\) is an expression build from the (partial) derivative of the unary operation \(f_1\), applied to the expression \(A\). Analogously, \(\partial_1 f_2(A_1,A_2)\) and \(\partial_2 f_2(A_1,A_2)\) are corresponding partial derivatives w.r.t. the first or second argument.

---

# Symbolic Differentiation
## Compile-time partial derivatives for expressions
For `UnaryExpr`:
```c++
template <class F, class A, int varID>
struct Derivative<UnaryExpr<F,A>, varID>
{
  using dF = Derivative_t<F, 0>;         // functor
  using dA = Derivative_t<A, varID>;    // expression

  using type = BinaryExpr<Mult, UnaryExpr<dF, A>, dA>;
  static type generate(UnaryExpr<F,A> const& expr)
  {
    return UnaryExpr<dF,A>(derivative<0>(expr.f_), expr.a_)
              * derivative<varID>(expr.a_);     // f1'(A) * dA/dx_i
  }
};
```

---

# Symbolic Differentiation
## Compile-time partial derivatives for expressions
For `BinaryExpr`:
```c++
template<class F, class A0, class A1, int varID>
struct Derivative<BinaryExpr<F,A0,A1>, varID >
{
  using dF0 = Derivative_t<F, 0>;       // functors
  using dF1 = Derivative_t<F, 1>;
  using dA0 = Derivative_t<A0, varID>;  // expressions
  using dA1 = Derivative_t<A1, varID>;

  using type = BinaryExpr<Plus, BinaryExpr<Mult, BinaryExpr<dF0,A0,A1>, dA0>,
				BinaryExpr<Mult, BinaryExpr<dF1,A0,A1>, dA1> >;
  static type generate (BinaryExpr<F,A0,A1> const& expr)
  {
    return BinaryExpr<dF0,A0,A1>(derivative<0>(expr.f_), expr.a1_, expr.a2_)
              * derivative<varID>(expr.a1_)
         + BinaryExpr<dF1,A0,A1>(derivative<1>(expr.f_), expr.a1_, expr.a2_)
              * derivative<varID>(expr.a2_);
  }
};
```

---

# Symbolic Differentiation
## Compile-time partial derivatives for functors
- Also the simple functors must be differentiated.
- Since the `varID` is itself an integer, we can use it to denote the argument number to differentiate

\(\partial_0\exp = \exp' = \exp\)
```c++
template <>
struct Derivative<Exp,0>
{
  using type = Exp;
  static type generate (Exp) { return {}; }
};
```

---

# Symbolic Differentiation
## Compile-time partial derivatives for functors
- Also the simple functors must be differentiated.
- Since the `varID` is itself an integer, we can use it to denote the argument number to differentiate

\(\partial_a (a + b) = 1 = \partial_b (a + b)\)
```c++
template <>
struct Derivative<Plus,0>
{
  using type = Integer<1>;      // NOTE: Integer<1> must be a binary functor!
  static type generate (Plus) { return {}; }
};
template <>
struct Derivative<Plus,1>
{
  using type = Integer<1>;
  static type generate (Plus) { return {}; }
};
```

---

# Symbolic Differentiation
## Compile-time partial derivatives for functors
- Also the simple functors must be differentiated.
- Since the `varID` is itself an integer, we can use it to denote the argument number to differentiate

\(\partial_a (a \cdot b) = b,\; \partial_b (a \cdot b) = a\)

.pure-g[.pure-u-1-2[
```c++
// A functor returning th i'th argument
template <int i>
struct Arg
{
  auto operator() (auto a, auto b) const
  {
    if constexpr (i == 0)
      return a;
    else
      return b;
  }
};
```
].pure-u-1-2[
```c++
template <>
struct Derivative<Mult,0>
{
  using type = Arg<1>;
  static type generate (Mult) { return {}; }
};
template <>
struct Derivative<Mult,1>
{
  using type = Arg<0>;
  static type generate (Mult) { return {}; }
};
```
]]

---

# Symbolic Differentiation
## Compile-time partial derivatives
### Example

```c++
int main() {
  Variable<0> x0;
  Variable<1> x1;
  Variable<2> x2;
  Integer<2> _2;

  auto f = _2 * x2 + exp(x0 * x1);
  double x[] = { -1.0, 2.5, 3.14 };
  std::cout << f(x) << " == " << 2*x[2] + std::exp(x[0] * x[1]) << std::endl;

  auto d0f = derivative<0>(f);
  std::cout << d0f(x) << " == " << x[1] * std::exp(x[0] * x[1]) << std::endl;
  auto d1f = derivative<1>(f);
  std::cout << d1f(x) << " == " << x[0]*std::exp(x[0] * x[1]) << std::endl;
  auto d2f = derivative<2>(f);
  std::cout << d2f(x) << " == " << 2 << std::endl;
}
```

---

# Symbolic Differentiation
## Compile-time partial derivatives

**It works!**

--

But generated expressions are very heavy:
```c++
template <class Expr>
void print (Expr const&) {
  std::cout << __PRETTY_FUNCTION__ << std::endl; // print all template parameters
}
...
print(d2f);  // should be just Integer<2>
```

---

# Symbolic Differentiation
## Compile-time partial derivatives
But `print(d2f);` results in
```bash
void print(const Expr&) [with Expr = BinaryExpr<Plus, BinaryExpr<Mult, BinaryExpr<Integer<1>,
BinaryExpr<Mult, Integer<2>, Variable<2> >, UnaryExpr<Exp, BinaryExpr<Mult, Variable<0>,
Variable<1> > > >, BinaryExpr<Plus, BinaryExpr<Mult, BinaryExpr<Arg<1>, Integer<2>, Variable<2> >,
Integer<0> >, BinaryExpr<Mult, BinaryExpr<Arg<0>, Integer<2>, Variable<2> >, Integer<1> > > >,
BinaryExpr<Mult, BinaryExpr<Integer<1>, BinaryExpr<Mult, Integer<2>, Variable<2> >, UnaryExpr<Exp,
BinaryExpr<Mult, Variable<0>, Variable<1> > > >, BinaryExpr<Mult, UnaryExpr<Exp, BinaryExpr<Mult,
Variable<0>, Variable<1> > >, BinaryExpr<Plus, BinaryExpr<Mult, BinaryExpr<Arg<1>, Variable<0>,
Variable<1> >, Integer<0> >, BinaryExpr<Mult, BinaryExpr<Arg<0>, Variable<0>, Variable<1> >,
Integer<0> > > > > >]
```

--

## Example 2
If you try to differentiate the expression \(\exp(x) + \exp(2x) + \exp(3x)\)  6-times your compiler will
crash or will take some minutes or gigabyte to compile.

---

# Symbolic Differentiation
## Term simplifications
- Introduce another template that performs some simplifications based on rules
- Rules are again implemented using template specialization
- The default simplification rule means: do nothing

```c++
template <class Expr>
struct Simplify
{
  using type = Expr;
  static Expr const& generate (Expr const& expr) { return expr; }
};

template <class Expr>
using Simplify_t = typename Simplify<Expr>::type;

template <class Expr>
auto simplify (Expr const& expr) { return Simplify<Expr>::generate(expr); }
```

---

# Symbolic Differentiation
## Term simplifications
### Set of rules

\[
x \pm 0 \to x,\quad 0 \pm x \to x \\
x \cdot 0 \to 0,\quad 0 \cdot x \to 0 \\
x \cdot 1 \to x,\quad 1 \cdot x \to x \\
n \cdot (m \cdot x) \to (n m)x \\
\exp(0) \to 1 \\
\exp(1) \to e
\]

To not get ambiguities, we need also some special cases explicitly:
\[
0 \pm 0 \to 0,\quad 0 \cdot 1 = 1 \cdot 0 \to 0,\quad 0 \cdot 0 \to 0,\quad 1 \cdot 1\to 1
\]

---

# Symbolic Differentiation
## Term simplifications
Let's start with the `UnaryExpr`
```c++
template <>
struct Simplify<UnaryExpr<Exp,Integer<0>>>
{
  using type = Integer<1>;
  static type generate (UnaryExpr<Exp,Integer<0>> const&)
  {
    return type{};
  }
};
template <>
struct Simplify<UnaryExpr<Exp,Integer<1>>>
{
  using type = Number;
  static type generate (UnaryExpr<Exp,Integer<1>> const&)
  {
    return Number{M_E}; // or Real<M_E>
  }
};
```

---

# Symbolic Differentiation
## Term simplifications

The `BinaryExpr` must be listed/specialized one by one:
```c++
template <class E>
struct Simplify<BinaryExpr<Plus,E,Integer<0>>>    // E + 0
{
  using type = E;
  static type generate (BinaryExpr<Plus,E,Integer<0>> const& expr)
  {
    return expr.a1_;
  }
};
template <class E>
struct Simplify<BinaryExpr<Plus,Integer<0>,E>>    // 0 + E
{
  using type = E;
  static type generate (BinaryExpr<Plus,Integer<0>,E> const& expr)
  {
    return expr.a2_;
  }
};
```

---

# Symbolic Differentiation
## Term simplifications

The `BinaryExpr` must be listed/specialized one by one:
```c++
// specialization 0 + 0 would be ambiguous
template <>
struct Simplify<BinaryExpr<Plus,Integer<0>,Integer<0>>> // 0 + 0
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Plus,Integer<0>,Integer<0>> const& expr)
  {
    return {};
  }
};
```

---

# Symbolic Differentiation
## Term simplifications

Simplification of an arbitrary `BinaryExpr`: recursive simplification
```c++
template <class F, class A1, class A2>
struct Simplify<BinaryExpr<F,A1,A2>>
{
  using type = BinaryExpr<F, Simplify_t<A1>, Simplify_t<A2>>
  static type generate (BinaryExpr<Plus,Integer<0>,Integer<0>> const& expr)
  {
    return {expr.f_, simplify(expr.a1_), simplify(expr.a2_)};
  }
};
```

---

# Symbolic Differentiation
## Term simplifications
Simplification rules can now be used in definition of derivative:

```c++
template <class F, class A, int varID>
struct Derivative<UnaryExpr<F,A>, varID>
{
  using dF = Derivative_t<F, 0>;         // functor
  using dA = Derivative_t<A, varID>;    // expression

  using type = Simplify_t< BinaryExpr<Mult, UnaryExpr<dF, A>, dA> >;
  static type generate(UnaryExpr<F,A> const& expr)
  {
    return simplify( UnaryExpr<dF,A>(derivative<0>(expr.f_), expr.a_)
        * derivative<varID>(expr.a_) );     // f1'(A) * dA/dx_i
  }
};
```

---

# Symbolic Differentiation
## Term simplifications
### Example
After implementing a lot more of these simplification rules:
```c++
print(d2f)
...
void print(const Expr&) [with Expr = Integer<2>]
```