#include <cmath>
#include <tuple>

// This version is an extension of version1, that uses variadic templates to generalize the
// composer to arbitrary arity of the functor arguments. Additionally, class-template argument deduction
// of c++17 is used to remove the necessity of a generator function.

// compiler requires std=c++1z or std=c++17

namespace scprog
{
  template <class Model>
  struct Functor
  {
    Model& get() { return static_cast<Model&>(*this); }
    Model const& get() const { return static_cast<Model const&>(*this); }
  };

  // the Composerr class
  // ------------------

  // Requirement: F is model of N-Functor where N=sizeof...(Gs)
  template <class F, class... Gs>
  struct Composer : Functor<Composer<F,Gs...>>
  {
    Composer(F const& f, Gs const&... gs)
      : f_(f)
      , gs_(gs...)
    {}

    template <class... Ts>
    auto operator()(Ts const&... ts) const
    {
      auto eval = [&](auto&& g) -> decltype(auto) { return g(ts...); };
      return std::apply([eval,f=f_](auto&&... gs) -> decltype(auto)
        {
          return f(eval(std::forward<decltype(gs)>(gs))...);
        }, gs_);
    }

  private:
    F f_;
    std::tuple<Gs...> gs_;
  };


  // some unary functors wrapping std functions
  // ------------------------------------------

  struct Sqr : Functor<Sqr>
  {
    template <class T>
    auto operator()(T const& t) const { return t*t; }
  };

  template <class F>
  auto sqr(Functor<F> const& f)
  {
    return Composer{Sqr{}, f.get()};
  }


  struct Sqrt : Functor<Sqrt>
  {
    template <class T>
    auto operator()(T const& t) const { return std::sqrt(t); }
  };

  template <class F>
  auto sqrt(Functor<F> const& f)
  {
    return Composer{Sqrt{}, f.get()};
  }


  struct Exp : Functor<Exp>
  {
    template <class T>
    auto operator()(T const& t) const { return std::exp(t); }
  };

  template <class F>
  auto exp(Functor<F> const& f)
  {
    return Composer{Exp{}, f.get()};
  }


  struct Tanh : Functor<Tanh>
  {
    template <class T>
    auto operator()(T const& t) const { return std::tanh(t); }
  };

  template <class F>
  auto tanh(Functor<F> const& f)
  {
    return Composer{Tanh{}, f.get()};
  }


  struct Log : Functor<Log>
  {
    template <class T>
    auto operator()(T const& t) const { return std::log(t); }
  };

  template <class F>
  auto log(Functor<F> const& f)
  {
    return Composer{Log{}, f.get()};
  }


  // some binary functors
  // --------------------

  struct Plus : Functor<Plus>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 + t1; }
  };

  template <class F0, class F1>
  auto operator+(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return Composer{Plus{}, f0.get(), f1.get()};
  }


  struct Minus : Functor<Minus>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 - t1; }
  };

  template <class F0, class F1>
  auto operator-(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return Composer{Minus{}, f0.get(), f1.get()};
  }


  struct Multiplies : Functor<Multiplies>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 * t1; }
  };

  template <class F0, class F1>
  auto operator*(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return Composer{Multiplies{}, f0.get(), f1.get()};
  }


  struct Divides : Functor<Divides>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 / t1; }
  };

  template <class F0, class F1>
  auto operator/(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return Composer{Divides{}, f0.get(), f1.get()};
  }

  // special functor representing the i'th argument passed to a function:

  template <std::size_t I = 0u>
  struct Arg : Functor<Arg<I>>
  {
    template <class... Ts>
    auto const& operator()(Ts const&... ts) const { return std::get<I>(std::forward_as_tuple(ts...)); }
  };


} // end namespace scprog
