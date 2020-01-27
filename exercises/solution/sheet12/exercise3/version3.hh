#include <cmath>
#include <tuple>

// compiler requires std=c++2a or -std=c++20
// only g++-10 or newer

namespace scprog
{
  namespace Concept
  {
    template <class F>
    concept Function = requires(F f)
    {
      &f.operator(); // f has operator(), i.e. one can take a pointer to this member-function
    };

    template <class F, class... Args>
    concept Invocable = requires(F f, Args... args)
    {
      f(args...);
    };

  } // end namespace Concept


  // alias for the function concept
  template <class F>
  concept Function_c = Concept::Function<F>;


  // the Composerr class
  // ------------------

  // Requirement: F is model of N-Functor where N=sizeof...(Gs)
  template <class F, class... Gs>
    requires Concept::Function<F> && (Concept::Function<Gs> && ...)
  struct Composer
  {
    Composer(F const& f, Gs const&... gs)
      : f_(f)
      , gs_(gs...)
    {}

    template <class... Ts>
      requires (Concept::Invocable<Gs,Ts...> && ...)
    auto operator()(Ts const&... ts)
    {
      auto eval = [&](auto&& g) { return g(ts...); };
      return std::apply([eval,f=f_](auto&&... gs) { return f(eval(std::forward<decltype(gs)>(gs))...); }, gs_);
    }

  private:
    F f_;
    std::tuple<Gs...> gs_;
  };


  // some unary functors wrapping std functions
  // ------------------------------------------

  struct Sqr
  {
    template <class T>
    auto operator()(T const& t) const { return t*t; }
  };

  template <class F>
    requires Concept::Function<F> // use requires clause to enforce concept
  auto sqr(F const& f)
  {
    return Composer{Sqr{}, f};
  }


  struct Sqrt
  {
    template <class T>
    auto operator()(T const& t) const { return std::sqrt(t); }
  };

  template <Function_c F> // use concept instead of `class` or `typename`
  auto sqrt(F const& f)
  {
    return Composer{Sqrt{}, f};
  }


  struct Exp
  {
    template <class T>
    auto operator()(T const& t) const { return std::exp(t); }
  };

  auto exp(Function_c auto const& f) // use concept in function argument directly
  {
    return Composer{Exp{}, f};
  }


  struct Tanh
  {
    template <class T>
    auto operator()(T const& t) const { return std::tanh(t); }
  };

  template <class F>
    requires Concept::Function<F>
  auto tanh(F const& f)
  {
    return Composer{Tanh{}, f};
  }


  struct Log
  {
    template <class T>
    auto operator()(T const& t) const { return std::log(t); }
  };

  template <class F>
    requires Concept::Function<F>
  auto log(F const& f)
  {
    return Composer{Log{}, f};
  }


  // some binary functors
  // --------------------

  struct Plus
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 + t1; }
  };

  template <class F0, class F1>
    requires Concept::Function<F0> && Concept::Function<F1>
  auto operator+(F0 const& f0, F1 const& f1)
  {
    return Composer{Plus{}, f0, f1};
  }


  struct Minus
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 - t1; }
  };

  template <class F0, class F1>
    requires Concept::Function<F0> && Concept::Function<F1>
  auto operator-(F0 const& f0, F1 const& f1)
  {
    return Composer{Minus{}, f0, f1};
  }


  struct Multiplies
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 * t1; }
  };

  template <class F0, class F1>
    requires Concept::Function<F0> && Concept::Function<F1>
  auto operator*(F0 const& f0, F1 const& f1)
  {
    return Composer{Multiplies{}, f0, f1};
  }


  struct Divides
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 / t1; }
  };

  template <class F0, class F1>
    requires Concept::Function<F0> && Concept::Function<F1>
  auto operator/(F0 const& f0, F1 const& f1)
  {
    return Composer{Divides{}, f0, f1};
  }

  // special functor representing the i'th argument passed to a function:

  template <std::size_t I = 0u>
  struct Arg
  {
    template <class... Ts>
    auto const& operator()(Ts const&... ts) const { return std::get<I>(std::forward_as_tuple(ts...)); }
  };


} // end namespace scprog
