#include <cmath>
#include <iostream>

#define SIMPLIFY 1

struct Plus {
  template <class A, class B>
  auto operator() (A const& a, B const& b) const { return a + b; }
};
struct Mult {
  template <class A, class B>
  auto operator() (A const& a, B const& b) const { return a * b; }
};
struct Exp {
  template <class A>
  auto operator() (A const& a) const { return std::exp(a); }
};

// some basic expressions:

template <int varID>
struct Variable
{
  double operator() (double const* x) const
  {
    return x[varID];
  }
};

// The integer class is both, an expression and a functor
template <int value>
struct Integer
{
  template <class... Ts>
  double operator() (Ts const&...) const
  {
    return double(value);
  }
};

struct Number
{
  double value_;
  Number (double value) : value_(value) {}

  double operator() (double const* x) const
  {
    return value_;
  }
};

// Composition of F(A)
template <class F, class A>
struct UnaryExpr
{
  F f_;
  A a_;

  UnaryExpr (F f, A const& a)
    : f_(f), a_(a) {}

  double operator() (double const* x) const
  {
    return f_(a_(x));
  }
};

// Exp(F) -> UnaryExpr<Exp,F>
template <class F>
auto exp (F const& f) {
  return UnaryExpr<Exp,F>{Exp{},f};
}


// Composition of F(A1,A2)
template <class F, class A1, class A2>
struct BinaryExpr
{
  F f_;
  A1 a1_;
  A2 a2_;

  BinaryExpr (F f, A1 const& a1, A2 const& a2)
    : f_(f), a1_(a1), a2_(a2) {}

  double operator() (double const* x) const
  {
    return f_(a1_(x), a2_(x));
  }
};

// F + G -> BinaryExpr<Plus,F,G>
template <class F, class G>
auto operator+ (F const& f, G const& g) {
  return BinaryExpr<Plus,F,G>{Plus{},f,g};
}

// F * G -> BinaryExpr<Mult,F,G>
template <class F, class G>
auto operator* (F const& f, G const& g) {
  return BinaryExpr<Mult,F,G>{Mult{},f,g};
}


// Simplification of expressions
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


#if SIMPLIFY
// basic simplification rules: recursively
template <class F, class A>
struct Simplify<UnaryExpr<F,A>>
{
  using type = UnaryExpr<F,Simplify_t<A>>;
  static type generate (UnaryExpr<F,A> const& expr)
  {
    return {expr.f_, simplify(expr.a_)};
  }
};

// basic simplification rules: recursively
template <class F, class A1, class A2>
struct Simplify<BinaryExpr<F,A1,A2>>
{
  using type = BinaryExpr<F,Simplify_t<A1>,Simplify_t<A2>>;
  static type generate (BinaryExpr<F,A1,A2> const& expr)
  {
    return {expr.f_, simplify(expr.a1_), simplify(expr.a2_)};
  }
};
#endif






// Generator for derivative expressions
template <class F, int varID>
struct Derivative;

template <class F, int varID>                   // alias for the generated derivative type
using Derivative_t = typename Derivative<F,varID>::type;

template <int varID, class F>                   // note the different order of the arguments
auto derivative (F const& f) {
  return Derivative<F,varID>::generate(f);
}

// Derivative of a general unary expression
template <class F, class A, int varID>
struct Derivative<UnaryExpr<F,A>, varID>
{
  using dF = Derivative_t<F, 0>;         // functor
  using dA = Derivative_t<A, varID>;    // expression

  using type = Simplify_t<Simplify_t<
    BinaryExpr<Mult, UnaryExpr<dF, A>, dA>
    >>;

  static type generate(UnaryExpr<F,A> const& expr)
  {
    return simplify(simplify(
      UnaryExpr<dF,A>(derivative<0>(expr.f_), expr.a_)
        * derivative<varID>(expr.a_) ));     // f1'(A) * dA/dx_i
  }
};

// Derivative of a general binary expression
template<class F, class A1, class A2, int varID>
struct Derivative<BinaryExpr<F,A1,A2>, varID >
{
  using dF0 = Derivative_t<F, 0>;       // functors
  using dF1 = Derivative_t<F, 1>;
  using dA1 = Derivative_t<A1, varID>;  // expressions
  using dA2 = Derivative_t<A2, varID>;

  using type = Simplify_t<Simplify_t<BinaryExpr<Plus,
    Simplify_t<BinaryExpr<Mult, BinaryExpr<dF0,A1,A2>, dA1> >,
		Simplify_t<BinaryExpr<Mult, BinaryExpr<dF1,A1,A2>, dA2> > >
    >>;

  static type generate (BinaryExpr<F,A1,A2> const& expr)
  {
    return simplify(simplify(
      simplify(BinaryExpr<dF0,A1,A2>(derivative<0>(expr.f_), expr.a1_, expr.a2_)
        * derivative<varID>(expr.a1_) ) +
      simplify(BinaryExpr<dF1,A1,A2>(derivative<1>(expr.f_), expr.a1_, expr.a2_)
        * derivative<varID>(expr.a2_) )
      ));
  }
};

// -----------------------------------

// Derivative of a plus expression
template<class A1, class A2, int varID>
struct Derivative<BinaryExpr<Plus,A1,A2>, varID >
{
  using dA1 = Derivative_t<A1, varID>;  // expressions
  using dA2 = Derivative_t<A2, varID>;

  using type = Simplify_t<Simplify_t<BinaryExpr<Plus, dA1, dA2> >>;
  static type generate (BinaryExpr<Plus,A1,A2> const& expr)
  {
    return simplify(simplify( derivative<varID>(expr.a1_) + derivative<varID>(expr.a2_) ));
  }
};

// derivatives of some basic expressions

template <int value, int varID>
struct Derivative<Integer<value>, varID>
{
  using type = Integer<0>;
  static type generate (Integer<value>) { return {}; }
};

template <int varID>
struct Derivative<Number, varID>
{
  using type = Integer<0>;
  static type generate (Number) { return {}; }
};

template <int i, int j>
struct Derivative<Variable<i>, j>
{
  using type = Integer<0>;
  static type generate (Variable<i>) { return {}; }
};

template <int i>
struct Derivative<Variable<i>, i> // specialization for i == j
{
  using type = Integer<1>;
  static type generate (Variable<i>) { return {}; }
};


template <>
struct Derivative<Exp,0>
{
  using type = Exp;
  static type generate (Exp) { return {}; }
};

#if SIMPLIFY
template <>
struct Simplify<UnaryExpr<Exp,Integer<0>>>
{
  using type = Integer<1>;
  static type generate (UnaryExpr<Exp,Integer<0>> const&) { return type{}; }
};
template <>
struct Simplify<UnaryExpr<Exp,Integer<1>>>
{
  using type = Number;
  static type generate (UnaryExpr<Exp,Integer<1>> const&) { return Number{M_E}; }
};
#endif


template <>
struct Derivative<Plus,0>
{
  using type = Integer<1>;
  static type generate (Plus) { return {}; }
};

template <>
struct Derivative<Plus,1>
{
  using type = Integer<1>;
  static type generate (Plus) { return {}; }
};

#if SIMPLIFY
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

template <>
struct Simplify<BinaryExpr<Plus,Integer<0>,Integer<0>>> // 0 + 0
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Plus,Integer<0>,Integer<0>> const&) { return {}; }
};

template <int n, int m>
struct Simplify<BinaryExpr<Plus,Integer<n>,Integer<m>>> // n + m
{
  using type = Integer<n+m>;
  static type generate (BinaryExpr<Plus,Integer<n>,Integer<m>> const&) { return {}; }
};

template <int n>
struct Simplify<BinaryExpr<Plus,Integer<n>,Integer<0>>> // n + 0
{
  using type = Integer<n>;
  static type generate (BinaryExpr<Plus,Integer<n>,Integer<0>> const&) { return {}; }
};

template <int m>
struct Simplify<BinaryExpr<Plus,Integer<0>,Integer<m>>> // n + m
{
  using type = Integer<m>;
  static type generate (BinaryExpr<Plus,Integer<0>,Integer<m>> const&) { return {}; }
};

template <int n, class A1, class A2>
struct Simplify<BinaryExpr<Integer<n>,A1,A2>>
{
  using type = Integer<n>;
  static type generate (BinaryExpr<Integer<n>,A1,A2> const&) { return {}; }
};

template <int n, class A>
struct Simplify<UnaryExpr<Integer<n>,A>>
{
  using type = Integer<n>;
  static type generate (UnaryExpr<Integer<n>,A> const&) { return {}; }
};
#endif


// functor representing the i'th argument
template <int i>
struct Arg
{
  template <class A, class B>
  auto operator() (A const& a, B const& b) const
  {
    if constexpr (i == 0)
      return a;
    else
      return b;
  }
};

template <int i, int j>
struct Derivative<Arg<i>,j>
{
  using type = Integer<0>;
  static type generate (Arg<i>) { return {}; }
};

template <int i>
struct Derivative<Arg<i>,i>
{
  using type = Integer<1>;
  static type generate (Arg<i>) { return {}; }
};

#if SIMPLIFY
template <class A1, class A2>
struct Simplify<BinaryExpr<Arg<0>,A1,A2>>
{
  using type = A1;
  static type generate (BinaryExpr<Arg<0>,A1,A2> const& expr) { return expr.a1_; }
};

template <class A1, class A2>
struct Simplify<BinaryExpr<Arg<1>,A1,A2>>
{
  using type = A2;
  static type generate (BinaryExpr<Arg<1>,A1,A2> const& expr) { return expr.a2_; }
};
#endif

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

#if SIMPLIFY
template <class E>
struct Simplify<BinaryExpr<Mult,E,Integer<0>>>    // E * 0
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,E,Integer<0>> const&) { return {}; }
};

template <class E>
struct Simplify<BinaryExpr<Mult,Integer<0>,E>>    // 0 * E
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<0>,E> const&) { return {}; }
};

template <>
struct Simplify<BinaryExpr<Mult,Integer<0>,Integer<0>>> // 0 * 0
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<0>,Integer<0>> const&) { return {}; }
};

template <class E>
struct Simplify<BinaryExpr<Mult,E,Integer<1>>>    // E * 1
{
  using type = E;
  static type generate (BinaryExpr<Mult,E,Integer<1>> const& expr) { return expr.a1_; }
};

template <class E>
struct Simplify<BinaryExpr<Mult,Integer<1>,E>>    // 1 * E
{
  using type = E;
  static type generate (BinaryExpr<Mult,Integer<1>,E> const& expr) { return expr.a2_; }
};

template <>
struct Simplify<BinaryExpr<Mult,Integer<1>,Integer<1>>> // 1 * 1
{
  using type = Integer<1>;
  static type generate (BinaryExpr<Mult,Integer<1>,Integer<1>> const&) { return {}; }
};

template <>
struct Simplify<BinaryExpr<Mult,Integer<0>,Integer<1>>> // 0 * 1
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<0>,Integer<1>> const&) { return {}; }
};

template <>
struct Simplify<BinaryExpr<Mult,Integer<1>,Integer<0>>> // 1 * 0
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<1>,Integer<0>> const&) { return {}; }
};

template <int n, int m>
struct Simplify<BinaryExpr<Mult,Integer<n>,Integer<m>>> // n * m
{
  using type = Integer<n*m>;
  static type generate (BinaryExpr<Mult,Integer<n>,Integer<m>> const&) { return {}; }
};

template <int n>
struct Simplify<BinaryExpr<Mult,Integer<n>,Integer<0>>> // n * 0
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<n>,Integer<0>> const&) { return {}; }
};

template <int m>
struct Simplify<BinaryExpr<Mult,Integer<0>,Integer<m>>> // 0 * m
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<0>,Integer<m>> const&) { return {}; }
};

template <int n>
struct Simplify<BinaryExpr<Mult,Integer<n>,Integer<1>>> // n * 1
{
  using type = Integer<n>;
  static type generate (BinaryExpr<Mult,Integer<n>,Integer<1>> const&) { return {}; }
};

template <int m>
struct Simplify<BinaryExpr<Mult,Integer<1>,Integer<m>>> // 1 * m
{
  using type = Integer<m>;
  static type generate (BinaryExpr<Mult,Integer<1>,Integer<m>> const&) { return {}; }
};

template <int n, int m, class E>
struct Simplify<BinaryExpr<Mult,Integer<n>,BinaryExpr<Mult,Integer<m>,E>>> // n * (m * E)
{
  using type = BinaryExpr<Mult,Integer<n*m>,E>;
  static type generate (BinaryExpr<Mult,Integer<n>,BinaryExpr<Mult,Integer<m>,E>> const& expr)
  { return {Mult{}, Integer<n*m>{}, expr.a2_.a2_}; }
};

template <int n, int m, class E>
struct Simplify<BinaryExpr<Mult,Integer<n>,BinaryExpr<Mult,E,Integer<m>>>> // n * (E * m)
{
  using type = BinaryExpr<Mult,Integer<n*m>,E>;
  static type generate (BinaryExpr<Mult,Integer<n>,BinaryExpr<Mult,E,Integer<m>>> const& expr)
  { return {Mult{}, Integer<n*m>{}, expr.a2_.a1_}; }
};

template <int m, class E>
struct Simplify<BinaryExpr<Mult,Integer<0>,BinaryExpr<Mult,Integer<m>,E>>> // 0 * (m * E)
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<0>,BinaryExpr<Mult,Integer<m>,E>> const& expr)
  { return {}; }
};

template <int m, class E>
struct Simplify<BinaryExpr<Mult,Integer<0>,BinaryExpr<Mult,E,Integer<m>>>> // 0 * (E * m)
{
  using type = Integer<0>;
  static type generate (BinaryExpr<Mult,Integer<0>,BinaryExpr<Mult,E,Integer<m>>> const& expr)
  { return {}; }
};

template <int m, class E>
struct Simplify<BinaryExpr<Mult,Integer<1>,BinaryExpr<Mult,E,Integer<m>>>> // 1 * (E * m)
{
  using type = BinaryExpr<Mult,Integer<m>,E>;
  static type generate (BinaryExpr<Mult,Integer<1>,BinaryExpr<Mult,E,Integer<m>>> const& expr)
  { return {Mult{}, Integer<m>{}, expr.a2_.a1_}; }
};

template <int m, class E>
struct Simplify<BinaryExpr<Mult,Integer<1>,BinaryExpr<Mult,Integer<m>,E>>> // 1 * (m * E)
{
  using type = BinaryExpr<Mult,Integer<m>,E>;
  static type generate (BinaryExpr<Mult,Integer<1>,BinaryExpr<Mult,Integer<m>,E>> const& expr)
  { return {Mult{}, Integer<m>{}, expr.a2_.a2_}; }
};
#endif

template <class Expr>
void print (Expr const&)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  Variable<0> x0;
  Variable<1> x1;
  Variable<2> x2;
  Integer<1> _1;
  Integer<2> _2;
  Integer<3> _3;

  auto f = _2 * x2 + exp(x0 * x1);
  double x[] = { -1.0, 2.5, 3.14 };
  print(f);
  std::cout << f(x) << " == " << 2*x[2] + std::exp(x[0] * x[1]) << std::endl;

  auto d0f = derivative<0>(f);
  print(d0f);
  std::cout << d0f(x) << " == " << x[1] * std::exp(x[0] * x[1]) << std::endl;

  auto d1f = derivative<1>(f);
  print(d1f);
  std::cout << d1f(x) << " == " << x[0]*std::exp(x[0] * x[1]) << std::endl;

  auto d2f = derivative<2>(f);
  print(d2f);
  std::cout << d2f(x) << " == " << 2 << std::endl; // = 2

  auto g = exp(_1 * x0) + exp(_2 * x0) + exp(_3 * x0);
  auto dg = simplify( derivative<0>(g) );
  auto ddg = simplify( derivative<0>(dg) );
  auto dddg = simplify( derivative<0>(ddg) );
  auto ddddg = simplify( derivative<0>(dddg) );
  auto dddddg = simplify( derivative<0>(ddddg) );
  auto ddddddg = simplify( derivative<0>(dddddg) );
  print(ddddddg);
}