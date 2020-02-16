#include <cmath>

// This version uses the CRTP base-class implementation to restrict
// template parameters to anything derived from Functor

namespace scprog
{
  // (CRTP) base class for functors
  template <class Model>
  struct Functor
  {
    Model& get() { return static_cast<Model&>(*this); }
    Model const& get() const { return static_cast<Model const&>(*this); }
  };

  // the composer class
  // ------------------

  // Requirement: F is model of UnaryFunctor
  template <class F, class G>
  class Composer : public Functor<Composer<F,G>>
  {
  public:
    Composer(F const& f, G const& g)
      : f_(f)
      , g_(g)
    {}

    template <class T>
    auto operator()(T const& t) const { return f_(g_(t)); }

    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) { return f_(g_(t0,t1)); }

  private:
    F f_;
    G g_;
  };

  template <class F, class G>
  Composer<F, G> compose(Functor<F> const& f, Functor<G> const& g)
  {
    return {f.get(), g.get()};
  }


  // Requirement: F is model of BinaryFunctor
  template <class F, class G0, class G1>
  class Composer2 : public Functor<Composer2<F,G0,G1>>
  {
  public:
    Composer2(F const& f, G0 const& g0, G1 const& g1)
      : f_(f)
      , g0_(g0)
      , g1_(g1)
    {}

    template <class T>
    auto operator()(T const& t) const { return f_(g0_(t), g1_(t)); }

    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) { return f_(g0_(t0,t1), g1_(t0,t1)); }

  private:
    F f_;
    G0 g0_;
    G1 g1_;
  };

  template <class F, class G0, class G1>
  Composer2<F, G0, G1> compose(Functor<F> const& f, Functor<G0> const& g0, Functor<G1> const& g1)
  {
    return {f.get(), g0.get(), g1.get()};
  }

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
    return compose(Sqr{}, f.get());
  }


  struct Sqrt : Functor<Sqrt>
  {
    template <class T>
    auto operator()(T const& t) const { return std::sqrt(t); }
  };

  template <class F>
  auto sqrt(Functor<F> const& f)
  {
    return compose(Sqrt{}, f.get());
  }


  struct Exp : Functor<Exp>
  {
    template <class T>
    auto operator()(T const& t) const { return std::exp(t); }
  };

  template <class F>
  auto exp(Functor<F> const& f)
  {
    return compose(Exp{}, f.get());
  }


  struct Tanh : Functor<Tanh>
  {
    template <class T>
    auto operator()(T const& t) const { return std::tanh(t); }
  };

  template <class F>
  auto tanh(Functor<F> const& f)
  {
    return compose(Tanh{}, f.get());
  }


  struct Log : Functor<Log>
  {
    template <class T>
    auto operator()(T const& t) const { return std::log(t); }
  };

  template <class F>
  auto log(Functor<F> const& f)
  {
    return compose(Log{}, f.get());
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
    return compose(Plus{}, f0.get(), f1.get());
  }


  struct Minus : Functor<Minus>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 - t1; }
  };

  template <class F0, class F1>
  auto operator-(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return compose(Minus{}, f0.get(), f1.get());
  }


  struct Multiplies : Functor<Multiplies>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 * t1; }
  };

  template <class F0, class F1>
  auto operator*(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return compose(Multiplies{}, f0.get(), f1.get());
  }


  struct Divides : Functor<Divides>
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 / t1; }
  };

  template <class F0, class F1>
  auto operator/(Functor<F0> const& f0, Functor<F1> const& f1)
  {
    return compose(Divides{}, f0.get(), f1.get());
  }

  // special functor representing the i'th argument passed to a function:

  // primary template
  template <int I = 0>
  struct Arg;

  // template specialization for the 0th argument
  template <>
  struct Arg<0> : Functor<Arg<0>>
  {
    template <class T0>
    auto const& operator()(T0 const& t0) const { return t0; }

    template <class T0, class T1>
    auto const& operator()(T0 const& t0, T1 const& t1) const { return t0; }
  };

  // template specialization for the 1st argument
  template <>
  struct Arg<1> : Functor<Arg<1>>
  {
    template <class T0, class T1>
    auto const& operator()(T0 const& t0, T1 const& t1) const { return t1; }
  };


} // end namespace scprog
