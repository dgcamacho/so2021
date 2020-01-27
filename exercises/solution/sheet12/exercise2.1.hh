#pragma once

#include <iterator>

namespace scprog
{
  // An iterator type representing an integer of type Int with iterator semantics
  template <class Int = int>
  struct integer_range_iterator
  {
    using iterator_category = std::forward_iterator_tag;
    using value_type = Int;
    using difference_type = Int;
    using pointer = Int const*;
    using reference = Int;

    // Constructor. Stores the initial integer
    explicit integer_range_iterator(value_type i)
      : i_(i)
    {}

    // (pre)incrementing increments the stored integer
    integer_range_iterator& operator++()
    {
      ++i_;
      return *this;
    }

    // (post)incrementing increments the stored integer and return the old iterator
    // This is implemented in terms of the pre-increment operator
    integer_range_iterator operator++(int)
    {
      integer_range_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    // comparison operator compares the stored integer
    bool operator==(integer_range_iterator const& that) const
    {
      return i_ == that.i_;
    }

    // comparison (unequal) implemented in terms of operator==
    bool operator!=(integer_range_iterator const& that) const
    {
      return !(*this == that);
    }

    // dereferencing returns the stored integer
    reference operator*() const
    {
      return i_;
    }

  private:
    value_type i_;
  };

  // Generator for the iterator class. Can deduce type of passed integer argument.
  template <class Int>
  auto range_iterator(Int i)
  {
    return integer_range_iterator<Int>{i};
  }

} // end namespace scprog
