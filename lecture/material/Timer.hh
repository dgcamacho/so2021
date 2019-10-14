#pragma once

#include <chrono>

namespace scprog
{
  /// time measurement methods
  class Timer
  {
    using value_type = double;
    using Clock     = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using fsec      = std::chrono::duration<value_type>;

  public:
    /// initializes the timer with current time
    Timer()
      : t0(Clock::now())
    {}

    /// resets the timer to current time
    void reset()
    {
      t0 = Clock::now();
    }

    /// returns the elapsed time (from construction or last reset) to now in seconds
    value_type elapsed() const
    {
      auto t1 = Clock::now();
      fsec fs = t1 - t0;
      return fs.count();
    }

  private:
    /// start time
    TimePoint t0;
  };

}  // end namespace scprog
