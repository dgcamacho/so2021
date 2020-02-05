#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

namespace scprog
{
  /// Range adaptor that maps the values by a given functor
  template <class Functor, class Range>
  class Map
  {
  private:
    using T = typename Range::value_type; // or: std::decay_t<decltype(*std::declval<Range>().begin())>

  public:
    using value_type    = std::result_of_t<Functor(T)>;
    using iterator_type = typename Range::const_iterator;

    // provide a type defined inside the class, representing the iterator of the range adaptor
    struct const_iterator
    {
      using iterator_category = std::forward_iterator_tag;
      using value_type        = Map::value_type;
      using difference_type   = typename iterator_type::difference_type;
      using reference         = value_type;

      // Constructor, stores functor `f` and an iterator `it`
      const_iterator(Functor f, iterator_type it)
        : f_(f)
        , it_(it)
      {}

      // incrementing
      const_iterator& operator++()    { ++it_; return *this; }
      const_iterator  operator++(int) { const_iterator tmp(*this); ++(*this); return tmp; }

      // comparison
      bool operator==(const_iterator const& other) const { return it_ == other.it_; }
      bool operator!=(const_iterator const& other) const { return !(*this == other); }

      // dereferencing
      reference operator*() const
      {
        return f_(*it_);
      }

    private:
      Functor f_;
      iterator_type it_;
    };

  public:
    // Constructor, stores the functor `f` and begin/end iterator of range `r`
    Map(Functor f, Range const& r)
      : f_(f)
      , begin_(r.begin())
      , end_(r.end())
    {}

    const_iterator begin() const
    {
      return {f_, begin_};
    }

    const_iterator end() const
    {
      return {f_, end_};
    }

  private:
    Functor f_;
    iterator_type begin_;
    iterator_type end_;
  };


  /// Generator function for \ref Map
  template <class Functor, class Range>
  Map<Functor, Range> map(Functor f, Range const& range)
  {
    return {f, range};
  }

} // end namespace scprog
