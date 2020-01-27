#include <cmath>

namespace scprog
{
  // some unary functors wrapping std functions

  struct Sqr
  {
    template <class T>
    auto operator()(T const& t) const { return t*t; }
  };

  struct Sqrt
  {
    template <class T>
    auto operator()(T const& t) const { return std::sqrt(t); }
  };

  struct Exp
  {
    template <class T>
    auto operator()(T const& t) const { return std::exp(t); }
  };

  struct Tanh
  {
    template <class T>
    auto operator()(T const& t) const { return std::tanh(t); }
  };

  struct Log
  {
    template <class T>
    auto operator()(T const& t) const { return std::log(t); }
  };

  // some binary functors

  struct Plus
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 + t1; }
  };

  struct Minus
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 - t1; }
  };

  struct Multiplies
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 * t1; }
  };

  struct Divides
  {
    template <class T0, class T1>
    auto operator()(T0 const& t0, T1 const& t1) const { return t0 / t1; }
  };

  // the composer class

  // Requirement: F is model of UnaryFunctor
  template <class F, class G>
  class Composer
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
  Composer<F, G> compose(F const& f, G const& g)
  {
    return {f, g};
  }


  // Requirement: F is model of BinaryFunctor
  template <class F, class G0, class G1>
  class Composer2
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
  Composer2<F, G0, G1> compose(F const& f, G0 const& g0, G1 const& g1)
  {
    return {f, g0, g1};
  }

} // end namespace scprog
