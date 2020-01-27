#pragma once

#include <cassert> // assert
#include <cstddef> // std::size_t

#include "exercise2.1.hh" // integer_range_iterator

namespace scprog
{
  template <class Int = int>
  struct integer_range
  {
    using value_type = Int;
    using iterator = integer_range_iterator<Int>;
    using const_iterator = iterator;
    using size_type = std::size_t;

    // Constructor with 2 arguments, represents the interval [begin,end)
    integer_range(value_type begin, value_type end)
      : begin_(begin)
      , end_(end)
    {
      assert( begin_ <= end_ );
    }

    // Constructor with just 1 argument, represents the interval [0,end)
    // implemented using delegating constructor
    explicit integer_range(value_type end)
      : integer_range(0, end)
    {}

    // Return an iterator to the begin_ integer
    auto begin() const
    {
      return const_iterator{begin_};
    }

    // Return an iterator to the end_ integer
    auto end() const
    {
      return const_iterator{end_};
    }

    // Return the i'th entry in the range
    Int operator[](size_type i) const
    {
      assert(i < size());
      return begin_ + i;
    }

    // Return the size of the range
    size_type size() const
    {
      return size_type(end_ - begin_);
    }

  private:
    value_type begin_;
    value_type end_;
  };

  // Generator for the integer_range type
  template <class Int>
  auto range(Int end)
  {
    return integer_range<Int>{end};
  }

  // Generator for the integer_range type
  template <class Int>
  auto range(Int begin, Int end)
  {
    return integer_range<Int>{begin, end};
  }

} // end namespace scprog
